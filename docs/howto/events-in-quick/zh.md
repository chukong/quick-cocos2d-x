# Quick 事件参考

Quick 修改后的 Cocos2d-x 提供一些底层事件支持。这些事件按照功能和用途分为：

-   节点事件 (cc.NODE_EVENT)
-   帧事件 (cc.NODE_ENTER_FRAME_EVENT)
-   触摸事件
-   键盘事件
-   重力感应事件
-   应用程序事件

### 节点事件 (cc.NODE_EVENT)

节点事件在一个 Node 对象进入、退出场景时触发。

```lua

local node = display.newNode()

node:addNodeEventListener(cc.NODE_EVENT, function(event)
    print(event.name)
end)

scene:addChild(node)

```


event 属性：

-   event.**name**: 指示节点事件类型，具有下列值：

    -   **enter**: Node 加入了正在运行的场景
    -   **exit**: Node 退出了正在运行的场景
    -   **enterTransitionFinish**: 进入一个新场景时的特效结束
    -   **exitTransitionStart**: 退出一个现有场景时的特效开始
    -   **cleanup**: Node 被完全清理并从内存删除时


下面的示例代码演示了 5 种事件类型的出现时机：

```lua

require("framework.init")

-- 首先创建一个空白场景
local sceneInit = display.newScene("sceneInit")
-- 进入该场景
display.replaceScene(sceneInit)

local function createTestScene(name)
    local scene = display.newScene(name)
    local node = display.newNode()
    node:addNodeEventListener(cc.NODE_EVENT, function(event)
        printf("node in scene [%s] NODE_EVENT: %s", name, event.name)
    end)
    scene:addChild(node)
    return scene
end

-- 等待 1.0 秒创建第一个测试场景
sceneInit:performWithDelay(function()
    local scene1 = createTestScene("scene1")
    display.replaceScene(scene1)

    -- 等待 1.0 秒创建第二个测试场景
    scene1:performWithDelay(function()
        print("--------")
        local scene2 = createTestScene("scene2")
        display.replaceScene(scene2)
    end, 1.0)
end, 1.0)

```

输出结果：

```

Cocos2d: [1.1140] node in scene [scene1] NODE_EVENT: enter
Cocos2d: [1.1140] node in scene [scene1] NODE_EVENT: enterTransitionFinish
Cocos2d: [2.1467] --------
Cocos2d: [2.1469] node in scene [scene1] NODE_EVENT: exitTransitionStart
Cocos2d: [2.1469] node in scene [scene1] NODE_EVENT: exit
Cocos2d: [2.1470] node in scene [scene1] NODE_EVENT: cleanup
Cocos2d: [2.1471] node in scene [scene2] NODE_EVENT: enter
Cocos2d: [2.1471] node in scene [scene2] NODE_EVENT: enterTransitionFinish

```

在切换场景时如果没有使用特效，那么事件出现的顺序如上。

但如果改动测试代码，将 `display.replaceScene(scene2)` 变成 `display.replaceScene(scene2, "random", 1.0)`，那么事件出现顺序变成：

```

Cocos2d: [1.1094] node in scene [scene1] NODE_EVENT: enter
Cocos2d: [1.1094] node in scene [scene1] NODE_EVENT: enterTransitionFinish
Cocos2d: [2.1258] --------
Cocos2d: [2.1337] node in scene [scene1] NODE_EVENT: exitTransitionStart
Cocos2d: [2.1338] node in scene [scene2] NODE_EVENT: enter
Cocos2d: [3.1752] node in scene [scene1] NODE_EVENT: exit
Cocos2d: [3.1753] node in scene [scene2] NODE_EVENT: enterTransitionFinish
Cocos2d: [3.1754] node in scene [scene1] NODE_EVENT: cleanup

```

造成这种区别的原因就是场景切换特效播放期间，会同时渲染两个场景，所以从事件上看，可以看到第二个场景的 `enter` 事件出现后，第一个场景的 `exit` 事件才出现。

因此，我们在使用节点事件时，不应该假定事件出现的顺序，而是根据特定事件采取特定的处理措施。

通常建议如下：

-   enter: 这里可以做一些场景初始化工作
-   exit: 如果场景切换使用了特效，可以在这里停止场景中的一些动画，避免切换场景的特效导致帧率下降
-   cleanup: 适合做清理工作

<br />

为了简化使用，Quick 为 cc.Node 封装了几个现成的方法，开发者如果从 Node（或继承类）创建自己的 Lua 类，那么可以直接覆盖这几个方法：

```lua

require("framework.init")

-- 定义一个自己的 cc.Node 继承类
local MyNode = class("MyNode", function(sceneName)
    local node = display.newNode()
    node.sceneName = sceneName
    return node
end)

function MyNode:onEnter()
    printf("node in scene [%s] method %s",
        self.sceneName,
        "onEnter")
end

function MyNode:onExit()
    printf("node in scene [%s] method %s",
        self.sceneName,
        "onExit")
end

function MyNode:onEnterTransitionFinish()
    printf("node in scene [%s] method %s",
        self.sceneName,
        "onEnterTransitionFinish")
end

function MyNode:onExitTransitionStart()
    printf("node in scene [%s] method %s",
        self.sceneName,
        "onExitTransitionStart")
end

function MyNode:onCleanup()
    printf("node in scene [%s] method %s",
        self.sceneName,
        "onCleanup")
end


-- 首先创建一个空白场景
local sceneInit = display.newScene("sceneInit")
-- 进入该场景
display.replaceScene(sceneInit)

local function createTestScene(name)
    local scene = display.newScene(name)
    local node = MyNode.new(name)
    node:setNodeEventEnabled(true) -- 启用节点事件，会调用节点预定义的方法
    scene:addChild(node)
    return scene
end

-- 等待 1.0 秒创建第一个测试场景
sceneInit:performWithDelay(function()
    local scene1 = createTestScene("scene1")
    display.replaceScene(scene1)

    -- 等待 1.0 秒创建第二个测试场景
    scene1:performWithDelay(function()
        print("--------")
        local scene2 = createTestScene("scene2")
        display.replaceScene(scene2, "random", 1.0)
    end, 1.0)
end, 1.0)

```

执行结果如下：

```

Cocos2d: [1.0988] node in scene [scene1] method onEnter
Cocos2d: [1.0988] node in scene [scene1] method onEnterTransitionFinish
Cocos2d: [2.1156] --------
Cocos2d: [2.1159] node in scene [scene1] method onExitTransitionStart
Cocos2d: [2.1160] node in scene [scene2] method onEnter
Cocos2d: [3.1488] node in scene [scene1] method onExit
Cocos2d: [3.1489] node in scene [scene2] method onEnterTransitionFinish
Cocos2d: [3.1489] node in scene [scene1] method onCleanup

```

效果和直接注册事件一样。两种方式让开发者可以根据实际需求灵活选择。

~


## 节点帧事件 (cc.NODE_ENTER_FRAME_EVENT)

注册该事件后，每一次刷新屏幕前（也就是前一帧和下一帧之间）都会触发事件。

```lua

require("framework.init")

local scene = display.newScene()

-- 注册事件
scene:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(dt)
    print(dt)
end)
-- 启用帧事件
scene:scheduleUpdate()

-- 0.5 秒后，停止帧事件
scene:performWithDelay(function()
    -- 禁用帧事件
    scene:unscheduleUpdate()
    print("STOP")

    -- 再等 0.5 秒，重新启用帧事件
    scene:performWithDelay(function()
        -- 再次启用帧事件
        scene:scheduleUpdate()
    end, 0.5)
end, 0.5)

display.replaceScene(scene)

```

运行时，屏幕上会不断输出上一帧和下一帧之间的时间间隔（通常为 1/60 秒），并在 0.5 时短暂暂停一下。

**注意**：一定要调用 `scheduleUpdate()` 后，帧事件才会触发。

~


**\[TO BE CONTINUED\]**

