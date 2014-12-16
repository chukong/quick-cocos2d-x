
#ifndef __CC_EXTENSION_CCNETWORK_H_
#define __CC_EXTENSION_CCNETWORK_H_

#include "cocos2dx_extra.h"

#if (CC_CURL_ENABLED > 0 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "network/CCHTTPRequest.h"
#include "network/CCHTTPRequestDelegate.h"
#endif

using namespace cocos2d;
NS_CC_EXTRA_BEGIN

#define kCCNetworkStatusNotReachable     0
#define kCCNetworkStatusReachableViaWiFi 1
#define kCCNetworkStatusReachableViaWWAN 2

class CCNetwork
{
public:
    /** @brief Checks whether a local wifi connection is available */
    static bool isLocalWiFiAvailable(void);

    /** @brief Checks whether the default route is available */
    static bool isInternetConnectionAvailable(void);

    /** @brief Checks the reachability of a particular host name */
    static bool isHostNameReachable(const char* hostName);

    /** @brief Checks Internet connection reachability status */
    static int getInternetConnectionStatus(void);

#if (CC_CURL_ENABLED > 0 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static CCHTTPRequest* createHTTPRequest(CCHTTPRequestDelegate* delegate,
                                            const char* url,
                                            int method = kCCHTTPRequestMethodGET);

#if CC_LUA_ENGINE_ENABLED > 0
    static CCHTTPRequest* createHTTPRequestLua(cocos2d::LUA_FUNCTION listener,
                                               const char* url,
                                               int method = kCCHTTPRequestMethodGET);
#endif

#endif // CC_CURL_ENABLED

private:
    CCNetwork(void) {}
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCNETWORK_H_
