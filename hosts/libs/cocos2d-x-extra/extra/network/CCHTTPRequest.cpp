
#include "network/CCHTTPRequest.h"
#include "network/CCHTTPRequest.h"
#include "cocos2d.h"
#include <stdio.h>
#include <iostream>

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif

using namespace cocos2d;

NS_CC_EXTRA_BEGIN

CCHTTPRequest* CCHTTPRequest::createWithUrl(CCHTTPRequestDelegate* delegate,
                                            const char* url,
                                            int method,
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
                                               int method)
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
    m_curl = curl_easy_init();
    curl_easy_setopt(m_curl, CURLOPT_URL, m_url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl");
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, DEFAULT_TIMEOUT * 1000);
    if (m_method == kCCHTTPRequestMethodPOST)
    {
        curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
    }
    return true;
}

CCHTTPRequest::~CCHTTPRequest(void)
{
    if (m_responseString)
    {
        delete m_responseString;
    }
    cleanup();
    CCLOG("~~ delete CCHTTPRequest\n");
}

void CCHTTPRequest::addRequestHeader(const char* key, const char* value)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    CCAssert(key, "Invalid key");
    m_headers[string(key)] = string(value ? value : "");
}

void CCHTTPRequest::addPostValue(const char* key, const char* value)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    CCAssert(key, "Invalid key");
    m_postFields[string(key)] = string(value ? value : "");
}

void CCHTTPRequest::setPostData(const char* data)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    CCAssert(data, "Invalid data");
    m_postFields.clear();
    m_postdata = string(data);
}

void CCHTTPRequest::setTimeout(float timeout)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, timeout * 1000);
}

void CCHTTPRequest::start(void)
{
    CCAssert(m_state == kCCHTTPRequestStateIdle, "Request not idle");
    CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
    
    m_state = kCCHTTPRequestStateInProgress;
    
    curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "gzip");
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
}

void CCHTTPRequest::cancel(void)
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
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

const char* CCHTTPRequest::getResponseHeaders(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
//    return ((CCHTTPRequest*)m_request)->getResponseHeaders().c_str();
}

const char* CCHTTPRequest::getResponseString(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
//    return ((CCHTTPRequest*)m_request)->getResponseString().c_str();
}

const void* CCHTTPRequest::getResponseData(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
//    return ((CCHTTPRequest*)m_request)->getResponseData();
}

cocos2d::LUA_STRING CCHTTPRequest::getResponseDataLua(void)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
    return 1;
}

int CCHTTPRequest::saveResponseData(const char* filename)
{
    CCAssert(m_state == kCCHTTPRequestStateCompleted, "Request not completed");
    
    FILE *fp = fopen(filename, "wb");
    int writedBytes = 0;
    if (fp)
    {
        writedBytes = fwrite(getResponseData(), m_rawResponseBufferLength, 1, fp);
        fclose(fp);
    }
    return writedBytes;
}

void CCHTTPRequest::update(float dt)
{
    CCHTTPRequest* request = (CCHTTPRequest*)m_request;
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

void CCHTTPRequest::onRequest(void)
{
    if (m_postFields.size() > 0)
    {
        curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
        std::stringbuf buf;
        PostFieldsIterator it = m_postFields.begin();
        while (it != m_postFields.end())
        {
            char* part = curl_easy_escape(m_curl, it->first.c_str(), 0);
            buf.sputn(part, strlen(part));
            buf.sputc('=');
            curl_free(part);
            
            part = curl_easy_escape(m_curl, it->second.c_str(), 0);
            buf.sputn(part, strlen(part));
            curl_free(part);
            
            ++it;
            if (it != m_postFields.end()) buf.sputc('&');
        }
        curl_easy_setopt(m_curl, CURLOPT_COPYPOSTFIELDS, buf.str().c_str());
    }
    else if (m_postdata.length() > 0)
    {
        curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
        curl_easy_setopt(m_curl, CURLOPT_COPYPOSTFIELDS, m_postdata.c_str());
    }
    else if (m_isPost)
    {
        curl_easy_setopt(m_curl, CURLOPT_COPYPOSTFIELDS, "");
    }
    
    struct curl_slist* chunk = NULL;
    for (HeadersIterator it = m_headers.begin(); it != m_headers.end(); ++it)
    {
        chunk = curl_slist_append(chunk, (*it).c_str());
    }
    
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, chunk);
    CURLcode code = curl_easy_perform(m_curl);
    curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &m_responseCode);
    curl_easy_cleanup(m_curl);
    m_curl = NULL;
    curl_slist_free_all(chunk);
    
    m_errorCode = (code == CURLE_OK) ? CCHTTPRequestErrorNone : CCHTTPRequestErrorUnknown;
    m_errorMessage = (code == CURLE_OK) ? "" : curl_easy_strerror(code);
    
    m_responseData = (unsigned char*)malloc(m_rawResponseBuffLength + 1);
    m_responseData[m_rawResponseBuffLength] = '\0';
    m_responseDataLength = 0;
    for (RecvBufferIterator it = m_rawResponseBuff.begin(); it != m_rawResponseBuff.end(); ++it)
    {
        CCHTTPRequest::Chunk* chunk = *it;
        size_t bytes = chunk->getBytes();
        memcpy(m_responseData + m_responseDataLength, chunk->getChunk(), bytes);
        m_responseDataLength += bytes;
    }
    cleanupRawResponseBuff();
    
    m_responseString = std::string(reinterpret_cast<char*>(m_responseData));
    m_state = STATE_COMPLETED;
}

size_t CCHTTPRequest::onWriteData(void* buffer, size_t bytes)
{
    CCHTTPRequest::Chunk* chunk = new CCHTTPRequest::Chunk(buffer, bytes);
    m_rawResponseBuff.push_back(chunk);
    m_rawResponseBuffLength += bytes;
    return bytes;
}

size_t CCHTTPRequest::onWriteHeader(void* buffer, size_t bytes)
{
    char* headerBuffer = new char[bytes + 1];
    memset(headerBuffer, 0, bytes + 1);
    memcpy(headerBuffer, buffer, bytes);
    delete []headerBuffer;
    
    std::string header(headerBuffer);
    size_t pos = header.find("Content-Encoding:");
    if (pos != header.npos)
    {
        CCLOG("Content-Encoding: %s", header.substr(pos + 18).c_str());
        
        if (header.compare(pos + 18, std::string::npos, "gzip") == 0)
        {
            m_responseEncoding = ENCODING_GZIP;
        }
        else if (header.compare(pos + 18, std::string::npos, "deflate") == 0)
        {
            m_responseEncoding = ENCODING_DEFLATE;
        }
    }
    
    m_responseHeaders.push_back(header);
    return bytes;
}

int CCHTTPRequest::onProgress(double dltotal, double dlnow, double ultotal, double ulnow)
{
    return m_state == STATE_CANCELLED ? 1: 0;
}

void CCHTTPRequest::cleanup(void)
{
    m_state = kCCHTTPRequestStateCleared;
    cleanupRawResponseBuff();
    m_rawResponseBufferLength = 0;
    if (m_responseString)
    {
        delete m_responseString;
        m_responseString = NULL;
    }
    if (m_curl)
    {
        curl_easy_cleanup(m_curl);
        m_curl = NULL;
    }
}

void CCHTTPRequest::cleanupRawResponseBuff(void)
{
    for (BufferIterator it = m_rawResponseBuffer.begin(); it != m_rawResponseBuffer.end(); ++it)
    {
        delete (*it);
    }
    m_rawResponseBuffer.clear();
    m_rawResponseBufferLength = 0;
}

// ----------------------------------------
// CURL callbacks

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
