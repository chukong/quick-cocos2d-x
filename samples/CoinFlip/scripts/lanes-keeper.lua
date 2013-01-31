--
-- KEEPER.LUA
--
-- Keeper state logic
-- DEPRECATED BY THE EQUIVALENT C IMPLEMENTATION, KEPT FOR REFERENCE ONLY
-- SHOULD NOT BE PART OF THE INSTALLATION ANYMORE
--
-- This code is read in for each "keeper state", which are the hidden, inter-
-- mediate data stores used by Lanes inter-state communication objects.
--
-- Author: Asko Kauppi <akauppi@gmail.com>
--
--[[
===============================================================================

Copyright (C) 2008-10 Asko Kauppi <akauppi@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

===============================================================================
]]--

-- We only need to have base and table libraries (and io for debugging)
--
local table_concat = assert( table.concat)
local table_insert = assert( table.insert)
local table_remove = assert( table.remove)
local select, unpack = assert( select), assert( unpack)

--[[
local function WR(...)
    if io then
        io.stderr:write( table_concat({...},'\t').."\n" )
    end
end

local function DEBUG(title,ud,key)
    assert( title and ud and key )

    local data,_= tables(ud)

    local s= tostring(data[key])
    for _,v in ipairs( data[key] or {} ) do
        s= s..", "..tostring(v)
    end
    WR( "*** "..title.." ("..tostring(key).."): ", s )
end
--]]

-----
-- FIFO for a key
--

local fifo_new = function()
    return { first = 1, count = 0}
end

local fifo_push = function( fifo, ...)
    local first, count, added = fifo.first, fifo.count, select( '#', ...)
    local start = first + count - 1
    for i = 1, added do
        fifo[start + i] = select( i, ...)
    end
    fifo.count = count + added
end

local fifo_peek = function( fifo, count)
    if count <= fifo.count then
			local first = fifo.first
			local last = first + count - 1
			return unpack( fifo, first, last)
    end
end

local fifo_pop = function( fifo, count)
    local first = fifo.first
    local last = first + count - 1
    local out = { unpack( fifo, first, last)}
    for i = first, last do
        fifo[i] = nil
    end
    fifo.first = first + count
    fifo.count = fifo.count - count
    return unpack( out)
end


-----
-- Actual data store
--
-- { [linda_deep_ud]= { key= { val [, ... ] } [, ...] }
--      ...
-- }
--
local _data= {}

-----
-- Length limits (if any) for queues
--
-- 0:   don't queue values at all; ':send()' waits if the slot is not vacant
-- N:   allow N values to be queued (slot itself + N-1); wait if full
-- nil: no limits, '_data' may grow endlessly
--
local _limits= {}

-----
-- data_tbl, limits_tbl = tables( linda_deep_ud )
--
-- Gives appropriate tables for a certain Linda (creates them if needed)
--
local function tables( ud )
    -- tables are created either all or nothing
    --
    if not _data[ud] then
        _data[ud]= {}
        _limits[ud]= {}
    end
    return _data[ud], _limits[ud]
end

-----
-- bool= send( linda_deep_ud, key, ...)
--
-- Send new data (1..N) to 'key' slot. This send is atomic; all the values
-- end up one after each other (this is why having possibility for sending
-- multiple values in one call is deemed important).
--
-- If the queue has a limit, values are sent only if all of them fit in.
--
-- Returns: 'true' if all the values were placed
--          'false' if sending would exceed the queue limit (wait & retry)
--
function send( ud, key, ...)

    local data, limits = tables( ud)

    local n = select( '#', ...)

    -- Initialize queue for all keys that have been used with ':send()'
    --
    if data[key] == nil then
        data[key] = fifo_new()
    end
    local fifo = data[key]

    local len = fifo.count
    local m = limits[key]

    if m and len+n > m then
        return false    -- would exceed the limit; try again later
    end

    fifo_push( fifo, ...)
    return true
end


-----
-- [val, key]= receive( linda_deep_ud, key [, ...] )
--
-- Read any of the given keys, consuming the data found. Keys are read in
-- order.
--
function receive( ud, ...)

    local data = tables( ud)

    for i = 1, select( '#', ...) do
        local key = select( i, ...)
        local fifo = data[key]
        if fifo and fifo.count > 0 then
            local val = fifo_pop( fifo, 1)
            if val ~= nil then
                return key, val
            end
        end
    end
end


-----
-- [val1, ... valCOUNT]= receive_batched( linda_deep_ud, key , min_COUNT, max_COUNT)
--
-- Read a single key, consuming the data found.
--
receive_batched = function( ud, key, min_count, max_count)
    if min_count > 0 then
        local fifo = tables( ud)[key]
        if fifo then
            local fifo_count = fifo.count
            if fifo_count >= min_count then
                max_count = max_count or min_count
                max_count = (max_count > fifo_count) and fifo_count or max_count
                return key, fifo_pop( fifo, max_count)
            end
        end
    end
end


-----
-- = limit( linda_deep_ud, key, uint )
--
function limit( ud, key, n)

    local _, limits = tables( ud)

    limits[key] = n
end


-----
-- void= set( linda_deep_ud, key, [val] )
--
function set( ud, key, val)

    local data, _ = tables( ud)

    -- Setting a key to 'nil' really clears it; only queing uses sentinels.
    --
    if val ~= nil then
        local fifo = fifo_new()
        fifo_push( fifo, val)
        data[key] = fifo
    else
        data[key] = nil
    end
end


-----
-- [val]= get( linda_deep_ud, key )
--
function get( ud, key)
    local data, _ = tables( ud)
    local fifo = data[key]
    return fifo and fifo_peek( fifo, 1)
end


-----
-- [val]= count( linda_deep_ud, ...)
--
-- 3 modes of operation
-- linda:count() -> returns a table of key/count pairs
-- linda:count(key) returns the number of items waiting in the key
-- linda:count(key,...) -> returns a table telling, for each key, the number of items
function count( ud, ...)
    local data, _ = tables( ud)
    local n = select( '#', ...)
    if n == 0 then
        local out
        for key, _ in pairs( data) do
			local fifo = data[key]
			local count = fifo and fifo.count or 0
			out = out or {}
            out[key] = count
            found = true
        end
        return out
    elseif n == 1 then
        local key = ...
        local fifo = data[key]
		return fifo and fifo.count or nil
    else -- more than 1 key
        local out
        for i = 1, n do
            local key = select( i, ...)
			local fifo = data[key]
			local count = fifo and fifo.count or nil
			out = out or {}
            out[key] = count
		end
        return out
    end
end


-----
-- void= clear( linda_deep_ud)
--
-- Clear the data structures used for a Linda (at its destructor)
--
function clear( ud)

    _data[ud]= nil
    _limits[ud]= nil
end
