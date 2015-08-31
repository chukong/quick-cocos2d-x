
require("config")
require("framework.init")

local Store = require("services.Store")

-- define global module
game = {}

function game.startup()
    game.store = Store.new()
    game.store:addEventListener(Store.TRANSACTION_PURCHASED,
                                game.onTransactionPurchased)
    game.store:addEventListener(Store.TRANSACTION_FAILED,
                                game.onTransactionFailed)
    game.store:addEventListener(Store.TRANSACTION_UNKNOWN_ERROR,
                                game.onTransactionUnknownError)

    CCFileUtils:sharedFileUtils():addSearchPath("res/")
    game.enterMainScene()
end

function game.exit()
    os.exit()
end

function game.enterMainScene()
    display.replaceScene(require("scenes.MainScene").new(), "fade", 0.6, display.COLOR_WHITE)
end

function game.onTransactionPurchased(event)
    local transaction = event.transaction
    local productId = transaction.productIdentifier
    local product = game.store:getProductDetails(productId)
    local msg
    if product then
        msg = string.format("productId = %s\nquantity = %s\ntitle = %s\nprice = %s %s", productId, tostring(transaction.quantity), product.localizedTitle, product.price, product.priceLocale)
    else
        -- prev unfinished transaction
        msg = string.format("productId = %s\nquantity = %s", productId, tostring(transaction.quantity))
    end
    device.showAlert("IAP Purchased", msg, {"OK"})

    -- add Player's Coins at here
end

function game.onTransactionFailed(event)
    local transaction = event.transaction
    local msg = string.format("errorCode = %s\nerrorString = %s",
                              tostring(transaction.errorCode),
                              tostring(transaction.errorString))
    device.showAlert("IAP Purchased", msg, {"OK"})
end

function game.onTransactionUnknownError(event)
    device.showAlert("IAP Error", "Unknown error", {"OK"})
end
