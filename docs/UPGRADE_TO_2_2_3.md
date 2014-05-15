# quick-cocos2d-x 升级说明

本文档描述了升级 quick-cocos2d-x 需要的注意的事项和代码修改范例。

~


## 升级到 2.2.3 版

项目运行时，如果出现 [DEPRECATED] 相关信息，应该将这些已经作废的 API 替换为新 API。

已作废 API 请参考 framework/deprecated.lua 文件。

~


### 事件机制的改变：

-   registerScriptHandler()

	过时的用法:

	~~~ lua
	node:registerScriptHandler(function(event)
	    print(event)
	end)
	~~~

    新用法:

    ~~~ lua
    node:addNodeEventListener(cc.NODE_EVENT, function(event)
        print(event.name)
    end)
    ~~~

----

SEARCH:

~~~
api.EventProtocol.extend(target)
~~~

REPLACE:

~~~
cc(target):addComponent("components.behavior.EventProtocol"):exportMethods()
~~~

----

----

SEARCH:

~~~
node:registerScriptTouchHandler(function(event, x, y, prevX, prevY)
end)
~~~

REPLACE:

~~~
node:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
    print(event.name, event.x, event.y, event.prevX, event.prevY)
end)
~~~

----

SEARCH:

~~~
node:scheduleUpdate(function(dt)
    print(dt)
end)
~~~

REPLACE:

~~~
self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(dt)
    print(dt)
end)
self:scheduleUpdate()
~~~

