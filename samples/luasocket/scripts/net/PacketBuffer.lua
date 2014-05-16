--[[
PacketBuffer receive the byte stream and analyze them, then pack them into a message packet.
The method name, message metedata and message body will be splited, and return to invoker.
@see https://github.com/zrong/as3/blob/master/src/org/zengrong/net/PacketBuffer.as
@author zrong(zengrong.net)
Creation: 2013-11-14
]]

local PacketBuffer = class("PacketBuffer")
local Protocol = require("net.Protocol")

PacketBuffer.ENDIAN = cc.utils.ByteArrayVarint.ENDIAN_BIG

PacketBuffer.MASK1 = 0x86
PacketBuffer.MASK2 = 0x7b
PacketBuffer.RANDOM_MAX = 10000
PacketBuffer.PACKET_MAX_LEN = 2100000000

--[[
packet bit structure
FLAG byte|FLAG byte|TYPE byte|BODY_LEN int|METHOD short|VER byte|META_NUM byte|META bytes|BODY bytes|
]]
PacketBuffer.FLAG_LEN = 2	-- package flag at start, 1byte per flag
PacketBuffer.TYPE_LEN = 1	-- type of message, 1byte
PacketBuffer.BODY_LEN = 4	-- length of message body, int
PacketBuffer.METHOD_LEN = 2	-- length of message method code, short
PacketBuffer.VER_LEN = 1	-- version of message, byte
PacketBuffer.META_NUM_LEN = 1	-- how much item in a message, 1byte

local _DATA_TYPE = 
{
	R = 0,	-- Unsigned Varint int
	S = 1,	-- String
	r = 2,	-- Varint int
}

local function _getDataTypeValue(__type)
	for __k, __v in pairs(_DATA_TYPE) do
		if __v == __type then return __k end
	end
	error(__type .. " is a unavailable type value! You can only use a type value in 012.")
	return nil
end

local function _getKeyFromi(i, __keys)
	if not __keys then return i end
	if __keys[i] then return __keys[i] end
	return i
end

--- metadata item description
function PacketBuffer._createMeta(__fmt)
	local __buf = PacketBuffer.getBaseBA()
	__buf:writeByte(#__fmt)
	for i=1,#__fmt do
		-- create a metadata description: data index(8~4bit 0~248(0xF8,b11111000)) + data type(3~1bit 0~7(b00000111))
		__buf:writeByte( bit.bor(bit.lshift(i-1, 3), _DATA_TYPE[__fmt:sub(i,i)]) )
	end
	return __buf
end

function PacketBuffer._parseMeta(__buf)
	local __meta = {}
	local __metaNum = __buf:readByte()
	for i=1,__metaNum do
		local __metaDes = __buf:readByte()
		--- right shift __metaDes 3 bits, get the head 5 bits
		local __index = bit.rshift(__metaDes, 3) + 1
		--print("parseMeta, __index:", __index)
		-- 7 = b0000 0111, bit and __metaDes, get the last 3 bits. see PacketBuffer._createMeta
		local __type = _getDataTypeValue(bit.band(__metaDes, 7))
		--print("parseMeta, __type:", __type)
		__meta[__index] = __type
	end
	return __meta
end

function PacketBuffer._createBody(__fmt, __body)
	assert(#__fmt == #__body, #__fmt.." ~= "..#__body.." The number of format string must be equivalent to body's!")
	--print("getBody, fmt:", __fmt)
	--print("getBody, body:", unpack(__body))
	local __buf = PacketBuffer.getBaseBA()
	for i=1,#__fmt do
		local __f = __fmt:sub(i,i)
		if __f == "R" then
			__buf:writeUVInt(__body[i])
		elseif __f == "S" then
			__buf:writeStringUVInt(__body[i])
		elseif __f == "r" then
			__buf:writeVInt(__body[i])
		else
			error(__f .. " is a unavailable type! You can only use a type in RSr.")
		end
	end
	return __buf
end

function PacketBuffer._parseBody(__buf, __meta, __fmt, __keys)
	local __body = {}
	for i=1,#__fmt do
		local __f = __fmt:sub(i,i)
		local __metaType = __meta[i]
		local __value = nil
		if __metaType and __metaType ~= __f then
			error("Server datas aren't matched protocol definition! Server defination is "..__metaType.." and protocol is "..__f)
		end
		if __f == "R" then
			__value = (__metaType and __buf:readUVInt()) or 0
		elseif __f == "S" then
			__value = (__metaType and __buf:readStringUVInt()) or ""
		elseif __f == "r" then
			__value = (__metaType and __buf:readVInt()) or 0
		else
			error(__f .. " is a unavailable type! You can only use a type in RSr.")
		end
		local __key = _getKeyFromi(i, __keys)
		__body[__key] = __value
		--print("parseBody, f:", __f, " key:", __key, " value:", __value)
	end
	return __body
end

function PacketBuffer.getBaseBA()
	return cc.utils.ByteArrayVarint.new(PacketBuffer.ENDIAN)
end

--- Create a formated packet that to send server
-- @param __msgDef the define of message, a table
-- @param __msgBodyTable the message body with key&value, a table
function PacketBuffer.createPacket(__msgDef, __msgBodyTable)
	local __buf = PacketBuffer.getBaseBA()
	local __metaBA = PacketBuffer._createMeta(__msgDef.fmt)
	local __bodyBA = PacketBuffer._createBody(__msgDef.fmt, __msgBodyTable)
	--print("metaBA:", __metaBA:getLen())
	--print("bodyBA:", __bodyBA:getLen())
	local __bodyLen = PacketBuffer.METHOD_LEN + PacketBuffer.VER_LEN + __metaBA:getLen() + __bodyBA:getLen()
	-- write 2 flags and message type, for client, is always 0
	__buf:rawPack(
		"b3ihb", 
		PacketBuffer.MASK1, 
		PacketBuffer.MASK2, 
		0,
		__bodyLen,
		__msgDef.method,
		__msgDef.ver
		)
	__buf:writeBytes(__metaBA)
	__buf:writeBytes(__bodyBA)
	return __buf
end

function PacketBuffer:ctor()
	self:init()
end

function PacketBuffer:init()
	self._buf = PacketBuffer.getBaseBA()
end

--- Get a byte stream and analyze it, return a splited table
-- Generally, the table include a message, but if it receive 2 packets meanwhile, then it includs 2 messages.
function PacketBuffer:parsePackets(__byteString)
	local __msgs = {}
	local __pos = 0
	self._buf:setPos(self._buf:getLen()+1)
	self._buf:writeBuf(__byteString)
	self._buf:setPos(1)
	local __flag1 = nil
	local __flag2 = nil
	local __preLen = PacketBuffer.FLAG_LEN + PacketBuffer.TYPE_LEN + PacketBuffer.BODY_LEN
	printf("start analyzing... buffer len: %u, available: %u", self._buf:getLen(), self._buf:getAvailable())
	while self._buf:getAvailable() >= __preLen do
		__flag1 = self._buf:readByte()
		--printf("__flag1:%2X", __flag1)
		--if bit.band(__flag1 ,PacketBuffer.MASK1) == __flag1 then
		if __flag1 == PacketBuffer.MASK1 then
			__flag2 = self._buf:readByte()
			--printf("__flag2:%2X", __flag2)
			--if bit.band(__flag2, PacketBuffer.MASK2) == __flag2 then
			if __flag2 ==  PacketBuffer.MASK2 then
				-- skip type value, client isn't needs it
				self._buf:setPos(self._buf:getPos()+1)
				local __bodyLen = self._buf:readInt()
				local __pos = self._buf:getPos()
				--printf("__bodyLen:%u", __bodyLen)
				-- buffer is not enougth, waiting...
				if self._buf:getAvailable() < __bodyLen then 
					-- restore the position to the head of data, behind while loop, 
					-- we will save this incomplete buffer in a new buffer,
					-- and wait next parsePackets performation.
					printf("received data is not enough, waiting... need %u, get %u", __bodyLen, self._buf:getAvailable())
					print("buf:", self._buf:toString())
					self._buf:setPos(self._buf:getPos() - __preLen)
					break 
				end
				if __bodyLen <= PacketBuffer.PACKET_MAX_LEN then
					local __method = self._buf:readShort()
					local __ver = self._buf:readByte()
					printf("method:%u", __method)
					local __prot = Protocol.getReceive(__method)
					printf("before get meta position:%u", self._buf:getPos())
					local __meta = PacketBuffer._parseMeta(self._buf)
					printf("after get meta position:%u", self._buf:getPos())
					local __msg = {}
					__msg.method = __method
					__msg.ver = __ver
					__msg.body = PacketBuffer._parseBody(self._buf, __meta, __prot.fmt, __prot.keys)
					__msgs[#__msgs+1] = __msg
					printf("after get body position:%u", self._buf:getPos())
				end
			end
		end
	end
	-- clear buffer on exhausted
	if self._buf:getAvailable() <= 0 then
		self:init()
	else
		-- some datas in buffer yet, write them to a new blank buffer.
		printf("cache incomplete buff,len: %u, available: %u", self._buf:getLen(), self._buf:getAvailable())
		local __tmp = PacketBuffer.getBaseBA()
		self._buf:readBytes(__tmp, 1, self._buf:getAvailable())
		self._buf = __tmp
		printf("tmp len: %u, availabl: %u", __tmp:getLen(), __tmp:getAvailable())
		print("buf:", __tmp:toString())
	end
	return __msgs
end

return PacketBuffer
