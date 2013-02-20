
require("resty.redis")

local RedisEasy = class("RedisEasy")

function RedisEasy:ctor(config)
    if type(config) ~= "table" then config = {} end
    config.timeout = config.timeout or 1000 -- 1 second
    config.host    = config.host or "127.0.0.1"
    config.port    = config.port or 6379
    self.config_ = config

    self.instance_ = resty.redis:new()
    self.instance_:set_timeout(self.config_.timeout)

    self.watch_ = false

    local function addCommand(cmd)
        self[cmd] = function(self, ...)
            local res, err = self.instance_[cmd](self.instance_, ...)
            if err then
                throw("redis error " .. tostring(err), ERROR_REDIS_FAILED)
            end
            return res
        end
    end

    for i, cmd in ipairs(resty.redis.commands) do
        addCommand(cmd)
    end

    addCommand("hmset")
    addCommand("init_pipeline")
    addCommand("cancel_pipeline")
    addCommand("commit_pipeline")
end

function RedisEasy:connect()
    local ok, err = self.instance_:connect(self.config_.host, self.config_.port)
    if not ok then
        throw("redis error " .. tostring(err), ERROR_REDIS_FAILED)
    end
end

function RedisEasy:loadModel(cls, id)
    local fields = self:hgetall(id)
    local properties = self.instance_:array_to_hash(fields)
    return cls.new(properties)
end

function RedisEasy:updateModel(model, id)
    local id = id or model:getId()
    local fields = self:hgetall(id)
    local properties = self.instance_:array_to_hash(fields)
    model:setProperties(properties)
end

function RedisEasy:loadModels(cls, ids)
    self:init_pipeline()
    for i, id in ipairs(ids) do
        self:hgetall(id)
    end
    local results = self:commit_pipeline()

    local objects = {}
    for i, fields in ipairs(results) do
        local properties = self.instance_:array_to_hash(fields)
        objects[#objects + 1] = cls.new(properties)
    end
    return objects
end

function RedisEasy:saveModel(target)
    return self:hmset(target:getId(), target:getProperties())
end

function RedisEasy:saveModels(set)
    self:multi()
    for i, target in pairs(set) do
        self:hmset(target:getId(), target:getProperties())
    end
    return self:exec()
end

return RedisEasy
