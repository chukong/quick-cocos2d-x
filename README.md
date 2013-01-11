
quick-cocos2d-x is a \*quick\* framework, based cocos2d-x. Make mobile games in Lua. Code Less, Play More!

> [cocos2d-x](http://www.cocos2d-x.org) is a multi-platform 2D game engine in C++, based on cocos2d-iphone and licensed under MIT. Now this engine has been expanded to iOS, Android, Bada, BlackBerry, Marmalade and desktop operating systems like Linux, WindowsXP & Windows7.

## Main Features

-   **Make game in Lua**: Learn easy, Use easy, Build easy.
-   **Enhanced Simulator**: Run the game from any directory, multiple resolution switching, debug console, More detailed error information.
-   **Full-featured development framework**: Write the entire game using Lua.
-   **Native extensions**: Integration of third-party components, including IAP, GameCenter, Gree, Flurry, etc..
-   **Open-Source**: Make your native extensions free. Licen

quick-cocos2d-x is licensed under the MIT license. That means you can use it freely for any purpose — including commercial ones.

~

## CODE LESS, PLAY MORE !

``` Lua
local sprite = display.newSprite("hello.png", 100, 100)
local scene = display.newScene()
scene:addChild(sprite)
display.replaceScene(scene)
```

~

## Full-featured development framework

Main modules:

-   display: creates scenes, display objects, animation ...
-   transition: moving, fades, creates animation programing easy ...
-   audio: play background music, effect sounds ...
-   ui: creates button, menu, label ...
-   luaj: Lua call Java, Java call Lua ...
-   network: Asynchronous HTTP requests, JSON, check the network status ...
-   GameNetwork: Integration GameCenter, Gree Platform, China Mobile Game Community ...
-   Store: Integration IAP, China Mobile Pay API ...
-   GameState: save game state to file, hash check ...

API Documents: [http://dualface.github.com/quick-cocos2d-x/docs/framework/index.html](http://dualface.github.com/quick-cocos2d-x/docs/framework/index.html)

~

## Lua running on the server, share code between client and server

With nginx-lua server environment and Redis database framework provides efficient server architecture. Developers can shared code between the client and server.

-   [nginx](http://nginx.org) - nginx [engine x] is an HTTP server.
-   [ngx_lua](http://wiki.nginx.org/HttpLuaModule) - Embed the power of Lua into Nginx.
-   [redis](http://redis.io) - Redis is an open source, advanced key-value store.
