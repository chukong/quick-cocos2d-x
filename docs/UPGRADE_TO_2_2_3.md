# quick-cocos2d-x 升级说明

本文档描述了升级到 quick-cocos2d-x 2.2.3 需要的注意的事项和代码修改范例。

项目运行时，如果出现 [DEPRECATED] 相关信息，应该将这些已经作废的 API 替换为新 API。已作废 API 请参考 framework/deprecated.lua 文件。

~


### 事件机制的改变

-   registerScriptHandler(handler)

    过时的用法:

    ```lua
    node:registerScriptHandler(function(event)
        print(event)
    end)
    ```

    新用法:

    ```lua
    node:addNodeEventListener(cc.NODE_EVENT, function(event)
        -- event.name 的值是下列之一：
        -- enter 节点进入场景
        -- exit 节点退出场景
        -- cleanup 节点进行清理
        -- enterTransitionFinish 节点进入场景的变换完成
        -- exitTransitionStart 节点退出场景的变换开始
        print(event.name)
    end)
    ```

~


-   scheduleUpdate(handler)

    过时的用法：

    ```lua
    node:scheduleUpdate(function(dt)
        print(dt)
    end)
    ```

    新用法：

    ```lua
    self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(dt)
        -- dt 是上一帧到这一帧之间的间隔事件，通常为 60 分之一秒
        print(dt)
    end)
    self:scheduleUpdate()
    ```

~


-   registerScriptTouchHandler(handler)

    过时的用法：

    ```lua
    node:registerScriptTouchHandler(function(event, x, y)
    end)
    ```

    新用法:

    ```lua
    -- 设置触摸模式
    node:setTouchMode(cc.TOUCH_MODE_ONE_BY_ONE) -- 单点触摸
    -- 或者
    node:setTouchMode(cc.TOUCH_MODE_ALL_AT_ONCE) -- 多点触摸

    -- 是否启用触摸
    -- 默认值： false
    node:setTouchEnabled(true)

    -- 是否允许当前 node 和所有子 node 捕获触摸事件
    -- 默认值： true
    node:setTouchCaptureEnabled(true)

    -- 如果当前 node 响应了触摸，是否吞噬触摸事件（阻止事件继续传递）
    -- 默认值： true
    not:setTouchSwallowEnabled(true)

    -- 添加触摸事件处理函数
    node:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        -- event.phase 的值是：
        -- cc.NODE_TOUCH_TARGETING_PHASE

        -- event.mode 的值是下列之一：
        -- cc.TOUCH_MODE_ONE_BY_ONE 单点触摸
        -- cc.TOUCH_MODE_ALL_AT_ONCE 多点触摸

        -- event.name 的值是下列之一：
        -- began 触摸开始
        -- moved 触摸点移动
        -- ended 触摸结束
        -- cancelled 触摸被取消

        -- 如果是单点触摸：
        -- event.x, event.y 是触摸点位置
        -- event.prevX, event.prevY 是触摸点之前的位置

        -- 如果是多点触摸：
        -- event.points 包含了所有触摸点的信息
        -- event.points = {point, point, ...}
        -- 每一个触摸点的值包含：
        -- point.x, point.y 触摸点的当前位置
        -- point.prevX, point.prevY 触摸点之前的位置
        -- point.id 触摸点 id，用于确定触摸点的变化

        if event.name == "began" then
            -- 在单点触摸模式下：在触摸事件开始时，必须返回 true
            -- 返回 true 表示响应本次触摸事件，并且接收后续状态更新
            return true
        end
    end)

    -- 添加触摸事件捕获函数
    node:addNodeEventListener(cc.NODE_TOUCH_CAPTURE_EVENT, function(event)
        -- event.phase 的值是：
        -- cc.NODE_TOUCH_CAPTURING_PHASE

        -- event.mode 的值是下列之一：
        -- cc.TOUCH_MODE_ONE_BY_ONE 单点触摸
        -- cc.TOUCH_MODE_ALL_AT_ONCE 多点触摸

        -- event.name 的值是下列之一：
        -- began 触摸开始
        -- moved 触摸点移动
        -- ended 触摸结束
        -- cancelled 触摸被取消

        -- 如果是单点触摸：
        -- event.x, event.y 是触摸点位置
        -- event.prevX, event.prevY 是触摸点之前的位置

        -- 如果是多点触摸：
        -- event.points 包含了所有触摸点的信息
        -- event.points = {point, point, ...}
        -- 每一个触摸点的值包含：
        -- point.x, point.y 触摸点的当前位置
        -- point.prevX, point.prevY 触摸点之前的位置
        -- point.id 触摸点 id，用于确定触摸点的变化

        if event.name == "began" then
            -- 在单点触摸模式下：在触摸事件开始捕获时，必须返回 true
            -- 返回 true 表示要捕获本次触摸事件
            return true
        end
    end)
    ```

~


### 扩展功能的变化

-   api.EventProtocol.extend(target)

    过时的用法：

    ```lua
    api.EventProtocol.extend(target)
    ```

    新用法：

    ```lua
    cc(target)
        :addComponent("components.behavior.EventProtocol")
        :exportMethods()
    ```
