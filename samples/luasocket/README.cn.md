* [README in english][10]
* [README in chinese][20]

作者： [zrong][1]

这是一个 luasocket 范例。

为了便于使用，我封装了 luasocket 到 cc.net.SocketTCP 类中。这个范例展示如何使用 cc.net.SocketTCP。

同时，在本范例中还使用了 cc.utils.ByteArray 和 cc.utils.ByteArrayVarint。

要了解更多关于 cc.net.SocketTCP 和 cc.utils.ByteArray 的信息，请阅读 [一个LuaSocket封装][6] 和 [用lua实现ByteArray和ByteArrayVarint][7] .

在本范例的 net 包中，有3个 lua 类：

* [net.PacketBuffer][2]  
我们收到的数据包经常是不完整的，特别是当数据包比较大的时候。因此我们必须确保数据包完整才能使用。PacketBuffer 就是做这件事的。
* [net.Protocol][3]  
这个类把数据包解析成人类可读的格式。它转换一个数据包到一个lua table，并且为每个数据项命名。数据项的名称定义在 [net.protocols][4] 文件中。
* [net.protocols][4] 
这是你的协议定义文件。你可以写一个生成器程序来生成它。

下面是本范例运行的log文件。当然，你需要自己实现服务端程序。

	[0.2467] [INFO] socket.getTime:1389319197.462940
	[0.2472] [INFO] os.gettime:1389319197.000000
	[0.2477] [INFO] socket._VERSION: LuaSocket 2.1-rc1
	[0.2530] [INFO] Scene "MainScene:onEnter()"
	[1.9754] [INFO] socket status: SOCKET_TCP_CONNECTED
	[5.8635] send 1000 packet: 86 7B 00 0B 00 00 00 B1 04 00 03 00 08 10 C0 3E 01 01 
	[5.8859] socket receive raw data:  86 7B 00 60 00 00 00 00 7D 00 0D 00 09 11 18 20 28 30 38 40 48 50 58 60 00 3C 63 73 76 3D 34 38 32 28 30 31 30 39 2E 31 35 33 32 32 38 29 0A 66 73 3D 31 33 31 28 30 31 30 39 2E 31 35 33 31 35 31 29 0A 67 73 3D 33 35 32 28 30 31 30 39 2E 31 38 30 33 32 37 29 04 74 65 73 74 00 14 50 D6 03 96 01 00 00 00 0F 6E   103
	[5.8873] start analyzing... buffer len: 103, available: 103
	[5.8878] method:2000
	[5.8884] before get meta position:11
	[5.8897] after get meta position:25
	[5.8904] after get body position:104
	[5.8909] dump from: [string "d:/cocos2dx/quick/samples/luasocket/scripts/scenes/MainScene.lua"]:54: in function <[string "d:/cocos2dx/quick/samples/luasocket/scripts/scenes/MainScene.lua"]:48>
	[5.8921] - "<var>" = {
	[5.8924] -     "body" = {
	[5.8931] -         "ap"          = 0
	[5.8938] -         "crystal"     = 150
	[5.8944] -         "dust"        = 0
	[5.8950] -         "gold"        = 470
	[5.8955] -         "goodsMaxNum" = 110
	[5.8959] -         "goodsNum"    = 15
	[5.8965] -         "lv"          = 20
	[5.8971] -         "mithril"     = 0
	[5.8975] -         "money"       = 80
	[5.8981] -         "flag"        = 0
	[5.8987] -         "name"    = "test"
	[5.8993] -         "sex"         = 0
	[5.8999] -         "ver"     = "csv=482(0109.153228)\nfs=131(0109.153151)\ngs=352(0109.180327)"
	[5.9008] -     }
	[5.9013] -     "method" = 2000
	[5.9019] -     "ver"    = 0
	[5.9025] - }

[1]: http://zengrong.net
[2]: scripts/net/PacketBuffer.lua
[3]: scripts/net/Protocol.lua
[4]: scripts/net/protocols.lua
[6]: http://zengrong.net/post/1980.htm
[7]: http://zengrong.net/post/1968.htm
[10]: README.md
[20]: README.cn.md
