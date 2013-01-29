
#ifndef __CC_EXTENSION_CCHTTP_REQUEST_H_
#define __CC_EXTENSION_CCHTTP_REQUEST_H_

#include "cocos2d-x-extra.h"
#include "cocos2d.h"
#include "network/CCHTTPRequestDelegate.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif

NS_CC_EXTRA_BEGIN

typedef enum {
    CCHTTPRequestMethodGET = 0,
    CCHTTPRequestMethodPOST,
} CCHTTPRequestMethod;

typedef enum {
    CCHTTPRequestErrorNone = 0,
    CCHTTPRequestErrorConnectionFailure = 1,
    CCHTTPRequestErrorTimeout,
    CCHTTPRequestErrorAuthentication,
    CCHTTPRequestErrorCancelled,
    CCHTTPRequestErrorUnknown
} CCHTTPRequestError;

class CCHTTPRequest : public cocos2d::CCObject
{
public:
    static CCHTTPRequest* createWithUrl(CCHTTPRequestDelegate* delegate,
                                        const char* url,
                                        CCHTTPRequestMethod method = CCHTTPRequestMethodGET,
                                        bool isAutoReleaseOnFinish = true);
    
#if CC_LUA_ENGINE_ENABLED > 0
    static CCHTTPRequest* createWithUrlLua(cocos2d::LUA_FUNCTION listener,
                                           const char* url,
                                           CCHTTPRequestMethod method = CCHTTPRequestMethodGET);
#endif
    
    ~CCHTTPRequest(void);
    
    /** @brief Add a custom header to the request. */
    void addRequestHeader(const char* key, const char* value);

    /** @brief Add a POST variable to the request, POST only. */
    void addPostValue(const char* key, const char* value);
    
    /** @brief Set POST data to the request body, POST only. */
    void setPostData(const char* data);

    /** @brief Number of seconds to wait before timing out - default is 10. */
    void setTimeout(float timeout);
    
    /** @brief True when the request hasn't finished yet. */
    bool getIsInProgress(void);

    /** @brief Return CCHTTPRequestDelegate delegate. */
    CCHTTPRequestDelegate* getDelegate(void) {
        return m_delegate;
    }
    
    /** @brief Execute an asynchronous request
     
     If isCached set to false, it will force request not to be cached.        
     Setting isCache to false also appends a query string parameter, "_=[TIMESTAMP]", to the URL.
     */
    void start(bool isCached = false);
    
    /** @brief Cancel an asynchronous request. */
    void cancel(void);
    
    /** @brief Cancel an asynchronous request, clearing all delegates first. */
    void clearDelegatesAndCancel(void);
    
    /** @brief Return HTTP status code. */
    int getResponseStatusCode(void);
    
    /** @brief Return HTTP response headers. */
    const char* getResponseHeaders(void);
    
    /** @brief Returns the contents of the result. */
    const char* getResponseString(void);
    
    /** @brief Get response data. */
    const void* getResponseData(void);
    
#if CC_LUA_ENGINE_ENABLED > 0
    cocos2d::LUA_STRING getResponseDataLua(void);
#endif
    
    /** @brief Get response data length (bytes). */
    int getResponseDataLength(void);
    
    /** @brief Save response data to file. */
    int saveResponseData(const char* filename);
    
    /** @brief Get error code. */
    CCHTTPRequestError getErrorCode(void);
    
    /** @brief Get error message. */
    const char* getErrorMessage(void);

    /** @brief timer function. */
    virtual void update(float dt);

private:
    CCHTTPRequest(CCHTTPRequestDelegate* delegate,
                  const char* url,
                  CCHTTPRequestMethod method,
                  bool isAutoReleaseOnFinish)
    : m_delegate(delegate)
    , m_url(url ? url : "")
    , m_method(method)
    , m_request(NULL)
    , m_isAutoReleaseOnFinish(isAutoReleaseOnFinish)
    , m_errorCode(CCHTTPRequestErrorNone)
#if CC_LUA_ENGINE_ENABLED > 0
    , m_luaListener(0)
#endif
    {
    }
    bool initHttpRequest(void);

    CCHTTPRequestDelegate*  m_delegate;
    const std::string       m_url;
    CCHTTPRequestMethod     m_method;
    void*                   m_request;
    bool                    m_isAutoReleaseOnFinish;
    CCHTTPRequestError      m_errorCode;
    std::string             m_errorMessage;

#if CC_LUA_ENGINE_ENABLED > 0
    cocos2d::LUA_FUNCTION   m_luaListener;
#endif
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCHTTP_REQUEST_H_
