## Q: How to declare classes

A: Use class(), in framework/shared/functions.lua

``` lua

local UserBase = class("UserBase")

-- constructor
function UserBase:ctor(username)
    print("UserBase:ctor()")
    self.username = username
end

function UserBase:sayHello()
    print(string.format("%s say: Hello", self.username))
end

----------------------------------------

-- Player inherited from UserBase
local Player = class("Player", UserBase)

-- constructor
function Player:ctor(username, level)
    -- call super class method
    Player.super.ctor(self, username)
    print("Player:ctor()")
    
    self.level = level
end

function Player:play()
    print(string.format("%s play level %d", self.username, self.level))
end

----------------------------------------

local player1 = Player.new("dualface", 99)
player1:sayHello()
player1:play()

-- output:
--
-- UserBase:ctor()
-- Player:ctor()
-- dualface say: Hello
-- dualface play level 99


```

----

## Q: How to declare classes, inherited from C++ object

A: Return C++ object to class(), in framework/shared/functions.lua

``` lua

local MyNode = class("MyNode", function()
    -- create C++ object
    return display.newNode()
end)

function MyNode:moveTo(x, y)
    self:runAction(CCMoveTo:create(CCPoint(x, y)))
end

----------------------------------------

-- step 1: create new CCNode object (C++)
-- step 2: copy MyNode methods to object
-- step 3: call MyNode.ctor(), if exists
local node = MyNode.new()
node:moveTo(100, 100)


```

----

