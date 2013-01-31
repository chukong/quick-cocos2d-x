
#ifndef __CC_HTTP_REQUEST_H_
#define __CC_HTTP_REQUEST_H_

#include "cocos2d-x-extra.h"
#include "cocos2d.h"
#include "network/CCHTTPRequestDelegate.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif

#ifdef _WINDOWS_
#include <Windows.h>
#else
#include <pthread.h>
#endif

#include <vector>
#include <map>
#include "curl/curl.h"

using namespace std;
USING_NS_CC;

NS_CC_EXTRA_BEGIN

#define kCCHTTPRequestMethodGET  0
#define kCCHTTPRequestMethodPOST 1

#define kCCHTTPRequestStateIdle       0
#define kCCHTTPRequestStateInProgress 1
#define kCCHTTPRequestStateCompleted  2
#define kCCHTTPRequestStateCancelled  3
#define kCCHTTPRequestStateCleared    4

#define kCCHTTPRequestErrorNone              0
#define kCCHTTPRequestErrorConnectionFailure 1
#define kCCHTTPRequestErrorTimeout           2
#define kCCHTTPRequestErrorAuthentication    3
#define kCCHTTPRequestErrorCancelled         4
#define kCCHTTPRequestErrorUnknown           5

class CCHTTPRequest : public CCObject
{
public:
    static CCHTTPRequest* createWithUrl(CCHTTPRequestDelegate* delegate,
                                        const char* url,
                                        int method = kCCHTTPRequestMethodGET,
                                        bool isAutoReleaseOnFinish = true);
    
#if CC_LUA_ENGINE_ENABLED > 0
    static CCHTTPRequest* createWithUrlLua(LUA_FUNCTION listener,
                                           const char* url,
                                           int method = kCCHTTPRequestMethodGET);
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
    int getState(void) {
        return m_state;
    }
    
    /** @brief Return CCHTTPRequestDelegate delegate. */
    CCHTTPRequestDelegate* getDelegate(void) {
        return m_delegate;
    }
    
    /** @brief Execute an asynchronous request
     
     If isCached set to false, it will force request not to be cached.        
     Setting isCache to false also appends a query string parameter, "_=[TIMESTAMP]", to the URL.
     */
    void start(void);
    
    /** @brief Cancel an asynchronous request. */
    void cancel(void);
    
    /** @brief Cancel an asynchronous request, clearing all delegates first. */
    void clearDelegatesAndCancel(void);
    
    /** @brief Return HTTP status code. */
    int getResponseStatusCode(void) {
        CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
        return m_responseCode;
    }
    
    /** @brief Return HTTP response headers. */
    const char* getResponseHeaders(void);
    
    /** @brief Returns the contents of the result. */
    const char* getResponseString(void);
    
    /** @brief Get response data. */
    const void* getResponseData(void);
    
#if CC_LUA_ENGINE_ENABLED > 0
    LUA_STRING getResponseDataLua(void);
#endif
    
    /** @brief Get response data length (bytes). */
    int getResponseDataLength(void) {
        CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
        return m_rawResponseBufferLength;
    }
    
    /** @brief Save response data to file. */
    int saveResponseData(const char* filename);
    
    /** @brief Get error code. */
    int getErrorCode(void) {
        return m_errorCode;
    }
    
    /** @brief Get error message. */
    const char* getErrorMessage(void) {
        return m_errorMessage.c_str();
    }
    
    /** @brief timer function. */
    virtual void update(float dt);
    
private:
    CCHTTPRequest(CCHTTPRequestDelegate* delegate,
                  const char* url,
                  int method,
                  bool isAutoReleaseOnFinish)
    : m_delegate(delegate)
    , m_luaListener(0)
    , m_url(url ? url : "")
    , m_method(method)
    , m_isAutoReleaseOnFinish(isAutoReleaseOnFinish)
    , m_state(kCCHTTPRequestStateIdle)
    , m_errorCode(kCCHTTPRequestErrorNone)
    , m_responseCode(0)
    , m_responseString(NULL)
    , m_responseDataLength(0)
    {
    }
    bool initHttpRequest(void);

    enum {
        DEFAULT_TIMEOUT = 10, // 10 seconds
    };
    
    struct Chunk {
        void* data;
        int bytes;
    };
    
    typedef vector<Chunk>       Chunks;
    typedef Chunks::iterator    ChunksIterator;
    typedef map<string, string> Fields;
    typedef Fields::iterator    FieldsIterator;
    
    CCHTTPRequestDelegate* m_delegate;
    int m_luaListener;
    
    string  m_url;
    int     m_method;
    bool    m_isAutoReleaseOnFinish;
    int     m_state;
    int     m_errorCode;
    string  m_errorMessage;

    // request
    Fields  m_postFields;
    Fields  m_headers;
    string  m_postdata;

    // response
    int     m_responseCode;
    Fields  m_responseHeaders;
    string* m_responseString;
    int     m_responseDataLength;
    
    CURL*   m_curl;
#ifdef _WINDOWS_
    static DWORD WINAPI requestCURL(LPVOID userdata);
#else
    pthread_t m_thread;
    static void* requestCURL(void *userdata);
#endif

    void cleanup(void);
    void cleanupRawResponseBuff(void);

    // instance callback
    void onRequest(void);
    size_t onWriteData(void* buffer, size_t bytes);
    size_t onWriteHeader(void* buffer, size_t bytes);
    int onProgress(double dltotal, double dlnow, double ultotal, double ulnow);

    // curl callback
    static size_t writeDataCURL(void* buffer, size_t size, size_t nmemb, void* userdata);
    static size_t writeHeaderCURL(void* buffer, size_t size, size_t nmemb, void* userdata);
    static int progressCURL(void* userdata, double dltotal, double dlnow, double ultotal, double ulnow);
};

NS_CC_EXTRA_END

#endif /* __CC_HTTP_REQUEST_H_ */
