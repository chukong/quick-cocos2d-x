
#include "network/CCNetwork.h"
#import "ReachabilityIOSMac.h"

NS_CC_EXTRA_BEGIN

bool CCNetwork::isLocalWiFiAvailable(void)
{
    return [[ReachabilityIOSMac reachabilityForLocalWiFi] currentReachabilityStatus] != NotReachable;
}

bool CCNetwork::isInternetConnectionAvailable(void)
{
    return [[ReachabilityIOSMac reachabilityForInternetConnection] currentReachabilityStatus] != NotReachable;
}

bool CCNetwork::isHostNameReachable(const char* hostName)
{
    NSString *hostName_ = [NSString stringWithUTF8String:hostName];
    return [[ReachabilityIOSMac reachabilityWithHostname:hostName_] currentReachabilityStatus] != NotReachable;
}

int CCNetwork::getInternetConnectionStatus(void)
{
    NetworkStatus status = [[ReachabilityIOSMac reachabilityForInternetConnection] currentReachabilityStatus];
    if (status == ReachableViaWiFi) return kCCNetworkStatusReachableViaWiFi;
    if (status == ReachableViaWWAN) return kCCNetworkStatusReachableViaWWAN;
    return kCCNetworkStatusNotReachable;
}

NS_CC_EXTRA_END
