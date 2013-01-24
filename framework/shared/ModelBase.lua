
--[[--

ModelBase 封装了一个模型对象的属性和行为。开发者应该从 ModelBase 继承自己的模型类，并添加模型的属性和行为。

~

## 对象的 ID

每一个对象都必须有一个唯一的 ID。

绝大多数情况下，用 id 属性存储对象的 ID。ModelBase 类的 idkey 设定用来指定模型用什么名称的属性存储对象的 ID。

~

## 对象的属性

对象具备一系列属性，每个属性的名字和类型，以及该属性的默认值用 ModelBase 类 schema 设定来指定。

-   setProperties() 会按照 schema 指定的名字和类型检查传入数组的值，并修改对象属性。
    如果值类型不对，或者值不存在，并且 schema 中没有为该属性指定默认值，将报告错误。

-   getProperties() 提取对象属性，然后构造为一个数组返回。

调用 setProperties() 时，传入数组的键名会追加一个下划线字符，然后再存入对象。例如：

    local properties = {
        title = "My First Post"
    }

    -- post 是一个 ModelBase 对象
    post:setProperties(properties)

    -- 数组中的 title 被存入了对象的 title_ 属性
    print(post.title_)

按照同样的规则，调用 getProperties() 读取对象的属性名都是附带下划线的，但最终返回的数组却是不带下划线的。
采用这种设计的目的是保护对象属性值，因此除非在对象自己的方法内，否则不应该直接访问对象的属性。

~

## 创建 ModelBase 继承类

ModelBase 并不能直接使用，开发者必须从 ModelBase 创建自己的继承类，例如下面的代码定义了一个基本的 User 模型：

    -- 定义 User 的构造函数
    local function ctor(self, properties)
    end

    -- 创建 User 类
    local ModelBase = require("framework.shared.ModelBase")
    local User = class("User", ctor, ModelBase)

    -- schema 指定对象有哪些属性，以及属性的类型和默认值
    User.schema = {
        id       = {"string"},      -- id 存储用户 ID
        username = {"string"},      -- username 存储用户名
        scores   = {"number", 0},   -- scores 存储用户的得分，默认为 0
    }

    -- fields 指定对象的哪些属性要存入数据库
    -- 如果未指定 fields，则对象的数据库操作被禁用
    User.fields = {"id", "username", "scores"}

~

## 在数据库中存取对象

ModelBase 并不提供数据库操作，下面假设使用 Redis 数据库来存取 User 对象：

    local properties = {
        id       = "user:1",
        username = "dualface",
    }
    local user = User.new(properties)

    -- 将对象保存到数据库
    redis:save(user)

    -- 从数据库读取对象
    local user = redis:load(User, "user:1")

~

## 访问对象属性

ModelBase 并不会为类自动添加 getter 和 setter 方法，所以开发者需要自行定义这些方法：

    function User:getUsername()
        return self.username_
    end

    function User:getScores()
        return self.scores_
    end

    function User:setScores(newScores)
        assert(type(newScores) == "number" and newScores >= 0,
               string.format("%s [User:setScores] Invalid scores %s", tostring(self), tostring(newScores)))
        self.scores_ = newScores
    end

虽然自行定义 getter 和 setter 增加一些工作量，但让开发者可以很容易的对属性访问做控制。
上面的代码中，由于没有定义 setUsername()，所以实现了针对 username 属性的“只读”效果。
同样，setScores() 还对传入的参数实行了有效性检查。

~

## 更灵活的设定对象属性

有时候只需要存储部分属性到数据库中，此时修改 fields 设定就可以达到目的。
问题在于不存入数据库的属性如果没有默认值，那么从数据库读取出来的对象，就是“残缺”的：

    local function ctor(self, properties)
    end

    local ModelBase = require("framework.shared.ModelBase")
    local Ship = class("Ship", ctor, ModelBase)

    Ship.schema = {
        id    = {"string"},
        model = {"string"},
        armor = {"number"},     -- 战舰的防御力
        speed = {"number"},     -- 战舰的速度
    }

    Ship.fields = {"id", "model"}

    function Ship:getModel()
        return self.model_
    end

    function Ship:getArmor()
        return self.armor_
    end

    function Ship:getSpeed()
        return self.speed_
    end

    -- 这里读取出来的 ship 对象，其 armor 和 speed 属性值都是无效的，因为数据库中没有包含这两个属性
    local ship = redis:load(Ship, "ship:1")
    print(ship:getArmor(), ship:getSpeed()) -- 将会输出 nil nil

这个问题需要开发者在自行处理：

    local ShipModelProperties = require("app.models.ShipModelProperties")

    local function setShopModelProperties(ship)
        -- 舰船的 armor 和 speed 属性保存在 ShipModelProperties 里
        -- 根据 model 属性从战舰属性表格中读取数据
        local shipProperties = ShipModelProperties.get(ship:getModel())
        -- 更新对象属性
        ship:setProperties(shipProperties)
    end

    -- 修改构造函数
    local function ctor(self, properties)
        setShopModelProperties(self)
    end

    -- 覆盖 setProperties() 方法
    function Ship:setProperties(properties, filter)
        -- 保存现在的 model_ 属性
        local model = self.model_
        -- 调用父类的 setProperties() 方法
        Ship.super.setProperties(properties, filter)

        -- 如果 model_ 属性有变化，则调用 setShopModelProperties() 更新舰船属性
        if model ~= self.model_ then
            setShopModelProperties(self)
        end
    end

~

## 将对象从服务端传递到客户端

对象是无法从服务端直接传递给客户端的，所以只能传递对象的属性，然后在客户端重建对象或更新已有对象。

假定使用 JSON 格式传递数据，那么从服务端返回对象属性的代码如下：

    local ship = Ship.load("ship:1")
    -- getProperties() 默认返回对象 fields 设定中指定的属性
    local properties = ship:getProperties()
    return json.encode({ship = properties})

客户端拿到服务端返回的数据后，用如下代码在客户端重建对象：

    local arr = json.decode(jsonString)
    local ship = Ship.new(arr.ship)

    -- 如果对象已经存在，只需更新属性
    ship:setProperties(arr.ship)

在一些情况下，需要过滤从服务端传递给客户端的数据。
例如从服务端传递用户的属性到客户端时，保存密码的“password”属性值应该过滤掉：

    local user = User.load("user:1")
    -- getProperties() 第二个参数用于指定要从结果中过滤掉哪些属性
    local properties = user:getProperties(nil, {"password"})
    retrun json.encode({user = properties})

~

## 使用插件

下面的代码创建了一个名为 UserPlugin 的插件，为 User 类增加了 login 方法和 increaseScores() 方法：

    -- 创建一个名为 UserPlugin 的插件类
    local UserPlugin = {}

    -- 在这个方法里可以修改 ModelBase 继承类的行为
    function UserPlugin.bind(theClass)

        -- 增加 login() 方法
        function theClass.login(username)
            if username == "dualface" then
                return theClass.load("user:1")
            else
                return nil
            end
        end

        -- 增加 increaseScores() 方法
        function theClass:increaseScores(amount)
            assert(type(amount) == "number" and amount >= 0,
               string.format("%s [UserPlugin:increaseScores] Invalid amount %s",
                             tostring(self), tostring(amount)))
            self.scores_ = self.scores_ + amount
        end

    end

定义了插件后，只需要修改 User 的定义，增加下列代码：

    -- 创建 User 类
    local User = class("User", ctor, ModelBase)

    -- 绑定插件到 User 类
    local UserPlugin = require("app.models.plugins.UserPlugin")
    UserPlugin.bind(User)

使用示例：

    local user = User.login("dualface")
    user:increaseScores(100)
    print(string.format("new scores: %d", user:getScores())

合理使用插件，可以将与“业务”无关的逻辑代码从模型类中分离出来。

]]

local json = require("framework.shared.json")

local ModelBase = class("ModelBase")
ModelBase.idkey = "id"
ModelBase.schema = {
    id = {"string"}
}
ModelBase.fields = {"id"}

local function filterProperties(properties, filter)
    for i, field in ipairs(filter) do
        properties[field] = nil
    end
end

function ModelBase:ctor(properties)
    self.isModelBase_ = true
    if type(properties) ~= "table" then properties = {} end
    self:setProperties(properties)
end

--[[--

返回对象的 ID 值。

**Returns:**

-   ID 值

]]
function ModelBase:getId()
    local id = self[self.class.idkey .. "_"]
    assert(id ~= nil, string.format("%s [%s:getId()] Invalid id", tostring(self), self.class.classname))
    return id
end

--[[--

确定对象是否设置了有效的 Id。

]]
function ModelBase:isValidId()
    local propname = self.class.idkey .. "_"
    local id = self[propname]
    return type(id) == "string" and id ~= ""
end

--[[--

修改对象的属性。

**Parameters:**

-   properties: 包含属性值的数组

]]
function ModelBase:setProperties(properties)
    assert(type(properties) == "table", "Invalid properties")
           -- string.format("%s [%s:setProperties()] Invalid properties", tostring(self), self.class.classname))

    for field, schema in pairs(self.class.schema) do
        local typ, def = unpack(schema)
        local propname = field .. "_"

        local val = properties[field] or def
        if val ~= nil then
            if typ == "number" then val = tonumber(val) end
            assert(type(val) == typ,
                   string.format("%s [%s:setProperties()] Type mismatch, %s expected %s, actual is %s",
                                 tostring(self), self.class.classname, field, typ, type(val)))
            self[propname] = val
        end
    end
end

--[[--

取得对象的属性值。

**Parameters:**

-   fields: 要取得哪些属性的值，如果未指定该参数，则返回 fields 中设定的属性
-   filter: 要从结果中过滤掉哪些属性，如果未指定则不过滤

**Returns:**

-   包含属性值的数组

]]
function ModelBase:getProperties(fields, filter)
    local schema = self.class.schema
    if type(fields) ~= "table" then fields = self.class.fields end

    local properties = {}
    for i, field in ipairs(fields) do
        local propname = field .. "_"
        local typ = schema[field][1]
        local val = self[propname]
        assert(type(val) == typ,
               string.format("%s [%s:getProperties()] Type mismatch, %s expected %s, actual is %s",
                                 tostring(self), self.class.classname, field, typ, type(val)))
        properties[field] = val
    end

    if type(filter) == "table" then
        filterProperties(properties, filter)
    end

    return properties
end

return ModelBase
