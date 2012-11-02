
--[[--

Session 用于在服务端保持一个会话状态。

在调用 Session:start() 和 Session:save() 之后，服务端会保存一组键值。
在处理客户端的后续请求时，只要客户端提供了 SessionId，服务端就可以通过 SessionId 获得这一组键值。

会话状态可以用来保存跨越多个请求的状态，减少客户端和服务端之间需要传递的数据，并且更好的保护用户的敏感信息。


### 关于 SessionId

SessionId 用于唯一标示一个存储在服务端的会话数据。

**创建 SessionId 的算法**

-   取服务器当前时间
-   取 4 位随机数
-   取当前用户 ID
-   时间 + 随机数 + 种子，求 MD5 得到 SessionId

**Session 的存储和有效期**

-   首次使用新 SessionId 调用 Session:start() 及 Session:save() 后，
    一组以 SessionId 为键名的键值会被保存在服务端，并设定一个有效期；
-   在下一次使用已有 SessionId 调用 Session:start() 时，这组键值会被读取出来放入 session 对象；
-   再次调用 Session:save() 或 Session:refresh() 会自动更新 session 的有效期。
-   如果调用 Session:destroy()，session 对象中的值和存储在服务端的键值会被立即删除。

**SessionId 的安全性**

-   目前简化实现，SessionId 的传输和存储没有进行加密操作。

]]

local Session = class("Session")

Session.PREFIX    = "sess:"
Session.LIFETIME  = 60 * 60   -- 1 hour

function Session:ctor(app)
    self.app  = app
    self.keys = {}
    self.sid  = nil
    self.key  = "sess:"
end

function Session:saveId()
    return Session.PREFIX .. self.sid
end

--[[--

生成 SessionId

**Parameters:**

-   seed: 用于生成 SessionId 的种子

**Returns:**

-   新生成的 SessionId

]]
function Session:makeSessionId(seed)
    local time = ngx.time()
    math.randomseed(time)
    local rand = math.random(1000, 9999)
    return ngx.md5(string.format("%d%s%d", time, tostring(seed), rand))
end

--[[--

验证 SessionId 是否是有效

**Parameters:**

-   sid: 要验证的 SessionId

**Returns:**

-   验证通过: true
-   验证失败: false

]]
function Session:validateSessionId(sid)
    if (string.len(sid) ~= 32) then return false end
    if (ngx.re.match(sid, "[^a-f0-9]")) then return false end
    return true
end

--[[--

启动 session，如果失败返回 Error

**Parameters:**

-   sid: SessionId，如果未提供将自动生成一个

**Returns:**

-   成功: 无
-   失败: 返回 Error

]]
function Session:start(sid)
    if type(sid) ~= "string" then
        sid = Session:makeSessionId(math.random(100000, 999999))
    elseif not Session:validateSessionId(sid) then
        throw("ERROR_INVALID_SESSION_ID", ERROR_INVALID_SESSION_ID)
    end

    self.sid = sid

    local redis = self.app:redis()
    local value = redis:get(self:saveId())
    if value ~= ngx.null then
        self.keys = json.decode(value)
    end
    if type(self.keys) ~= "table" then
        self.keys = {}
    end
end

--[[--

获得 SessionId

**Returns:**

-   SessionId

]]
function Session:getSessionId()
    return self.sid
end

--[[--

获取指定的键值

**Parameters:**

-   key: 键名

**Returns:**

-   键值

]]
function Session:get(key)
    return clone(self.keys[key])
end

--[[--

获取所有键值

**Returns:**

-   包含所有键值的数组

]]
function Session:getAll()
    return clone(self.keys)
end

--[[--

设定键值

**Parameters:**

-   key: 键名
-   value: 键值

]]
function Session:set(key, value)
    self.keys[key] = value
end

--[[--

删除 session

]]
function Session:destroy()
    if self.sid then
        local redis = self.app:redis()
        redis:del(self:saveId())
    end
    self.keys = {}
    self.sid = nil
end

--[[--

刷新 session 过期时间

]]
function Session:refresh()
    if not self.sid then return end
    local redis = self.app:redis()
    redis:expire(self:saveId(), Session.LIFETIME)
end

--[[--

保存 session

**Returns:**

-   成功: nil
-   失败: Error

]]
function Session:save()
    if not self.sid then return end
    local str = json.encode(self.keys)
    local redis = self.app:redis()
    redis:setex(self:saveId(), Session.LIFETIME, str)
end

return Session
