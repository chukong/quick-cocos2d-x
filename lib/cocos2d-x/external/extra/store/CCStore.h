
#ifndef  __CC_EXTENSION_CCSTORE_H_
#define  __CC_EXTENSION_CCSTORE_H_

#include "cocos2dx_extra.h"
#include "store/CCStoreProduct.h"
#include "store/CCStorePaymentTransaction.h"
#include "store/CCStoreTransactionObserver.h"
#include "store/CCStoreProductsRequestDelegate.h"

NS_CC_EXTRA_BEGIN

typedef bool CCStoreIsSandbox;

typedef std::map<const std::string, CCStorePaymentTransaction*> CCStorePaymentTransactions;
typedef CCStorePaymentTransactions::iterator                    CCStorePaymentTransactionsIterator;

class CCStore: public CCStoreTransactionObserver
#if CC_LUA_ENGINE_ENABLED > 0
, public CCStoreProductsRequestDelegate
#endif
{
public:
    static CCStore* sharedStore(void);
    static void purgeSharedStore(void);
    
    ~CCStore(void);
    
    void postInitWithTransactionObserver(CCStoreTransactionObserver* observer);
#if CC_LUA_ENGINE_ENABLED > 0
    void postInitWithTransactionListenerLua(cocos2d::LUA_FUNCTION listener);
#endif
    
    bool canMakePurchases(void);
    
    void loadProducts(CCArray* productsId, CCStoreProductsRequestDelegate* delegate);
#if CC_LUA_ENGINE_ENABLED > 0
    void loadProductsLua(cocos2d::LUA_TABLE __LUA_TABLE__, cocos2d::LUA_FUNCTION callback);
#endif
    void cancelLoadProducts(void);
    bool isProductLoaded(const char* productId);
    bool purchase(const char* productId);
    void restore(void);
    void finishTransaction(CCStorePaymentTransaction *transaction);
#if CC_LUA_ENGINE_ENABLED > 0
    void finishTransactionLua(const char* transactionIdentifier);
#endif

    CCStoreReceiptVerifyMode getReceiptVerifyMode(void);
    void setReceiptVerifyMode(CCStoreReceiptVerifyMode mode, CCStoreIsSandbox isSandbox = true);
    const char* getReceiptVerifyServerUrl(void);
    void setReceiptVerifyServerUrl(const char* url);
    
#pragma mark -
#pragma mark delegates
    
    virtual void transactionCompleted(CCStorePaymentTransaction* transaction);
    virtual void transactionFailed(CCStorePaymentTransaction* transaction);
    virtual void transactionRestored(CCStorePaymentTransaction* transaction);
    
#if CC_LUA_ENGINE_ENABLED > 0
    virtual void requestProductsCompleted(cocos2d::CCArray* products, cocos2d::CCArray* invalidProductsId = NULL);
    virtual void requestProductsFailed(int errorCode, const char* errorString);
#endif
    
private:
    CCStore(void)
    : m_observer(NULL)
#if CC_LUA_ENGINE_ENABLED > 0
    , m_listener(0)
    , m_loadProductsCallback(0)
#endif
    , m_isLoadProductsLuaNotCompleted(false)
    {
    }
    bool init(void);
    
    static CCStore*             s_sharedStore;
    CCStoreTransactionObserver* m_observer;
#if CC_LUA_ENGINE_ENABLED > 0
    cocos2d::LUA_FUNCTION       m_listener;
    cocos2d::LUA_FUNCTION       m_loadProductsCallback;
#endif
    bool                        m_isLoadProductsLuaNotCompleted;
    CCStorePaymentTransactions  m_transactions;
    
#if CC_LUA_ENGINE_ENABLED > 0
    void passCCStorePaymentTransactionToLuaListener(CCStorePaymentTransaction* transaction);
#endif
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCSTORE_H_
