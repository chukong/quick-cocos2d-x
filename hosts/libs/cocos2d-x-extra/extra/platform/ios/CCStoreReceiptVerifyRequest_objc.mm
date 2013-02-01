
#include "platform/ios/CCStoreReceiptVerifyRequest_objc.h"


CCStoreReceiptVerifyRequest_objc* CCStoreReceiptVerifyRequest_objc::create(CCStore_objc* store,
                                                                           SKPaymentTransaction* transaction,
                                                                           const char* url)
{
    CCStoreReceiptVerifyRequest_objc* handler = new CCStoreReceiptVerifyRequest_objc();
    handler->init(store, transaction, url);
    handler->autorelease();
    handler->retain();
    return handler;
}

bool CCStoreReceiptVerifyRequest_objc::init(CCStore_objc* store,
                                            SKPaymentTransaction* transaction,
                                            const char* url)
{
    m_store = store;
    [m_store retain];
    m_transaction = transaction;
    [m_transaction retain];
    m_request = CCHttpRequest::createWithUrl(this, url, CCHttpRequestMethodPOST);
    m_request->retain();
    return true;
}

CCStoreReceiptVerifyRequest_objc::~CCStoreReceiptVerifyRequest_objc(void)
{
    [m_transaction release];
    CC_SAFE_RELEASE(m_request);
    CCLOG("~~ delete CCStoreReceiptVerifyRequest_objc");
}

void CCStoreReceiptVerifyRequest_objc::requestFinished(CCHttpRequest* request)
{
    [m_store verifyReceiptRequestFinished: this];
    [m_store release];
    release();
}

void CCStoreReceiptVerifyRequest_objc::requestFailed(CCHttpRequest* request)
{
    [m_store verifyReceiptRequestFailed: this];
    [m_store release];
    release();
}
