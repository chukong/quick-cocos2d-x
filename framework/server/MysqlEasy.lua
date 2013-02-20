
require("resty.mysql")

local MysqlEasy = class("MysqlEasy")

function MysqlEasy:ctor(config)
    self.db_ = nil
    local db, err = resty.mysql:new()
    if not db then
        ngx.say("failed to instantiate mysql: ", err)
        return
    end

    self.db_ = db

    local ok, err, errno, sqlstate = self.db_:connect(config)
    if not ok then
        ngx.say("mysql query error: ", err, ",", errno, ",", sqlstate)
        return
    end

    self.db_:query("SET NAMES 'utf8'")
end

function MysqlEasy:setTimeout(timeout)
    assert(self.db_ ~= nil, "Not connect to mysql")
    self.db_:set_timeout(timeout)
end

function MysqlEasy:close()
    assert(self.db_ ~= nil, "Not connect to mysql")
    self.db_:close()
end

function MysqlEasy:insert(tableName, params)
    assert(self.db_ ~= nil, "Not connect to mysql")
    local fieldNames = {}
    local fieldValues = {}

    for name, value in pairs(params) do
        fieldNames[#fieldNames + 1] = self:escapeName(name)
        fieldValues[#fieldValues + 1] = self:escapeValue(value)
    end

    local sql = format("INSERT INTO %s (%s) VALUES (%s)",
                       self:escapeName(tableName),
                       table.concat(fieldNames, ","),
                       table.concat(fieldValues, ","))

    -- ngx.say("SQL: " .. sql)
    local ok, err, errno, sqlstate = self.db_:query(sql)
    if not ok then
        ngx.say("mysql query error: ", err, ",", errno, ",", sqlstate)
    end
    return ok, err, errno, sqlstate
end

function MysqlEasy:update(tableName, params, where)
    assert(self.db_ ~= nil, "Not connect to mysql")
    local fields = {}
    local whereFields = {}

    for name, value in pairs(params) do
        fields[#fields + 1] = self:escapeName(name) .. "=".. self:escapeValue(value)
    end

    for name, value in pairs(where) do
        whereFields[#whereFields + 1] = self:escapeName(name) .. "=".. self:escapeValue(value)
    end

    local sql = format("UPDATE %s SET %s %s",
                       self:escapeName(tableName),
                       table.concat(fields, ","),
                       "WHERE " .. table.concat(whereFields, " AND "))

    -- ngx.say("SQL: " .. sql)

    local ok, err, errno, sqlstate = self.db_:query(sql)
    if not ok then
        ngx.say("mysql query error: ", err, ",", errno, ",", sqlstate)
    end
    return ok, err, errno, sqlstate
end


function MysqlEasy:escapeName(name)
    return string.format("`%s`", name)
end

function MysqlEasy:escapeValue(value)
    return ngx.quote_sql_str(value)
end

return MysqlEasy
