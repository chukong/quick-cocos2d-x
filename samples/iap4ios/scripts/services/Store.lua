
local Store = class("Store")

Store.LOAD_PRODUCTS_FINISHED    = "LOAD_PRODUCTS_FINISHED"
Store.TRANSACTION_PURCHASED     = "TRANSACTION_PURCHASED"
Store.TRANSACTION_RESTORED      = "TRANSACTION_RESTORED"
Store.TRANSACTION_FAILED        = "TRANSACTION_FAILED"
Store.TRANSACTION_UNKNOWN_ERROR = "TRANSACTION_UNKNOWN_ERROR"

function Store:ctor()
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()

    self.provider = require("framework.api.Store")
    self.provider.init(handler(self, self.transactionCallback))
    self.products = {}
end

function Store:canMakePurchases()
    return self.provider.canMakePurchases()
end

function Store:loadProducts(productsId)
    self.provider.loadProducts(productsId, function(event)
        self.products = {}
        for _, product in ipairs(event.products) do
            self.products[product.productIdentifier] = clone(product)
        end

        self:dispatchEvent({
            name = Store.LOAD_PRODUCTS_FINISHED,
            products = event.products,
            invalidProducts = event.invalidProducts
        })
    end)
end

function Store:getProductDetails(productId)
    local product = self.products[productId]
    if product then
        return clone(product)
    else
        return nil
    end
end

function Store:cancelLoadProducts()
    self.provider.cancelLoadProducts()
end

function Store:isProductLoaded(productId)
    return self.provider.isProductLoaded(productId)
end

function Store:purchaseProduct(productId)
    self.provider.purchase(productId)
end

function Store:transactionCallback(event)
    local transaction = event.transaction
    if transaction.state == "purchased" then
        print("Transaction succuessful!")
        print("productIdentifier", transaction.productIdentifier)
        print("quantity", transaction.quantity)
        print("transactionIdentifier", transaction.transactionIdentifier)
        print("date", os.date("%Y-%m-%d %H:%M:%S", transaction.date))
        print("receipt", transaction.receipt)
        self:dispatchEvent({
            name = Store.TRANSACTION_PURCHASED,
            transaction = transaction,
        })
    elseif  transaction.state == "restored" then
        print("Transaction restored (from previous session)")
        print("productIdentifier", transaction.productIdentifier)
        print("receipt", transaction.receipt)
        print("transactionIdentifier", transaction.identifier)
        print("date", transaction.date)
        print("originalReceipt", transaction.originalReceipt)
        print("originalTransactionIdentifier", transaction.originalIdentifier)
        print("originalDate", transaction.originalDate)
        self:dispatchEvent({
            name = Store.TRANSACTION_RESTORED,
            transaction = transaction,
        })
    elseif transaction.state == "failed" then
        print("Transaction failed")
        print("errorCode", transaction.errorCode)
        print("errorString", transaction.errorString)
        self:dispatchEvent({
            name = Store.TRANSACTION_FAILED,
            transaction = transaction,
        })
    else
        print("unknown event")
        self:dispatchEvent({
            name = Store.TRANSACTION_UNKNOWN_ERROR,
            transaction = transaction,
        })
    end

    -- Once we are done with a transaction, call this to tell the store
    -- we are done with the transaction.
    -- If you are providing downloadable content, wait to call this until
    -- after the download completes.
    self.provider.finishTransaction(transaction)
end

return Store
