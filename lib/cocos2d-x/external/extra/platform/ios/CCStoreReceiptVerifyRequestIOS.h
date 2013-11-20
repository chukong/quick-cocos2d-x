
#import <StoreKit/StoreKit.h>
#import "platform/ios/CCStoreIOS.h"

#include "cocoa/CCObject.h"
#include "network/CCHTTPRequestDelegate.h"
#include "network/CCHTTPRequest.h"

USING_NS_CC_EXTRA;

class CCStoreReceiptVerifyRequestIOS : public cocos2d::CCObject, public CCHTTPRequestDelegate
{
public:
    static CCStoreReceiptVerifyRequestIOS* create(CCStoreIOS* store,
                                                  SKPaymentTransaction* transaction,
                                                  const char* url);
    ~CCStoreReceiptVerifyRequestIOS(void);

    CCHTTPRequest* getRequest(void)
    {
        return m_request;
    }

    SKPaymentTransaction* getTransaction(void)
    {
        return m_transaction;
    }

    virtual void requestFinished(CCHTTPRequest* request);
    virtual void requestFailed(CCHTTPRequest* request);

private:
    bool init(CCStoreIOS* store,
              SKPaymentTransaction* transaction,
              const char* url);

    CCStoreIOS*             m_store;
    CCHTTPRequest*          m_request;
    SKPaymentTransaction*   m_transaction;
};
