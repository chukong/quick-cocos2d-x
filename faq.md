
## Q: How to declare classes

A: Use class(), in framework/shared/functions.lua

``` lua

local UserBase = class("UserBase")

function UserBase:ctor(username)
    self.username = username
end

function UserBase:sayHello()
    print(string.format("%s say: Hello", self.username))
end

----------------------------------------

-- Player inherited from UserBase
local Player = class("Player", UserBase)

function Player:ctor(username, level)
    Player.super.ctor(self, username)
    self.level = level
end

function Player:play()
    print(string.format("%s play", self.username))
end

----------------------------------------

local player1 = Player.new("dualface")
player1:sayHello()
player1:play()


```

----



