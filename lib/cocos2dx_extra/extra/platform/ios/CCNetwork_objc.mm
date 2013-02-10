
#include "network/CCNetwork.h"

#import "platform/ios/reachability/Reachability_objc.h"

NS_CC_EXTRA_BEGIN

#pragma mark -
#pragma mark Reachability

bool CCNetwork::isLocalWiFiAvailable(void)
{
    return [[Reachability_objc reachabilityForLocalWiFi] currentReachabilityStatus] != NotReachable;
}

bool CCNetwork::isInternetConnectionAvailable(void)
{
    return [[Reachability_objc reachabilityForInternetConnection] currentReachabilityStatus] != NotReachable;
}

bool CCNetwork::isHostNameReachable(const char* hostName)
{
    NSString *hostName_ = [NSString stringWithUTF8String:hostName];
    return [[Reachability_objc reachabilityWithHostName:hostName_] currentReachabilityStatus] != NotReachable;
}

CCNetworkStatus CCNetwork::getInternetConnectionStatus(void)
{
    NetworkStatus status = [[Reachability_objc reachabilityForInternetConnection] currentReachabilityStatus];
    if (status == ReachableViaWiFi) return CCNetworkStatusReachableViaWiFi;
    if (status == ReachableViaWWAN) return CCNetworkStatusReachableViaWWAN;
    return CCNetworkStatusNotReachable;
}

NS_CC_EXTRA_END
