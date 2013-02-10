
#import <StoreKit/StoreKit.h>
#import "platform/ios/CCStore_objc.h"

#include "CCObject.h"
#include "network/CCHttpRequestDelegate.h"
#include "network/CCHttpRequest.h"

USING_NS_CC_EXT;

class CCStoreReceiptVerifyRequest_objc : public cocos2d::CCObject, public CCHttpRequestDelegate
{
public:
    static CCStoreReceiptVerifyRequest_objc* create(CCStore_objc* store,
                                                    SKPaymentTransaction* transaction,
                                                    const char* url);
    ~CCStoreReceiptVerifyRequest_objc(void);
    
    CCHttpRequest* getRequest(void) {
        return m_request;
    }
    
    SKPaymentTransaction* getTransaction(void) {
        return m_transaction;
    }
    
    virtual void requestFinished(CCHttpRequest* request);
    virtual void requestFailed(CCHttpRequest* request);
    
private:
    bool init(CCStore_objc* store,
              SKPaymentTransaction* transaction,
              const char* url);
    
    CCStore_objc*           m_store;
    CCHttpRequest*          m_request;
    SKPaymentTransaction*   m_transaction;
};
