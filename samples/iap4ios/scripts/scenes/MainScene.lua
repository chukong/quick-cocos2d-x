
local Store = require("services.Store")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    self.busy = false

    local label = ui.newTTFLabelMenuItem({
        text = "Load Products from Apple IAP Server",
        align = ui.TEXT_ALIGN_CENTER,
        x = display.cx,
        y = display.cy,
        listener = handler(self, self.onLoadProductsClicked),
    })

    self.menu = ui.newMenu({label})
    self:addChild(self.menu)

    self.storeHandles = {}

    self.storeHandles[Store.LOAD_PRODUCTS_FINISHED] = game.store:addEventListener(Store.LOAD_PRODUCTS_FINISHED, handler(self, self.onLoadProductsFinished))
    self.storeHandles[Store.TRANSACTION_PURCHASED] = game.store:addEventListener(Store.TRANSACTION_PURCHASED, handler(self, self.onTransactionPurchased))
    self.storeHandles[Store.TRANSACTION_FAILED] = game.store:addEventListener(Store.TRANSACTION_FAILED, handler(self, self.onTransactionFailed))
    self.storeHandles[Store.TRANSACTION_UNKNOWN_ERROR] = game.store:addEventListener(Store.TRANSACTION_UNKNOWN_ERROR, handler(self, self.onTransactionFailed))
end

function MainScene:onLoadProductsClicked()
    if self.busy then return end

    if not game.store:canMakePurchases() then
        device.showAlert("IAP Error", "canMakePurchases() == false", {"Please check project config"})
        return
    end

    self.busy = true
    print("REQUEST LOAD PRODUCTS")
    device.showActivityIndicator()
    game.store:loadProducts(STORE_PRODUCTS_ID)
end

function MainScene:onLoadProductsFinished(event)
    dump(event.products, "products")

    self.menu:removeSelf()
    self.menu = nil

    device.hideActivityIndicator()
    device.showAlert("IAP OK", "Load products success", "OK")
    self.busy = false

    local items = {}
    local y = display.cy + 40 * (#event.products / 2)
    for _, product in ipairs(event.products) do
        items[#items + 1] = ui.newTTFLabelMenuItem({
            text = string.format("Buy \"%s\" with \"%s %s\"", product.localizedTitle, product.price, product.priceLocale),
            align = ui.TEXT_ALIGN_CENTER,
            x = display.cx,
            y = y,
            listener = function()
                return self:onPurchaseClicked(product.productIdentifier)
            end,
        })

        y = y - 40
    end

    self.menu = ui.newMenu(items)
    self:addChild(self.menu)
end

function MainScene:onPurchaseClicked(productId)
    if self.busy then return end

    self.busy = true
    device.showActivityIndicator()
    game.store:purchaseProduct(productId)
end

function MainScene:onTransactionPurchased(event)
    self.busy = false
    device.hideActivityIndicator()
end

function MainScene:onTransactionFailed(event)
    self.busy = false
    device.hideActivityIndicator()
end

function MainScene:onEnter()
end

function MainScene:onExit()
    for eventName, handle in pairs(self.storeHandles) do
        game.store:removeEventListener(eventName, handle)
    end
end

return MainScene
