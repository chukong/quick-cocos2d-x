
--[[--

This feature allows you to support In-App Purchases. Currently, only the Apple iTunes Store is supported. In the future, other store fronts may be added.

@module framework.client.api.Store

]]
local Store = {}

local store = __FRAMEWORK_GLOBALS__["api.Store"]

--[[--

Activates In-App Purchases.

Starts up the In-App Purchase engine and allows you to receive callbacks with the listener function you specify.

**Syntax:**

    framework.client.api.Store.init(listener)

**Example:**

    function transactionCallback(event)
        local transaction = event.transaction
        if transaction.state == "purchased" then
            print("Transaction succuessful!")
            print("productId", transaction.productId)
            print("quantity", transaction.quantity)
            print("transactionIdentifier", transaction.transactionIdentifier)
            print("date", os.date("%Y-%m-%d %H:%M:%S", transaction.date))
            print("receipt", transaction.receipt)
        elseif  transaction.state == "restored" then
            print("Transaction restored (from previous session)")
            print("productId", transaction.productId)
            print("receipt", transaction.receipt)
            print("transactionIdentifier", transaction.identifier)
            print("date", transaction.date)
            print("originalReceipt", transaction.originalReceipt)
            print("originalTransactionIdentifier", transaction.originalIdentifier)
            print("originalDate", transaction.originalDate)
        elseif transaction.state == "failed" then
            print("Transaction failed")
            print("errorCode", transaction.errorCode)
            print("errorString", transaction.errorString)
        else
            print("unknown event")
        end

        -- Once we are done with a transaction, call this to tell the store
        -- we are done with the transaction.
        -- If you are providing downloadable content, wait to call this until
        -- after the download completes.
        framework.client.api.Store.finishTransaction(transaction)
    end

    framework.client.api.Store.init(transactionCallback)

<br />

@tparam function listener
This is the listener that will handle transaction callback events.

@return Nothing.

]]
function Store.init(listener)
    if not CCStore then return end

    if store then
        echoError("[framework.client.api.Store] ERR, init() store already init")
        return false
    end

    if type(listener) ~= "function" then
        echoError("[framework.client.api.Store] ERR, init() invalid listener")
        return false
    end

    store = CCStore:sharedStore()
    __FRAMEWORK_GLOBALS__["api.Store"] = store    -- avoid gc
    return store:postInitWithTransactionListenerLua(listener)
end

--[[--

]]
function Store.getReceiptVerifyMode()
    if not CCStore then return end

    if not store then
        echoError("[framework.client.api.Store] ERR, getReceiptVerifyMode() store not init")
        return false
    end

    return store:getReceiptVerifyMode()
end

--[[--

]]
function Store.setReceiptVerifyMode(mode, isSandbox)
    if not CCStore then return end

    if not store then
        echoError("[framework.client.api.Store] ERR, setReceiptVerifyMode() store not init")
        return false
    end

    if type(mode) ~= "number"
        or (mode ~= CCStoreReceiptVerifyModeNone
            and mode ~= CCStoreReceiptVerifyModeDevice
            and mode ~= CCStoreReceiptVerifyModeServer) then
        echoError("[framework.client.api.Store] ERR, setReceiptVerifyMode() invalid mode")
        return false
    end

    if type(isSandbox) ~= "boolean" then isSandbox = true end
    store:setReceiptVerifyMode(mode, isSandbox)
end

--[[--

]]
function Store.getReceiptVerifyServerUrl()
    if not CCStore then return end

    if not store then
        echoError("[framework.client.api.Store] ERR, getReceiptVerifyServerUrl() store not init")
        return false
    end

    return store:getReceiptVerifyServerUrl()
end

--[[--

]]
function Store.setReceiptVerifyServerUrl(url)
    if not CCStore then return end

    if not store then
        echoError("[framework.client.api.Store] ERR, setReceiptVerifyServerUrl() store not init")
        return false
    end

    if type(url) ~= "string" then
        echoError("[framework.client.api.Store] ERR, setReceiptVerifyServerUrl() invalid url")
        return false
    end

    store:setReceiptVerifyServerUrl(url)
end

--[[--

Returns true if purchases are allowed, false otherwise.

**Syntax:**

    value = framework.client.api.Store.canMakePurchases

**Example:**

    if framework.client.api.Store.canMakePurchases() then
        framework.client.api.Store.purchase(productId)
    else
        print("Store purchases are not available")
    end

**Note:**

iOS devices have a setting that disables purchasing. A common case for this is to prevent children from accidentally purchasing things without parents' permission. Corona provides an API to check whether purchasing is possible. Use this preemptively to avoid having your users navigate through many purchase steps only to find out at the last step that purchasing is forbidden.

<br />

@return Returns true if purchases are allowed, false otherwise.

]]
function Store.canMakePurchases()
    if not CCStore then return false end

    if not store then
        echoError("[framework.client.api.Store] ERR, canMakePurchases() store not init")
        return false
    end

    return store:canMakePurchases()
end

--[[--

Retrieves information about items available for sale.
This includes the price of each item, a localized name, and a localized description.

**Syntax:**

    framework.client.api.Store.loadProducts(arrayOfProductIdentifiers, listener)

**Example:**

    function productCallback(event)
        print("showing valid products", #event.products)
        for i=1, #event.products do
            print(event.products[i].title)              -- string.
            print(event.products[i].description)        -- string.
            print(event.products[i].price)              -- number.
            print(event.products[i].localizedPrice)     -- string.
            print(event.products[i].productIdentifier)  -- string.
        end

        print("showing invalidProducts", #event.invalidProducts)
        for i=1, #event.invalidProducts do
            print(event.invalidProducts[i])
        end
    end

    local productsId = {
        "com.anscamobile.NewExampleInAppPurchase.ConsumableTier1",
        "com.anscamobile.NewExampleInAppPurchase.NonConsumableTier1",
        "com.anscamobile.NewExampleInAppPurchase.SubscriptionTier1",
        -- "bad.product.id",
    }

    framework.client.api.Store.loadProducts(productsId, productCallback)

<br />

@tparam table productsId
A Lua array with each element containing a string which is the product identifier of the in-app item you want to know about.

@tparam function listener
A callback function that is invoked when the store finishes retrieving the product information.

@return Nothing.

]]
function Store.loadProducts(productsId, listener)
    if not CCStore then return false end

    if not store then
        echoError("[framework.client.api.Store] ERR, loadProducts() store not init")
        return false
    end

    if type(listener) ~= "function" then
        echoError("[framework.client.api.Store] ERR, loadProducts() invalid listener")
        return false
    end

    if type(productsId) ~= "table" then
        echoError("[framework.client.api.Store] ERR, loadProducts() invalid productsId")
        return false
    end

    for i = 1, #productsId do
        if type(productsId[i]) ~= "string" then
            echoError("[framework.client.api.Store] ERR, loadProducts() invalid id[#%d] in productsId", i)
            return false
        end
    end

    store:loadProductsLua(productsId, listener)
    return true
end

--[[--

]]
function Store.cancelLoadProducts()
    if not store then
        echoError("[framework.client.api.Store] ERR, cancelLoadProducts() store not init")
        return false
    end

    store:cancelLoadProducts()
end

--[[--

]]
function Store.isProductLoaded(productId)
    if not CCStore then return false end

    if not store then
        echoError("[framework.client.api.Store] ERR, isProductLoaded() store not init")
        return false
    end

    return store:isProductLoaded(productId)
end

--[[--

Initiates a purchase transaction on a provided list of products.

This function will send out purchase requests to the store. The listener you specified in framework.client.api.Store.init() will be invoked when the store finishes processing the transaction.

**Syntax:**

    framework.client.api.Store.purchase(productId)

**Example:**

    framework.client.api.Store.purchase("com.framework.example.ConsumableTier1")

<br />

@param productId
A string which is the product identifier string.

@return Nothing.

]]
function Store.purchase(productId)
    if not CCStore then return end

    if not store then
        echoError("[framework.client.api.Store] ERR, purchase() store not init")
        return false
    end

    if type(productId) ~= "string" then
        echoError("[framework.client.api.Store] ERR, purchase() invalid productId")
        return false
    end

    return store:purchase(productId)
end

--[[--

Notifies the App Store that a transaction is complete.

After you finish handling a transaction, you must call framework.client.api.Store.finishTransaction() on the transaction object. If you don't do this, the App Store will think your transaction was interrupted and will attempt to resume it on the next application launch.

**Syntax:**

    framework.client.api.Store.finishTransaction(transaction)

@tparam table transaction
The transaction object belonging to the transaction you want to mark as finished.

@return Nothing.

]]
function Store.finishTransaction(transaction)
    if not CCStore then return false end

    if not store then
        echoError("[framework.client.api.Store] ERR, finishTransaction() store not init")
        return false
    end

    if type(transaction) ~= "table" or type(transaction.transactionIdentifier) ~= "string" then
        echoError("[framework.client.api.Store] ERR, finishTransaction() invalid transaction")
        return false
    end

    return store:finishTransactionLua(transaction.transactionIdentifier)
end

return Store
