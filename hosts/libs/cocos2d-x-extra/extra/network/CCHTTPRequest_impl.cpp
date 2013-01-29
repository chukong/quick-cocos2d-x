
#include "network/CCHTTPRequest_impl.h"
#include "cocos2d.h"
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include <pthread.h>
#endif
#include <iostream>
#include "zlib.h"

NS_CC_EXTRA_BEGIN

CCHTTPRequest_impl::CCHTTPRequest_impl(const char* url, CCHTTPRequestMethod method)
: m_state(STATE_IDLE)
, m_isPost(method == CCHTTPRequestMethodPOST)
, m_rawResponseBuffLength(0)
, m_responseData(NULL)
, m_responseDataLength(0)
, m_responseEncoding(ENCODING_IDENTITY)
, m_responseCode(0)
, m_errorCode(CCHTTPRequestErrorNone)
{
    m_curl = curl_easy_init();
    curl_easy_setopt(m_curl, CURLOPT_URL, url);
    curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl");
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, DEFAULT_TIMEOUT * 1000);
    if (method == CCHTTPRequestMethodPOST)
    {
        curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
    }
}

CCHTTPRequest_impl::~CCHTTPRequest_impl(void)
{
    cleanup();
    CCLOG("~~ delete CCHTTPRequest_impl\n");
}

void CCHTTPRequest_impl::addRequestHeader(const char* key, const char* value)
{
    std::stringbuf buff;
    buff.sputn(key, strlen(key));
    buff.sputn(": ", 2);
    buff.sputn(value, strlen(value));
    m_headers.push_back(buff.str());
}

void CCHTTPRequest_impl::addPostValue(const char* key, const char* value)
{
    m_postFields[std::string(key)] = std::string(value);
}

void CCHTTPRequest_impl::setPostData(const char* data)
{
    m_postFields.clear();
    m_postdata = std::string(data);
}

void CCHTTPRequest_impl::setTimeout(float timeout)
{
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, timeout * 1000);
}

bool CCHTTPRequest_impl::start(void)
{
    if (m_state != STATE_IDLE) return false;
    m_state = STATE_IN_PROGRESS;

    m_responseCode = 0;
    m_errorCode = CCHTTPRequestErrorNone;
    m_errorMessage = "";
    
    curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "gzip");
    curl_easy_setopt(m_curl, CURLOPT_HTTP_CONTENT_DECODING, 1);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, curlWriteData);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, curlWriteHeader);
    curl_easy_setopt(m_curl, CURLOPT_WRITEHEADER, this);
    curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, curlProgress);
    curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, this);
    
#ifdef _WINDOWS_
    CreateThread(NULL,          // default security attributes
                 0,             // use default stack size
                 curlRequest,   // thread function name
                 this,          // argument to thread function
                 0,             // use default creation flags
                 NULL);
#else
    pthread_create(&m_thread, NULL, curlRequest, this);
    pthread_detach(m_thread);
#endif
    
    return true;
}

void CCHTTPRequest_impl::cancel(void)
{
    if (m_state != STATE_IN_PROGRESS) return;
    m_state = STATE_CANCELLED;
}

// ----------------------------------------

#ifdef _WINDOWS_
DWORD WINAPI CCHTTPRequest_impl::curlRequest(LPVOID lpParam)
{
    CCHTTPRequest_impl* instance = (CCHTTPRequest_impl*)lpParam;
    instance->onRequest();
    return 0;
}
#else // _WINDOWS_
void* CCHTTPRequest_impl::curlRequest(void *data)
{
    CCHTTPRequest_impl* instance = (CCHTTPRequest_impl*)data;
    instance->onRequest();
    return NULL;
}
#endif // _WINDOWS_

size_t CCHTTPRequest_impl::curlWriteData(void* buffer, size_t size, size_t nmemb, void* userdata)
{
    CCHTTPRequest_impl* instance = (CCHTTPRequest_impl*)userdata;
    return instance->onWriteData(buffer, size * nmemb);
}

size_t CCHTTPRequest_impl::curlWriteHeader(void* buffer, size_t size, size_t nmemb, void* userdata)
{
    CCHTTPRequest_impl* instance = (CCHTTPRequest_impl*)userdata;
    return instance->onWriteHeader(buffer, size * nmemb);
}

int CCHTTPRequest_impl::curlProgress(void* userp, double dltotal, double dlnow, double ultotal, double ulnow)
{
    CCHTTPRequest_impl* instance = (CCHTTPRequest_impl*)userp;
    return instance->onProgress(dltotal, dlnow, ultotal, ulnow);
}

// ----------------------------------------

void CCHTTPRequest_impl::onRequest(void)
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
    for (RawResponseDataBuffIterator it = m_rawResponseBuff.begin(); it != m_rawResponseBuff.end(); ++it)
    {
        CCHTTPRequest_impl::Chunk* chunk = *it;
        size_t bytes = chunk->getBytes();
        memcpy(m_responseData + m_responseDataLength, chunk->getChunk(), bytes);
        m_responseDataLength += bytes;
    }
    cleanupRawResponseBuff();
        
    m_responseString = std::string(reinterpret_cast<char*>(m_responseData));
    m_state = STATE_COMPLETED;
}

size_t CCHTTPRequest_impl::onWriteData(void* buffer, size_t bytes)
{
    CCHTTPRequest_impl::Chunk* chunk = new CCHTTPRequest_impl::Chunk(buffer, bytes);
    m_rawResponseBuff.push_back(chunk);
    m_rawResponseBuffLength += bytes;
    return bytes;
}

size_t CCHTTPRequest_impl::onWriteHeader(void* buffer, size_t bytes)
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

int CCHTTPRequest_impl::onProgress(double dltotal, double dlnow, double ultotal, double ulnow)
{
    return m_state == STATE_CANCELLED ? 1: 0;
}

// ----------------------------------------

void CCHTTPRequest_impl::cleanup(void)
{
    cleanupRawResponseBuff();
    if (m_responseData) free(m_responseData);
    m_responseData = NULL;
    m_responseDataLength = 0;
    m_responseString = "";
    if (m_curl) curl_easy_cleanup(m_curl);
    m_curl = NULL;
}

void CCHTTPRequest_impl::cleanupRawResponseBuff(void)
{
    for (RawResponseDataBuffIterator it = m_rawResponseBuff.begin(); it != m_rawResponseBuff.end(); ++it)
    {
        delete (*it);
    }
    m_rawResponseBuff.clear();
    m_rawResponseBuffLength = 0;
}

NS_CC_EXTRA_END
