
#include "network/CCNetwork.h"

NS_CC_EXTRA_BEGIN

bool CCNetwork::isLocalWiFiAvailable(void)
{
    CCLOG("CCNetwork::isLocalWiFiAvailable() - not support this platform.");
    return true;
}

bool CCNetwork::isInternetConnectionAvailable(void)
{
    CCLOG("CCNetwork::isInternetConnectionAvailable() - not support this platform.");
    return true;
}

bool CCNetwork::isHostNameReachable(const char* hostName)
{
    CCLOG("CCNetwork::isHostNameReachable() - not support this platform.");
    return true;
}

int CCNetwork::getInternetConnectionStatus(void)
{
    CCLOG("CCNetwork::getInternetConnectionStatus() - not support this platform.");
    return kCCNetworkStatusNotReachable;
}

NS_CC_EXTRA_END
