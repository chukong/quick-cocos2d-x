
#include "platform/ios/CCStoreReceiptVerifyRequestIOS.h"

CCStoreReceiptVerifyRequestIOS* CCStoreReceiptVerifyRequestIOS::create(CCStoreIOS* store,
                                                                           SKPaymentTransaction* transaction,
                                                                           const char* url)
{
    CCStoreReceiptVerifyRequestIOS* handler = new CCStoreReceiptVerifyRequestIOS();
    handler->init(store, transaction, url);
    handler->autorelease();
    handler->retain();
    return handler;
}

bool CCStoreReceiptVerifyRequestIOS::init(CCStoreIOS* store,
                                            SKPaymentTransaction* transaction,
                                            const char* url)
{
    m_store = store;
    [m_store retain];
    m_transaction = transaction;
    [m_transaction retain];
    m_request = CCHTTPRequest::createWithUrl(this, url, kCCHTTPRequestMethodPOST);
    m_request->retain();
    return true;
}

CCStoreReceiptVerifyRequestIOS::~CCStoreReceiptVerifyRequestIOS(void)
{
    [m_transaction release];
    CC_SAFE_RELEASE(m_request);
    CCLOG("~~ delete CCStoreReceiptVerifyRequestIOS");
}

void CCStoreReceiptVerifyRequestIOS::requestFinished(CCHTTPRequest* request)
{
    [m_store verifyReceiptRequestFinished: this];
    [m_store release];
    release();
}

void CCStoreReceiptVerifyRequestIOS::requestFailed(CCHTTPRequest* request)
{
    [m_store verifyReceiptRequestFailed: this];
    [m_store release];
    release();
}
