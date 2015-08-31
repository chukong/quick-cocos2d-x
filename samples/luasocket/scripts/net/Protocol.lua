--[[
The file defines all protocols.
@author zrong(zengrong.net)
Creation: 2013-11-15
Latest modification: 2014-01-10

All of the supported data types are following:

	R : Unsigned Varint Int		1~4bit
	r : Varint Int				1~4bit
    I : Unsigned Int			4bit
    i : Int						4bit
    H : Unsigned Short			2bit
    h : Short					2bit
	S : String					dynamic
    b : byte (unsigned char) 	1bit 0~255
    c : char (signed byte)		1bit -127~128
    f : float					4bit
    d : double					8bit

Certainly, a user of this api can only use RSr.
]]

local _p = require("net.protocols")

local Protocol = {}

--- Expand format in protocol, split varint style data and standard data, return a array
local function _expandFmt(__fmt)
    local __pos = 1
    local __fmtArr = {}
	local __indicesArr = {} -- the value in __fmtArr is variant or standard style.
	 -- for metadata description. 
	 -- metadata need relize every data's format and integrate index and type of data item,
	 -- so, expend standard data is necessary. 
	 -- only in this way, the PacketBuffer.createPackets can understand all type of the message data item.
	local __allExpendedFmtArr = {}
	local __index = 1
	local function __saveFmt(__fmt, __isVar)
		__fmtArr[__index] = __fmt
		__indicesArr[__index] = __isVar
		--if not __isVar then
			__allExpendedFmtArr[#__allExpendedFmtArr+1] = Protocol.expandNum(__fmtArr[__index])
		--end
		__index = __index + 1
	end
    while __pos <= #__fmt do
        local i,j = __fmt:find("[RSr]+%d*", __pos)
        if not i  then
			__saveFmt(__fmt:sub(__pos, #__fmt), false)
            return __indicesArr, __fmtArr, __allExpendedFmtArr
        end
        if __pos < i then
			__saveFmt(__fmt:sub(__pos,i-1), false)
        end
		local __varintStr = __fmt:sub(i,j)
		__saveFmt(Protocol.expandNum(__varintStr), true)
        __pos = j + 1
    end
	return __indicesArr, __fmtArr, __allExpendedFmtArr
end

local function _getProtocol(__name, __methodCode, __ver)
	__ver = __ver or 0
	assert(_p[__name][__methodCode], "Can not find ".. __name .." protocol in method:"..__methodCode.."!")
	local __oldTable = _p[__name][__methodCode][__ver]
	assert(__oldTable, "Can not find "..__name.." protocol in method:"..__methodCode.." ver:"..__ver.."!")
	local __newTable = {} 
	__newTable.ver = __ver
	__newTable.method = __methodCode
	__newTable.fmt = Protocol.expandNum(__oldTable.fmt)
	__newTable.keys = __oldTable.keys
	return __newTable
end

function Protocol.expandNum(__fmt)
	local __rep = {}
	local __pattern = "%a%d+"
	for __v in __fmt:gmatch(__pattern) do
		local __f = __v:sub(1, 1)
		local __n = tonumber(__v:sub(2))
		local __nfi = {}
		for i=1,__n do
			__nfi[i] = __f
		end
		__rep[__v] = table.concat(__nfi)
	end
	return __fmt:gsub(__pattern, __rep)
end

function Protocol.getSend(__methodCode, __ver)
	return _getProtocol("send", __methodCode, __ver)
end

function Protocol.getReceive(__methodCode, __ver)
	return _getProtocol("receive", __methodCode, __ver)
end

function Protocol.getReceiveBySend(__methodCode, __ver)
	__methodCode = __methodCode + 1000
	return Protocol.getReceive(__methodCode, __ver)
end

function Protocol.getSendByReceive(__methodCode, __ver)
	__methodCode = __methodCode - 1000
	return Protocol.getSend(__methodCode, __ver)
end

return Protocol
