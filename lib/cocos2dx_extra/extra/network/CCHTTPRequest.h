
#ifndef __CC_HTTP_REQUEST_H_
#define __CC_HTTP_REQUEST_H_

#include "cocos2dx_extra.h"
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
#include <string>
#include "curl/curl.h"

using namespace std;
USING_NS_CC;

NS_CC_EXTRA_BEGIN

#define kCCHTTPRequestMethodGET  0
#define kCCHTTPRequestMethodPOST 1

#define kCCHTTPRequestAcceptEncodingIdentity 0
#define kCCHTTPRequestAcceptEncodingGzip     1
#define kCCHTTPRequestAcceptEncodingDeflate  2

#define kCCHTTPRequestStateIdle       0
#define kCCHTTPRequestStateCleared    1
#define kCCHTTPRequestStateInProgress 2
#define kCCHTTPRequestStateCompleted  3
#define kCCHTTPRequestStateCancelled  4
#define kCCHTTPRequestStateFailed     5

typedef vector<string> CCHTTPRequestHeaders;
typedef CCHTTPRequestHeaders::iterator CCHTTPRequestHeadersIterator;

class CCHTTPRequest : public CCObject
{
public:
    static CCHTTPRequest* createWithUrl(CCHTTPRequestDelegate* delegate,
                                        const char* url,
                                        int method = kCCHTTPRequestMethodGET);
    
#if CC_LUA_ENGINE_ENABLED > 0
    static CCHTTPRequest* createWithUrlLua(LUA_FUNCTION listener,
                                           const char* url,
                                           int method = kCCHTTPRequestMethodGET);
#endif
    
    ~CCHTTPRequest(void);
    
    /** @brief Set request url. */
    void setRequestUrl(const char* url);
    
    /** @brief Add a custom header to the request. */
    void addRequestHeader(const char* header);
    
    /** @brief Add a POST variable to the request, POST only. */
    void addPOSTValue(const char* key, const char* value);
    
    /** @brief Set POST data to the request body, POST only. */
    void setPOSTData(const char* data);
    
    /** @brief Set accept encoding. */
    void setAcceptEncoding(int acceptEncoding);
    
    /** @brief Number of seconds to wait before timing out - default is 10. */
    void setTimeout(float timeout);
    
    /** @brief Execute an asynchronous request. */
    void start(void);
    
    /** @brief Cancel an asynchronous request, clearing all delegates first. */
    void cancel(void);
    
    /** @brief Get the request state. */
    int getState(void) {
        return m_state;
    }
    
    /** @brief Return HTTP status code. */
    int getResponseStatusCode(void) {
        CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
        return m_responseCode;
    }
    
    /** @brief Return HTTP response headers. */
    const CCHTTPRequestHeaders& getResponseHeaders(void);
    
    /** @brief Returns the contents of the result. */
    const string getResponseString(void);
    
    /** @brief Alloc memory block, return response data. use free() release memory block */
    void* getResponseData(void);
    
#if CC_LUA_ENGINE_ENABLED > 0
    LUA_STRING getResponseDataLua(void);
#endif
    
    /** @brief Get response data length (bytes). */
    int getResponseDataLength(void) {
        CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
        return m_responseDataLength;
    }
    
    /** @brief Save response data to file. */
    size_t saveResponseData(const char* filename);
    
    /** @brief Get error code. */
    int getErrorCode(void) {
        return m_errorCode;
    }
    
    /** @brief Get error message. */
    const char* getErrorMessage(void) {
        return m_errorMessage.c_str();
    }
    
    /** @brief Return CCHTTPRequestDelegate delegate. */
    CCHTTPRequestDelegate* getDelegate(void) {
        return m_delegate;
    }

    /** @brief timer function. */
    virtual void update(float dt);
    
private:
    CCHTTPRequest(void)
    : m_delegate(NULL)
    , m_listener(0)
    , m_state(kCCHTTPRequestStateIdle)
    , m_errorCode(0)
    , m_responseCode(0)
    , m_responseBuffer(NULL)
    , m_responseBufferLength(0)
    , m_responseDataLength(0)
    {
    }
    bool initWithDelegate(CCHTTPRequestDelegate* delegate, const char* url, int method);
#if CC_LUA_ENGINE_ENABLED > 0
    bool initWithListener(LUA_FUNCTION listener, const char* url, int method);
#endif
    bool initWithUrl(const char* url, int method);

    enum {
        DEFAULT_TIMEOUT = 10, // 10 seconds
        BUFFER_CHUNK_SIZE = 32768, // 32 KB
    };
    
    static unsigned int s_id;
    CURL* m_curl;
    CCHTTPRequestDelegate* m_delegate;
    int m_listener;
    
    int     m_state;
    int     m_errorCode;
    string  m_errorMessage;

    // request
    typedef map<string, string> Fields;    
    Fields m_postFields;
    CCHTTPRequestHeaders m_headers;

    // response
    int     m_responseCode;
    CCHTTPRequestHeaders m_responseHeaders;
    void*   m_responseBuffer;
    size_t  m_responseBufferLength;
    size_t  m_responseDataLength;

    // private methods
    void cleanup(void);
    void cleanupRawResponseBuff(void);

    // instance callback
    void onRequest(void);
    size_t onWriteData(void* buffer, size_t bytes);
    size_t onWriteHeader(void* buffer, size_t bytes);
    int onProgress(double dltotal, double dlnow, double ultotal, double ulnow);

    // curl callback
#ifdef _WINDOWS_
    static DWORD WINAPI requestCURL(LPVOID userdata);
#else
    pthread_t m_thread;
    static void* requestCURL(void *userdata);
#endif
    static size_t writeDataCURL(void* buffer, size_t size, size_t nmemb, void* userdata);
    static size_t writeHeaderCURL(void* buffer, size_t size, size_t nmemb, void* userdata);
    static int progressCURL(void* userdata, double dltotal, double dlnow, double ultotal, double ulnow);
};

NS_CC_EXTRA_END

#endif /* __CC_HTTP_REQUEST_H_ */
