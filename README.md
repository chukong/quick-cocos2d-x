
## ENGLISH README ==> README_en.md ##

quick-cocos2d-x 是一个可以让您觉得“爽快”的 cocos2d-x 的扩展版。基于 cocos2d-x，完全的跨平台能力、优异的性能和可靠性。而 quick-cocos2d-x 在这一切的基础上，添加了完善的 Lua 脚本语言支持，让开发者可以使用 Lua 这种简单易用的脚本语言完成商业品质的移动游戏。

## 为什么要选择 quick-cocos2d-x

在这个“以快致胜”的时代，生产力很大程度上决定了成败！

-   **Lua 是成熟、无风险的选择**: cocos2d-x 对 Lua 的支持已经很成熟，国内外多家大型开发商都在使用 cocos2d-x + Lua 开发游戏。而且 Lua 在游戏领域已经有十多年的实践使用，被各种大型端游所应用。所以可以找到各种 Lua 的开源项目来进一步降低开发成本。

-   **低门槛、高效率**: Lua 简单易用，了解任何一种语言的开发者都可以在一周内掌握。而且 quick-cocos2d-x 提供了一个全功能的，基于 Lua 语言的高层开发框架。这个框架可以极大程度降低游戏开发的门槛并提高开发效率。一个没有任何 C++ 知识的团队也能创建商业品质的移动游戏。

-   **出色的框架设计**: quick-cocos2d-x 由具备多年框架和 API 设计经验的资深开发者创建。之前我们创建的 FleaPHP、QeePHP 都是国内顶尖的 PHP 开发框架之一。今时今日，我们将多年来积累的经验带到了移动领域，为移动游戏开发提供了一流质量的开发框架支持。

-   **无痛升级**: 高层开发框架的引入，统一了底层 cocos2d-x 的 API，解决了 cocos2d-x 升级改进时对游戏开发和维护带来的影响。团队不再需要纠结是否升级，没有任何痛苦就可以获得最新版 cocos2d-x 带来的好处。quick-cocos2d-x 将会紧跟 cocos2d-x 的版本发布，并且尽力保证高层框架的 API 不发生破坏兼容性的变化。

-   **无限的扩展能力**: quick-cocos2d-x 准备了多种扩展，让开发者可以用 C++/Java/Objective-C 语言开发与设备操作系统、第三方平台相关的功能，并方便的集成到 Lua 脚本中。而且 quick-cocos2d-x 还附带了预先开发完成的第三方库，可以为游戏添加支付、分析、广告等服务。随着时间的流逝，这些扩展插件还在不断增加，并且全部以开源形式发布。

-   **增强的开发环境**: 在 Windows 和 Mac 环境下，quick-cocos2d-x 提供了更完善的模拟器，开发者只要一个执行文件就可以开始游戏的开发和测试。

-   **最快的脚本引擎**: Lua 是“最快”的脚本语言之一，而 quick-cocos2d-x 集成了 LuaJIT，在支持 JIT 的设备上，可以将 Lua 脚本编译为机器码执行，性能无以伦比。

-   **100% 开源**: cocos2d-x、Lua，以及 quick-cocos2d-x 都是 100% 开源的项目。这意味着更低的成本、自由修改的权利，以及快速发展的技术。

> [cocos2d-x](http://www.cocos2d-x.org) is a multi-platform 2D game engine in C++, based on cocos2d-iphone and licensed under MIT. Now this engine has been expanded to iOS, Android, Bada, BlackBerry, Marmalade and desktop operating systems like Linux, WindowsXP & Windows7.

<br />


## 快速开始

**1. Get sources from Github.com**

    git clone git://github.com/dualface/quick-cocos2d-x.git
    cd quick-cocos2d-x
    git submodule init
    git submodule update

Update sources:

    git pull
    git submodule update

<br />

**2. Open Xcode Perferences, add Source Trees:**

![Add Source Trees](http://dualface.github.com/quick-cocos2d-x/images/AddSourceTrees.png)

<br />

**3. Open samples/CoinFlip/proj.ios project, try it!**

**4. Read documents**

API Documents: [http://dualface.github.com/quick-cocos2d-x/docs/framework/index.html](http://dualface.github.com/quick-cocos2d-x/docs/framework/index.html)

<br />


## 框架主要功能模块介绍

<br />


## 文档

-   创建项目：工程、目录结构、骨架文件
-   编译项目：将 Lua 文件编译到执行文件中
-   发布项目

<br />


## 与 cocos2d-x 的差异

<br />


## 版本发布与分支维护

<br />



## 修订记录

<br />

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

<br />

## Lua running on the server, share code between client and server

With nginx-lua server environment and Redis database framework provides efficient server architecture. Developers can shared code between the client and server.

-   [nginx](http://nginx.org) - nginx [engine x] is an HTTP server.
-   [ngx_lua](http://wiki.nginx.org/HttpLuaModule) - Embed the power of Lua into Nginx.
-   [redis](http://redis.io) - Redis is an open source, advanced key-value store.
