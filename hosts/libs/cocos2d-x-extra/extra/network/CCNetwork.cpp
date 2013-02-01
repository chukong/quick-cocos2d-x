
#include "network/CCNetwork.h"

using namespace cocos2d;

NS_CC_EXTRA_BEGIN

CCHTTPRequest* CCNetwork::createHTTPRequest(CCHTTPRequestDelegate* delegate,
                                            const char* url,
                                            CCHTTPRequestMethod method)
{
    CCHTTPRequest* request = CCHTTPRequest::createWithUrl(delegate, url, method);
    request->start();
    return request;
}

#if CC_LUA_ENGINE_ENABLED > 0
CCHTTPRequest* CCNetwork::createHTTPRequestLua(LUA_FUNCTION listener,
                                               const char* url,
                                               CCHTTPRequestMethod method)
{
    CCHTTPRequest* request = CCHTTPRequest::createWithUrlLua(listener, url, method);
    request->start();
    return request;
}
#endif

NS_CC_EXTRA_END
