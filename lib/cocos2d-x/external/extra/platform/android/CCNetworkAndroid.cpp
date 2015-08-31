
#include "network/CCNetwork.h"
#include "cocos2d.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#include <stdlib.h>
#include <android/log.h>

NS_CC_EXTRA_BEGIN

bool CCNetwork::isLocalWiFiAvailable(void)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNetwork", "isLocalWiFiAvailable", 
        "()Z"))
    {
        jboolean ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		return ret;
    }
    return false;
    
}

bool CCNetwork::isInternetConnectionAvailable(void)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNetwork", "isInternetConnectionAvailable", 
        "()Z"))
    {
        jboolean ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		return ret;
    }
    return false;
}

bool CCNetwork::isHostNameReachable(const char* hostName)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNetwork", "isHostNameReachable", 
        "(Ljava/lang/String;)Z"))
    {
		jstring jhostName = methodInfo.env->NewStringUTF(hostName);
        jboolean ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jhostName);
		methodInfo.env->DeleteLocalRef(jhostName);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		return ret;
    }
    return false;
}

int CCNetwork::getInternetConnectionStatus(void)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNetwork", "getInternetConnectionStatus", 
        "()I"))
    {
        jint ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		return ret;
    }
    return kCCNetworkStatusNotReachable;
}

NS_CC_EXTRA_END
