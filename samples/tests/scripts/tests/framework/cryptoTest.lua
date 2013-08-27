
local CryptoTestScene = game.createSceneClass("CryptoTestScene")

function CryptoTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "encryptXXTEA",
        "decryptXXTEA",
        "encodeBase64",
        "decodeBase64",
        "md5",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function CryptoTestScene:runTest(name)
    local m = self[name .. "Test"]
    m(self)
end

function CryptoTestScene:encryptXXTEATest()
    local p = "Hello"
    local k = "KEYKEY"
    printf("encryptXXTEATest: %s -> %s", p, bin2hex(crypto.encryptXXTEA(p, k)))
end

function CryptoTestScene:decryptXXTEATest()
    local p = "Hello"
    local k = "KEYKEY"
    local c = crypto.encryptXXTEA(p, k)
    printf("decryptXXTEATest: %s -> %s", bin2hex(c), crypto.decryptXXTEA(c, k))
end

function CryptoTestScene:encodeBase64Test()
    local p = "Hello"
    local c = crypto.encodeBase64(p)
    printf("encodeBase64Test: %s -> %s", p, c)
end

function CryptoTestScene:decodeBase64Test()
    local p = "Hello"
    local c = crypto.encodeBase64(p)
    printf("decodeBase64Test: %s -> %s", c, crypto.decodeBase64(c))
end

function CryptoTestScene:md5Test()
    local p = "Hello"
    printf("md5Test: %s -> %s", p, crypto.md5(p))
end


return CryptoTestScene
