
#include "network/CCHTTPRequest.h"
#include "network/CCHTTPRequest_impl.h"
#include "cocos2d.h"
#include <stdio.h>

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif

using namespace cocos2d;

NS_CC_EXTRA_BEGIN

CCHTTPRequest* CCHTTPRequest::createWithUrl(CCHTTPRequestDelegate* delegate,
                                            const char* url,
                                            CCHTTPRequestMethod method,
                                            bool isAutoReleaseOnFinish)
{
    CCHTTPRequest* request = new CCHTTPRequest(delegate, url, method, isAutoReleaseOnFinish);
    request->initHttpRequest();
    request->autorelease();
    if (isAutoReleaseOnFinish)
    {
        request->retain();
    }
    return request;
}

#if CC_LUA_ENGINE_ENABLED > 0
CCHTTPRequest* CCHTTPRequest::createWithUrlLua(cocos2d::LUA_FUNCTION listener,
                                               const char* url,
                                               CCHTTPRequestMethod method)
{
    CCHTTPRequest* request = new CCHTTPRequest(NULL, url, method, true);
    request->m_luaListener = listener;
    request->initHttpRequest();
    request->autorelease();
    request->retain();
    return request;
}
#endif

bool CCHTTPRequest::initHttpRequest(void)
{
    m_request = new CCHTTPRequest_impl(m_url.c_str(), m_method);
    return true;
}

CCHTTPRequest::~CCHTTPRequest(void)
{
    delete (CCHTTPRequest_impl*)m_request;
}

void CCHTTPRequest::addRequestHeader(const char* key, const char* value)
{
    if (key && value)
    {
        ((CCHTTPRequest_impl*)m_request)->addRequestHeader(key, value);
    }
}

void CCHTTPRequest::addPostValue(const char* key, const char* value)
{
    if (key && value)
    {
        ((CCHTTPRequest_impl*)m_request)->addPostValue(key, value);
    }
}

void CCHTTPRequest::setPostData(const char* data)
{
    if (data)
    {
        ((CCHTTPRequest_impl*)m_request)->setPostData(data);
    }
}

void CCHTTPRequest::setTimeout(float timeout)
{
    ((CCHTTPRequest_impl*)m_request)->setTimeout(timeout);
}

bool CCHTTPRequest::getIsInProgress(void)
{
    return ((CCHTTPRequest_impl*)m_request)->getIsInProgress();
}

void CCHTTPRequest::start(bool isCached)
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
    if (((CCHTTPRequest_impl*)m_request)->start())
    {
        CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
    }
}

void CCHTTPRequest::cancel(void)
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
    ((CCHTTPRequest_impl*)m_request)->cancel();
}

void CCHTTPRequest::clearDelegatesAndCancel(void)
{
    m_delegate = NULL;
    cancel();
}

int CCHTTPRequest::getResponseStatusCode(void)
{
    return ((CCHTTPRequest_impl*)m_request)->getResponseStatusCode();
}

const char* CCHTTPRequest::getResponseHeaders(void)
{
    return ((CCHTTPRequest_impl*)m_request)->getResponseHeaders().c_str();
}

const char* CCHTTPRequest::getResponseString(void)
{
    return ((CCHTTPRequest_impl*)m_request)->getResponseString().c_str();
}

const void* CCHTTPRequest::getResponseData(void)
{
    return ((CCHTTPRequest_impl*)m_request)->getResponseData();
}

cocos2d::LUA_STRING CCHTTPRequest::getResponseDataLua(void)
{
    
}

int CCHTTPRequest::getResponseDataLength()
{
    return ((CCHTTPRequest_impl*)m_request)->getResponseDataLength();
}

int CCHTTPRequest::saveResponseData(const char* filename)
{
    FILE *fp = fopen(filename, "wb");
    int writedBytes = 0;
    if (fp)
    {
        writedBytes = fwrite(((CCHTTPRequest_impl*)m_request)->getResponseData(),
                             ((CCHTTPRequest_impl*)m_request)->getResponseDataLength(),
                             1,
                             fp);
        fclose(fp);
    }
    return writedBytes;
}

CCHTTPRequestError  CCHTTPRequest::getErrorCode(void)
{
    return ((CCHTTPRequest_impl*)m_request)->getErrorCode();
}

const char* CCHTTPRequest::getErrorMessage(void)
{
    return ((CCHTTPRequest_impl*)m_request)->getErrorMessage();
}

void CCHTTPRequest::update(float dt)
{
    CCHTTPRequest_impl* request = (CCHTTPRequest_impl*)m_request;
    if (!request || !request->getIsInProgress())
    {
        CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
    }
    
    if (request->getIsCompleted())
    {
        if (m_delegate) m_delegate->requestFinished(this);
        
#if CC_LUA_ENGINE_ENABLED > 0
        
        if (m_luaListener)
        {
            cocos2d::CCLuaValueDict dict;
            dict["name"] = cocos2d::CCLuaValue::stringValue("completed");
            dict["request"] = cocos2d::CCLuaValue::ccobjectValue(this, "CCHTTPRequest");
            cocos2d::CCLuaStack *stack = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack();
            stack->clean();
            stack->pushCCLuaValueDict(dict);
            stack->executeFunctionByHandler(m_luaListener, 1);
        }
        
#endif
        
    }
    else if (request->getIsCancelled())
    {
        if (m_delegate) m_delegate->requestFailed(this);
        
#if CC_LUA_ENGINE_ENABLED > 0
        
        if (m_luaListener)
        {
            cocos2d::CCLuaValueDict dict;
            dict["name"] = cocos2d::CCLuaValue::stringValue("failed");
            dict["request"] = cocos2d::CCLuaValue::ccobjectValue(this, "CCHTTPRequest");
            cocos2d::CCLuaStack *stack = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack();
            stack->clean();
            stack->pushCCLuaValueDict(dict);
            stack->executeFunctionByHandler(m_luaListener, 1);
        }
        
#endif
        
    }
}

NS_CC_EXTRA_END
