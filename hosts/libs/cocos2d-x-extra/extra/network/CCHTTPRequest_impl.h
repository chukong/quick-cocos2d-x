
#ifndef __CC_EXTENSION_CCHTTP_REQUEST_WIN32_H_
#define __CC_EXTENSION_CCHTTP_REQUEST_WIN32_H_

#include "network/CCHTTPRequest.h"

#ifdef _WINDOWS_
#include <Windows.h>
#else
#include <pthread.h>
#endif

#include <vector>
#include <map>
#include "curl/curl.h"

NS_CC_EXTRA_BEGIN

class CCHTTPRequest_impl
{
public:
    CCHTTPRequest_impl(const char* url, CCHTTPRequestMethod method);
    virtual ~CCHTTPRequest_impl(void);
    
    void addRequestHeader(const char* key, const char* value);
    void addPostValue(const char* key, const char* value);
    void setPostData(const char* data);
    void setTimeout(float timeout);
    
    bool start(void);
    void cancel(void);
    
    bool getIsInProgress(void) {
        return m_state == STATE_IN_PROGRESS;
    }
    
    bool getIsCompleted(void) {
        return m_state == STATE_COMPLETED;
    }
    
    bool getIsCancelled(void) {
        return m_state == STATE_CANCELLED;
    }
    
    int getResponseStatusCode(void) {
        return m_responseCode;
    }
    
    const std::string& getResponseHeaders(void) {
//        return m_responseHeaders;
        return std::string("");
    }
    
    const std::string& getResponseString(void) {
        return m_responseString;
    }
    
    const void* getResponseData(void) {
        return m_responseData;
    }
    
    int getResponseDataLength(void) {
        return m_responseDataLength;
    }
    
    CCHTTPRequestError getErrorCode(void) {
        return m_errorCode;
    }
    
    const char* getErrorMessage(void) {
        return m_errorMessage.c_str();
    }
    
private:
    enum {
        DEFAULT_TIMEOUT = 10, // 10 seconds
    };
    
    typedef enum {
        STATE_IDLE,
        STATE_IN_PROGRESS,
        STATE_COMPLETED,
        STATE_CANCELLED
    } State;
    
    typedef enum {
        ENCODING_IDENTITY,
        ENCODING_GZIP,
        ENCODING_DEFLATE
    } Encoding;
    
    class Chunk
    {
    public:
        Chunk(const void* source, size_t bytes)
        : m_bytes(bytes)
        {
            m_chunk = malloc(bytes);
            memcpy(m_chunk, source, bytes);
        }
        ~Chunk(void) {
            free(m_chunk);
        }
        
        void* getChunk(void) {
            return m_chunk;
        }
        size_t getBytes(void) {
            return m_bytes;
        }
        
    private:
        void*   m_chunk;
        size_t  m_bytes;
    };
    
    typedef std::vector<Chunk*>                 RawResponseDataBuff;
    typedef RawResponseDataBuff::iterator       RawResponseDataBuffIterator;
    
    typedef std::map<std::string, std::string>  PostFields;
    typedef PostFields::iterator                PostFieldsIterator;
    
    typedef std::vector<std::string>            Headers;
    typedef Headers::iterator                   HeadersIterator;
    
    CURL*               m_curl;
    State               m_state;
    bool                m_isPost;
    PostFields          m_postFields;
    Headers             m_headers;
    std::string         m_postdata;
    
    RawResponseDataBuff m_rawResponseBuff;
    size_t              m_rawResponseBuffLength;
    long                m_responseCode;
    CCHTTPRequestError  m_errorCode;
    std::string         m_errorMessage;
    
    Headers             m_responseHeaders;
    std::string         m_responseString;
    unsigned char*      m_responseData;
    int                 m_responseDataLength;
    Encoding            m_responseEncoding;
    
#ifdef _WINDOWS_
    static DWORD WINAPI curlRequest(LPVOID lpParam);
#else
    pthread_t           m_thread;
    static void*        curlRequest(void *data);
#endif
    
    static size_t curlWriteData(void* buffer, size_t size, size_t nmemb, void* userdata);
    static size_t curlWriteHeader(void* buffer, size_t size, size_t nmemb, void* userdata);
    static int curlProgress(void* userp, double dltotal, double dlnow, double ultotal, double ulnow);
    
    void onRequest(void);
    size_t onWriteData(void* buffer, size_t bytes);
    size_t onWriteHeader(void* buffer, size_t bytes);
    int onProgress(double dltotal, double dlnow, double ultotal, double ulnow);
    
    void cleanup(void);
    void cleanupRawResponseBuff(void);
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCHTTP_REQUEST_WIN32_H_
