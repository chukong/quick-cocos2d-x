cc.utils 				= require("framework.cc.utils.init")
cc.net 					= require("framework.cc.net.init")

local PacketBuffer = require("net.PacketBuffer")
local Protocol = require("net.Protocol")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
	printInfo("socket.getTime:%f", cc.net.SocketTCP.getTime())
	printInfo("os.gettime:%f", os.time())
	printInfo("socket._VERSION: %s", cc.net.SocketTCP._VERSION)

	local __luaSocketLabel = ui.newTTFLabelMenuItem({
		text = "lua socket connect",
		size = 32,
		x = display.cx,
		y = display.top - 32,
		listener = handler(self, self.onLuaSocketConnectClicked),
	})

	local __luaSocket1000Label = ui.newTTFLabelMenuItem({
		text = "lua socket send 1000",
		size = 32,
		x = display.cx,
		y = display.top - 64,
		listener = handler(self, function() self:send2Socket(1000, {8000, 1,1}) end)
	})

    self:addChild(ui.newMenu({__luaSocketLabel, __luaSocket1000Label}))

	self._buf = PacketBuffer.new()
end

function MainScene:onStatus(__event)
	printInfo("socket status: %s", __event.name)
end

function MainScene:send2Socket(__method, __msg)
	if not self._socket then
		print("connect first")
		return
	end

	local __def = Protocol.getSend(__method)
	local __buf = PacketBuffer.createPacket(__def, __msg)
	printf("send %u packet: %s", __method, __buf:toString(16))
	self._socket:send(__buf:getPack())
end

function MainScene:onData(__event)
	print("socket receive raw data:", cc.utils.ByteArray.toString(__event.data, 16))
	local __msgs = self._buf:parsePackets(__event.data)
	local __msg = nil
	for i=1,#__msgs do
		__msg = __msgs[i]
		dump(__msg)
	end
end

function MainScene:onLuaSocketConnectClicked()
	if not self._socket then
		self._socket = cc.net.SocketTCP.new("192.168.18.18", 13000, false)
		self._socket:addEventListener(cc.net.SocketTCP.EVENT_CONNECTED, handler(self, self.onStatus))
		self._socket:addEventListener(cc.net.SocketTCP.EVENT_CLOSE, handler(self,self.onStatus))
		self._socket:addEventListener(cc.net.SocketTCP.EVENT_CLOSED, handler(self,self.onStatus))
		self._socket:addEventListener(cc.net.SocketTCP.EVENT_CONNECT_FAILURE, handler(self,self.onStatus))
		self._socket:addEventListener(cc.net.SocketTCP.EVENT_DATA, handler(self,self.onData))
	end
	self._socket:connect()
end

return MainScene
