
quick-cocos2d-x 是一个可以让您觉得“爽快”的 cocos2d-x 的扩展版。基于 cocos2d-x，完全的跨平台能力、优异的性能和可靠性。而 quick-cocos2d-x 在这一切的基础上，添加了完善的 Lua 脚本语言支持，让开发者可以使用 Lua 这种简单易用的脚本语言完成商业品质的移动游戏。

CODE LESS, PLAY MORE !

> [cocos2d-x](http://www.cocos2d-x.org) is a multi-platform 2D game engine in C++, based on cocos2d-iphone and licensed under MIT. Now this engine has been expanded to iOS, Android, Bada, BlackBerry, Marmalade and desktop operating systems like Linux, WindowsXP & Windows7.

<br />

## 快速开始

### 系统需求

-   最新版本 Xcode (当前为 4.6) 和最新的 iOS SDK (当前为 6.1)
-   Android SDK (2.2) 和 Android NDK (r8b, 不能使用其他版本)

### 下载

-   **最新版本**: [quick-cocos2d-x-20130509.zip](http://quick-x.com/downloads/quick-cocos2d-x-20130509.zip)
-   **中国大陆下载地址**: [quick-cocos2d-x-20130509.zip](http://17wanapp.cn/quickx/quick-cocos2d-x-20130509.zip)


### 运行模拟器

打开 quick-cocos2d-x/simulator/bin/mac/quick-x-player.app, 或者 quick-cocos2d-x/simulator/bin/win32/quick-x-player.exe

1.  选择菜单: File -> Open Project
2.  设置 Project Director 为 **quick-cocos2d-x/sample/CoinFlip**
3.  设置 Script File 为 **$WORKDIR/scripts/main.lua**

    ![](https://raw.github.com/dualface/quick-cocos2d-x/master/doc/img/RUN_SIMULATOR_WINDOWS_01.png)

4.  点击 "Open Project" 按钮.

![](https://raw.github.com/dualface/quick-cocos2d-x/master/doc/img/RUN_SIMULATOR_WINDOWS_02.png)


### 编译和创建新项目

-   [安装 Android SDK/NDK - Mac](https://github.com/dualface/quick-cocos2d-x/blob/master/doc/INSTALL_ANDROID_SDK_MAC.md)
-   [安装 Android SDK/NDK - Windows](https://github.com/dualface/quick-cocos2d-x/blob/master/doc/INSTALL_ANDROID_SDK_WINDOWS.md)
-   [从源代码编译 - Mac](https://github.com/dualface/quick-cocos2d-x/blob/master/doc/BUILD_FROM_SOURCE_MAC.md)
-   [从源代码编译 - Windows](https://github.com/dualface/quick-cocos2d-x/blob/master/doc/BUILD_FROM_SOURCE_WINDOWS.md)
-   [创建新项目](https://github.com/dualface/quick-cocos2d-x/blob/master/doc/CREATE_NEW_PROJECT.md)


### 文档

-   [API 文档](http://quick-x.com/docs/api/)
-   [开发者指南](http://quick-x.com/docs/manual/)

<br />

----

## 为什么选择 quick-cocos2d-x

在这个“以快致胜”的时代，生产力很大程度上决定了成败！

-   **Lua 是成熟、无风险的选择**: cocos2d-x 对 Lua 的支持已经很成熟，国内外多家大型开发商都在使用 cocos2d-x + Lua 开发游戏。而且 Lua 在游戏领域已经有十多年的实践使用，被各种大型端游所应用。所以可以找到各种 Lua 的开源项目来进一步降低开发成本。

-   **低门槛、高效率**: Lua 简单易用，了解任何一种语言的开发者都可以在一周内掌握。而且 quick-cocos2d-x 提供了一个全功能的，基于 Lua 语言的高层开发框架。这个框架可以极大程度降低游戏开发的门槛并提高开发效率。一个没有任何 C++ 知识的团队也能创建商业品质的移动游戏。

-   **出色的框架设计**: quick-cocos2d-x 由具备多年框架和 API 设计经验的资深开发者创建。之前我们创建的 FleaPHP、QeePHP 都是国内顶尖的 PHP 开发框架之一。今时今日，我们将多年来积累的经验带到了移动领域，为移动游戏开发提供了一流质量的开发框架支持。

-   **无痛升级**: 高层开发框架的引入，统一了底层 cocos2d-x 的 API，解决了 cocos2d-x 升级改进时对游戏开发和维护带来的影响。团队不再需要纠结是否升级，没有任何痛苦就可以获得最新版 cocos2d-x 带来的好处。quick-cocos2d-x 将会紧跟 cocos2d-x 的版本发布，并且尽力保证高层框架的 API 不发生破坏兼容性的变化。

-   **无限的扩展能力**: quick-cocos2d-x 准备了多种扩展，让开发者可以用 C++/Java/Objective-C 语言开发与设备操作系统、第三方平台相关的功能，并方便的集成到 Lua 脚本中。而且 quick-cocos2d-x 还附带了预先开发完成的第三方库，可以为游戏添加支付、分析、广告等服务。随着时间的流逝，这些扩展插件还在不断增加，并且全部以开源形式发布。

-   **增强的开发环境**: 在 Windows 和 Mac 环境下，quick-cocos2d-x 提供了更完善的模拟器，开发者只要一个执行文件就可以开始游戏的开发和测试。

-   **最快的脚本引擎**: Lua 是“最快”的脚本语言之一，而 quick-cocos2d-x 集成了 LuaJIT，在支持 JIT 的设备上，可以将 Lua 脚本编译为机器码执行，性能无以伦比。

-   **100% 开源**: cocos2d-x、Lua，以及 quick-cocos2d-x 都是 100% 开源的项目。这意味着更低的成本、自由修改的权利，以及快速发展的技术。

<br />

### 框架的主要特征:

-   display: creates scenes, display objects, animation ...
-   transition: moving, fades, creates animation programing easy ...
-   audio: play background music, effect sounds ...
-   ui: creates button, menu, label ...
-   luaoc: Lua call Objective-C, Objective-C call Lua ...
-   luaj: Lua call Java, Java call Lua ...
-   network: Asynchronous HTTP requests, JSON, check the network status ...
