# Upgrade to quick-cocos2d-x 2.2.3

SEARCH, REPLACE:

-   tonum(), checknumber()
-   tobool(), checkbool()
-   toint(), checkint()
-   totable(), checktable()

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

SEARCH:

~~~
node:registerScriptHandler(function(event)
    print(event)
end)
~~~

REPLACE:

~~~
node:addNodeEventListener(cc.NODE_EVENT, function(event)
    print(event.name)
end)
~~~

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
