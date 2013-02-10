
#include "network/CCHTTPRequest.h"
#include <stdio.h>
#include <iostream>

#if CC_LUA_ENGINE_ENABLED > 0
extern "C" {
#include "lua.h"
}
#include "CCLuaEngine.h"
#endif

using namespace cocos2d;

NS_CC_EXTRA_BEGIN

CCHTTPRequest* CCHTTPRequest::createWithUrl(CCHTTPRequestDelegate* delegate,
                                            const char* url,
                                            int method)
{
    CCHTTPRequest* request = new CCHTTPRequest();
    request->initWithDelegate(delegate, url, method);
    request->autorelease();
    return request;
}

#if CC_LUA_ENGINE_ENABLED > 0
CCHTTPRequest* CCHTTPRequest::createWithUrlLua(LUA_FUNCTION listener,
                                               const char* url,
                                               int method)
{
    CCHTTPRequest* request = new CCHTTPRequest();
    request->initWithListener(listener, url, method);
    request->autorelease();
    return request;
}
#endif

bool CCHTTPRequest::initWithDelegate(CCHTTPRequestDelegate* delegate, const char* url, int method)
{
    m_delegate = delegate;
    return initWithUrl(url, method);
}

#if CC_LUA_ENGINE_ENABLED > 0
bool CCHTTPRequest::initWithListener(LUA_FUNCTION listener, const char* url, int method)
{
    m_listener = listener;
    return initWithUrl(url, method);
}
#endif

bool CCHTTPRequest::initWithUrl(const char* url, int method)
{
    m_curl = curl_easy_init();
    curl_easy_setopt(m_curl, CURLOPT_URL, url);
    curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl");
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, DEFAULT_TIMEOUT * 1000);
    if (method == kCCHTTPRequestMethodPOST)
    {
        curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
        curl_easy_setopt(m_curl, CURLOPT_COPYPOSTFIELDS, "");
    }
    return true;
}

CCHTTPRequest::~CCHTTPRequest(void)
{
    cleanup();
    CCLOG("~~ delete CCHTTPRequest\n");
}

void CCHTTPRequest::setRequestUrl(const char* url)
{
    curl_easy_setopt(m_curl, CURLOPT_URL, url);
}

void CCHTTPRequest::addRequestHeader(const char* header)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    CCAssert(header, "Invalid header");
    m_headers.push_back(string(header));
}

void CCHTTPRequest::addPOSTValue(const char* key, const char* value)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    CCAssert(key, "Invalid key");
    m_postFields[string(key)] = string(value ? value : "");
}

void CCHTTPRequest::setPOSTData(const char* data)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    CCAssert(data, "Invalid data");
    m_postFields.clear();
    curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
    curl_easy_setopt(m_curl, CURLOPT_COPYPOSTFIELDS, data);
}

void CCHTTPRequest::setAcceptEncoding(int acceptEncoding)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    switch (acceptEncoding)
    {
        case kCCHTTPRequestAcceptEncodingGzip:
            curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "gzip");
            break;
            
        case kCCHTTPRequestAcceptEncodingDeflate:
            curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
            break;
            
        default:
            curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "identity");
    }
}

void CCHTTPRequest::setTimeout(float timeout)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, timeout * 1000);
}

void CCHTTPRequest::start(void)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");    
    m_state = kCCHTTPRequestStateInProgress;
    
    curl_easy_setopt(m_curl, CURLOPT_HTTP_CONTENT_DECODING, 1);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeDataCURL);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, writeHeaderCURL);
    curl_easy_setopt(m_curl, CURLOPT_WRITEHEADER, this);
    curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, progressCURL);
    curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, this);
    
#ifdef _WINDOWS_
    CreateThread(NULL,          // default security attributes
                 0,             // use default stack size
                 requestCURL,   // thread function name
                 this,          // argument to thread function
                 0,             // use default creation flags
                 NULL);
#else
    pthread_create(&m_thread, NULL, requestCURL, this);
    pthread_detach(m_thread);
#endif
    
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

void CCHTTPRequest::cancel(void)
{
    if (m_state == kCCHTTPRequestStateInProgress)
    {
        m_state = kCCHTTPRequestStateCancelled;
    }
}

void CCHTTPRequest::clearDelegatesAndCancel(void)
{
    m_delegate = NULL;
    cancel();
}

const CCHTTPRequestHeaders& CCHTTPRequest::getResponseHeaders(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
    return m_responseHeaders;
}

const string CCHTTPRequest::getResponseString(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
    return string(m_responseBuffer ? static_cast<char*>(m_responseBuffer) : "");
}

void* CCHTTPRequest::getResponseData(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
    void* buff = malloc(m_responseDataLength);
    memcpy(buff, m_responseBuffer, m_responseDataLength);
    return buff;
}

#if CC_LUA_ENGINE_ENABLED > 0
LUA_STRING CCHTTPRequest::getResponseDataLua(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
    CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
    stack->clean();
    stack->pushString(static_cast<char*>(m_responseBuffer), m_responseDataLength);
    return 1;
}
#endif

size_t CCHTTPRequest::saveResponseData(const char* filename)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
    
    FILE *fp = fopen(filename, "wb");
    size_t writedBytes = m_responseDataLength;
    if (fp)
    {
        if (writedBytes > 0)
        {
            fwrite(m_responseBuffer, m_responseDataLength, 1, fp);
        }
        fclose(fp);
    }
    return writedBytes;
}

void CCHTTPRequest::update(float dt)
{
    if (m_state == kCCHTTPRequestStateInProgress) return;
    CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);

    if (m_state == kCCHTTPRequestStateCompleted)
    {
        if (m_delegate) m_delegate->requestFinished(this);
        
#if CC_LUA_ENGINE_ENABLED > 0
        if (m_listener)
        {
            CCLuaValueDict dict;
            dict["name"] = CCLuaValue::stringValue("completed");
            dict["request"] = CCLuaValue::ccobjectValue(this, "CCHTTPRequest");
            CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
            stack->clean();
            stack->pushCCLuaValueDict(dict);
            stack->executeFunctionByHandler(m_listener, 1);
        }
#endif
    }
    else if (m_state == kCCHTTPRequestStateCancelled)
    {
        if (m_delegate) m_delegate->requestFailed(this);
        
#if CC_LUA_ENGINE_ENABLED > 0
        if (m_listener)
        {
            CCLuaValueDict dict;
            dict["name"] = CCLuaValue::stringValue("failed");
            dict["request"] = CCLuaValue::ccobjectValue(this, "CCHTTPRequest");
            CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
            stack->clean();
            stack->pushCCLuaValueDict(dict);
            stack->executeFunctionByHandler(m_listener, 1);
        }
#endif
    }
}

// instance callback

void CCHTTPRequest::onRequest(void)
{
    if (m_postFields.size() > 0)
    {
        curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
        stringbuf buf;
        for (Fields::iterator it = m_postFields.begin(); it != m_postFields.end(); ++it)
        {
            char* part = curl_easy_escape(m_curl, it->first.c_str(), 0);
            buf.sputn(part, strlen(part));
            buf.sputc('=');
            curl_free(part);
            
            part = curl_easy_escape(m_curl, it->second.c_str(), 0);
            buf.sputn(part, strlen(part));
            curl_free(part);
            
            buf.sputc('&');
        }
        curl_easy_setopt(m_curl, CURLOPT_COPYPOSTFIELDS, buf.str().c_str());
    }

    struct curl_slist* chunk = NULL;
    for (CCHTTPRequestHeadersIterator it = m_headers.begin(); it != m_headers.end(); ++it)
    {
        chunk = curl_slist_append(chunk, (*it).c_str());
    }
    
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, chunk);
    CURLcode code = curl_easy_perform(m_curl);
    curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(m_curl);
    m_curl = NULL;
    curl_slist_free_all(chunk);
    
    m_errorCode = code;
    m_errorMessage = (code == CURLE_OK) ? "" : curl_easy_strerror(code);
    
    m_state = kCCHTTPRequestStateCompleted;
}

size_t CCHTTPRequest::onWriteData(void* buffer, size_t bytes)
{
    if (m_responseDataLength + bytes + 1 > m_responseBufferLength)
    {
        m_responseBufferLength += BUFFER_CHUNK_SIZE;
        m_responseBuffer = realloc(m_responseBuffer, m_responseBufferLength);
    }
    
    memcpy(static_cast<char*>(m_responseBuffer) + m_responseDataLength, buffer, bytes);
    m_responseDataLength += bytes;
    static_cast<char*>(m_responseBuffer)[m_responseDataLength] = 0;
    return bytes;
}

size_t CCHTTPRequest::onWriteHeader(void* buffer, size_t bytes)
{
    char* headerBuffer = new char[bytes + 1];
    headerBuffer[bytes] = 0;
    memcpy(headerBuffer, buffer, bytes);    
    m_responseHeaders.push_back(string(headerBuffer));
    delete []headerBuffer;
    return bytes;
}

int CCHTTPRequest::onProgress(double dltotal, double dlnow, double ultotal, double ulnow)
{
    return m_state == kCCHTTPRequestStateCancelled ? 1: 0;
}

void CCHTTPRequest::cleanup(void)
{
    m_state = kCCHTTPRequestStateCleared;
    if (m_responseBuffer)
    {
        free(m_responseBuffer);
    }
    m_responseBuffer = NULL;
    m_responseBufferLength = 0;
    m_responseDataLength = 0;
    if (m_curl)
    {
        curl_easy_cleanup(m_curl);
    }
    m_curl = NULL;
}

// curl callback

#ifdef _WINDOWS_
DWORD WINAPI CCHTTPRequest::requestCURL(LPVOID userdata)
{
    static_cast<CCHTTPRequest*>(userdata)->onRequest();
    return 0;
}
#else // _WINDOWS_
void* CCHTTPRequest::requestCURL(void *userdata)
{
    static_cast<CCHTTPRequest*>(userdata)->onRequest();
    return NULL;
}
#endif // _WINDOWS_

size_t CCHTTPRequest::writeDataCURL(void* buffer, size_t size, size_t nmemb, void* userdata)
{
    return static_cast<CCHTTPRequest*>(userdata)->onWriteData(buffer, size * nmemb);
}

size_t CCHTTPRequest::writeHeaderCURL(void* buffer, size_t size, size_t nmemb, void* userdata)
{
    return static_cast<CCHTTPRequest*>(userdata)->onWriteHeader(buffer, size * nmemb);
}

int CCHTTPRequest::progressCURL(void* userdata, double dltotal, double dlnow, double ultotal, double ulnow)
{
    return static_cast<CCHTTPRequest*>(userdata)->onProgress(dltotal, dlnow, ultotal, ulnow);
}

NS_CC_EXTRA_END
