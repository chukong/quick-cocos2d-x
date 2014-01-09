cc.utils 				= require("framework.cc.utils.init")
cc.net 					= require("framework.cc.net.init")

local PacketBuffer = require("net.PacketBuffer")
local Protocol = require("net.Protocol")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
	echoInfo("socket.getTime:%f", cc.net.SocketTCP.getTime())
	echoInfo("os.gettime:%f", os.time())
	echoInfo("socket._VERSION: %s", SocketTCP._VERSION)

	local __luaSocketLabel = ui.newTTFLabelMenuItem({
		text = "lua socket connect",
		size = 32,
		x = display.cx,
		y = display.top - 32,
		listener = handler(self, self.onLuaSocketConnectClicked),
	})

	local __luaSocket1201Label = ui.newTTFLabelMenuItem({
		text = "lua socket send 1201",
		size = 32,
		x = display.cx,
		y = display.top - 64,
		listener = handler(self, function() self:send2Socket(1201, {8000, 1,1}) end)
	})

	local __luaSocket1202Label = ui.newTTFLabelMenuItem({
		text = "lua socket send 1202",
		size = 32,
		x = display.cx,
		y = display.top - 96,
		listener = handler(self, function() self:send2Socket(1202, {0}) end)
	})

	local __luaSocket1203Label = ui.newTTFLabelMenuItem({
		text = "lua socket send 1203",
		size = 32,
		x = display.cx,
		y = display.top - 128,
		listener = handler(self, function() self:send2Socket(1203, {-1375731712}) end)
	})

    self:addChild(ui.newMenu({__luaSocketLabel, __luaSocket1201Label, __luaSocket1202Label, __luaSocket1203Label}))

	self._buf = PacketBuffer.new()

	self:test()
end

function MainScene:test()
end

function MainScene:onStatus(__event)
	echoInfo("socket status: %s", __event.name)
end

function MainScene:send2Socket(__method, __msg)
	local __def = Protocol.getSend(__method)
	local __buf = PacketBuffer.createPacket(__def, __msg)
	printf("send %u packet: %s", __method, __buf:toString(16))
	self._socket:send(__buf:getPack())
end

function MainScene:onData(__event)
	print("socket receive raw data:", ByteArray.toString(__event.data, 16))
	local __msgs = self._buf:parsePackets(__event.data)
	local __msg = nil
	for i=1,#__msgs do
		__msg = __msgs[i]
		print("msg", i, "ver:", __msg.ver, "method:", __msg.method, "body:", unpack(__msg.body))
		if __msg.method == 2202 then
			for i=1,__msg.body[2].len do
				print(unpack(__msg.body[2].data[i]))
			end
		end
	end
end

function MainScene:onLuaSocketConnectClicked()
	if not self._socket then
		self._socket = SocketTCP.new("192.168.18.88", 30005, false)
		self._socket:addEventListener(SocketTCP.EVENT_CONNECTED, handler(self, self.onStatus))
		self._socket:addEventListener(SocketTCP.EVENT_CLOSE, handler(self,self.onStatus))
		self._socket:addEventListener(SocketTCP.EVENT_CLOSED, handler(self,self.onStatus))
		self._socket:addEventListener(SocketTCP.EVENT_CONNECT_FAILURE, handler(self,self.onStatus))
		self._socket:addEventListener(SocketTCP.EVENT_DATA, handler(self,self.onData))
	end
	self._socket:connect()
end

function MainScene:onSend1101()
	if not self._socket then return end
	self:send2Socket(1202, {0})
end

return MainScene
