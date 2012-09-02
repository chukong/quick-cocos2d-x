
基于 cocos2d-x 快速游戏引擎

## 主要特征

-   **使用 Lua 脚本语言编写游戏**: Lua 语言简单易学，运行快速，完全不需要学习 C++ 等语言
-   **强化的模拟器**: 直接从模拟器切换不同分辨率，方便调试游戏在不同设备上的表现；控制台窗口可以输出各种调试信息；在错误发生时，显示完整的错误状态和调用堆栈，显著降低开发成本。
-   **全功能开发框架**: 整个游戏可以 100% 使用 Lua 编写，OpenFeint/GameCenter/IAP 等功能轻松集成。
-   **自适应各种分辨率**: 开发框架提供的机制让开发者可以一次搞定各种尺寸的屏幕，省时又省力。

~

## 以十倍速度开发游戏

Code less, play more !

C++ 代码：

``` C++
CCScene* HelloWorld::scene(void)
{
    CCScene* scene = CCScene::create();

    CCSprite* pImg = CCSprite::create("hello.png");
    pImg:setPosition(100, 100)
    scene->addChild(pImg);

    return scene
}
```

同等功能的 Lua 代码：

``` Lua
local scene = display.newScene("HelloWorld")
display.newImage(scene, "hello.png", 100, 100)
```

~

## 全功能开发框架

主要功能模块：

-   display: 创建和切换场景、创建 sprite 和动画、载入 sprites sheetscene ...
-   transition: 移动、旋转、淡入淡出，cocos2d-x 中的各种 action 都可以一行代码替代 ...
-   scheduler: 设置计时器、延迟调用、回调函数 ...
-   audio：播放背景音乐和音效、切换音乐 ...
-   network：异步 HTTP 请求、JSON、检查网络状态 ...
-   ui: 创建标签、按钮、菜单，以及各各种控件 ...
-   GameNetwork: 集成 OpenFeint (Gree Platform)、GameCenter ...
-   Store: 集成 IAP、收据验证 ...
-   GameState: 游戏状态存档，并支持加密和验证操作 ...

这个框架包含近百个 API，提供了开发游戏需要的基本功能。即便完全不懂 C++，也可以开发出高质量的手机游戏。

~

## 服务端支持

配合 nginx-lua 服务器环境和 Redis 数据库，框架提供了高效实用的服务端架构。开发者不但可以用同一种语言开发客户端和服务端程序，还能在客户端和服务端共享游戏逻辑代码。

~

