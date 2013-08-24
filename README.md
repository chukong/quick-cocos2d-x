## CHINESE => [README_CN.md](README_CN.md)

quick-cocos2d-x is a **quick** framework, based cocos2d-x. Make mobile games in Lua.

**CODE LESS, PLAY MORE !**

> [cocos2d-x](http://www.cocos2d-x.org) is a multi-platform 2D game engine in C++, based on cocos2d-iphone and licensed under MIT. Now this engine has been expanded to iOS, Android, Bada, BlackBerry, Marmalade and desktop operating systems like Linux, WindowsXP & Windows7.

<br />

## Run Player

Open quick-cocos2d-x/player/bin/mac/quick-x-player.app, or quick-cocos2d-x/player/bin/win32/quick-x-player.exe

![](http://cn.quick-x.com/wp-content/uploads/2013/08/player_01.png)

1.  Select menu: File -> Open
2.  Set Project Directory to **quick-cocos2d-x/sample/coinflip**
3.  Set Script File to **scripts/main.lua**
4.  Set Screen Direction to **Portrait**
5.  Click "Open Project" button.

Get Started: 

-   quick-cocos2d-x official site: [quick-x.com](http://quick-x.com/)
-   chinese official site: [cn.quick-x.com](http://cn.quick-x.com/)


<br />

----

## Why quick-cocos2d-x

QUICK = SUCCESS !

-   **No risk**: cocos2d-x's Lua support already exists two years, mature, reliable, the choice of large companies.

-   **Full-featured framework**: Write the entire game using Lua, no C++ requirements.

-   **Native extensions**: Integration of third-party components, including Payment, Ad, Analysis. Lua-ObjectiveC and Lua-Java bridge make life easy.

-   **Enhanced Simulator**: Run the game from any directory, multiple resolution switching, debug console.

-   **100% FREE**: cocos2d-x, Lua, quick-cocos2d-x all is Open-Sources project. licensed under MIT.

<br />

### Framework main features:

-   display: creates scenes, display objects, animation ...
-   transition: moving, fades, creates animation programing easy ...
-   audio: play background music, effect sounds ...
-   ui: creates button, menu, label ...
-   luaoc: Lua call Objective-C, Objective-C call Lua ...
-   luaj: Lua call Java, Java call Lua ...
-   network: Asynchronous HTTP requests, JSON, check the network status ...

----

### Changes in quick-cocos2d-x

Common:

- refactoring CCPointArray
- add CCLinkPosition
- add CCShapeNode, CCCircleShape, CCRectShape, CCPolygonShape, CCPointShape
- add CCClippingRegionNode
- add CCGraySprite, and shader ShaderPositionTextureGray
- add CCZipFile
- CCScriptEngineProtocol:executeGlobalFunction() add parameter numArgs
- add CCFileUtils:isDirectoryExist()
- add CCFileUtils:getCachePath(), return Library/Caches on iOS, same as getWritablePath() on other platforms
- add CCFileUtils:setSearchRootPath()
- add CCFileUtils:setWritablePath(), for debug
- add CCFileUtils:setCachePath(), for debug
- fix CCLabelTTF render blur
- fix CCTouchScriptHandlerEntry will release twice lua reference, see [http://www.cocos2d-x.org/issues/2535]
- add CCNotificationCenter Lua support
- CCLuaEngine:executeLayerKeypadEvent() use "back", "menu" for keypad events
- add Lua global function CCLuaLoadChunksFromZIP()
- add Lua global function typen() for faster type check, and constants LUA\_TNIL, LUA\_TBOOLEAN, LUA\_TLIGHTUSERDATA, LUA\_TNUMBER, LUA\_TSTRING, LUA\_TTABLE, LUA\_TFUNCTION, LUA\_TUSERDATA, LUA\_TTHREAD
- add Lua global function CCLuaStackSnapshot, get Lua state snapshot
- upgrade LuaJIT to 2.0.2
- add LuaJavaBridge
- add LuaObjectiveCBridge
- add Chipmunk Lua support
- add CCArmature Lua support
- add AssetsManager Lua support
- add cocos2d-x-extra library
- remove CCHttpClient
- remove CCPhysicsDebugNode, CCPhysicsSprite
- remove spine support
- remove physics support from CCArmature

Mac only:
- refactoring Mac support

Windows only:
- refactoring Windows support
- compile CocosDenshion as UNICODE
- compile LuaJIT as static library

Android only:
- improved Lua loader for Android, support package.path
- on Samsung i9100, not use OpenSL, but limit simulataneous sound streams to 3
- fix CCLabelTTF crash on Android
- support Android NDK r9
- remove LocalStorageAndroid

