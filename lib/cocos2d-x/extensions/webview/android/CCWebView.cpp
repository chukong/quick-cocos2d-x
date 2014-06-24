//
//  CCWebView.cpp
//
// Created by Vincent on 12-11-27.
// From https://github.com/go3k/CCXWebview
// Modified by zrong on 2014-06-24.
//

#include "CCWebView.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

/*
 More info about JNI using, check this:
 http://go3k.org/?p=49
 */

#warning 如果想在你的工程中嵌入，前务必修改这个包名，值为Andriod工程Main Activity的路径
#warning If you want to use this CCXWebview in your project, please modify this packageName as your Android project.
//const char* kJNIPakageName = "us/t1201/testplayer/Testplayer";

CCWebView* CCWebView::create()
{
	CCWebView* webview = new CCWebView();
	if(webview && webview->init())
	{
		webview->autorelease();
		return webview;
	}
	else
	{
		delete webview;
		webview = NULL;
		return NULL;
	}
}

CCWebView* CCWebView::create(const char* activityName)
{
	CCWebView* webview = new CCWebView(activityName);
	if(webview && webview->init())
	{
		webview->autorelease();
		return webview;
	}
	else
	{
		delete webview;
		webview = NULL;
		return NULL;
	}
}

CCWebView::CCWebView()
: _activityName(NULL)
{
    
}

CCWebView::CCWebView(const char* activityName)
{
	_activityName = CCString::create(activityName);
	_activityName->retain();
}

CCWebView::~CCWebView()
{
	CC_SAFE_RELEASE_NULL(_activityName);
}

bool CCWebView::init()
{
	return true;
}

void CCWebView::showWebView(const char* url, float x, float y, float width, float height)
{
    //1. 获取activity静态对象
    JniMethodInfo minfo;
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 this->getActivityName(),
                                                 "getJavaActivity",
                                                 "()Ljava/lang/Object;");
    jobject activityObj;
    if (isHave)
    {
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    
    //2. 查找displayWebView接口，并用jobj调用
    isHave = JniHelper::getMethodInfo(minfo,this->getActivityName(),"displayWebView", "(IIII)V");
    
    if (!isHave)
    {
        CCLog("jni:displayWebView 函数不存在");
    }
    else
    {
        //调用此函数
        jint jX = (int)x;
        jint jY = (int)y;
        jint jWidth = (int)width;
        jint jHeight = (int)height;
        minfo.env->CallVoidMethod(activityObj, minfo.methodID, jX, jY, jWidth, jHeight);
    }
    
    //3. 查找updateURL接口，并用jobj调用
    isHave = JniHelper::getMethodInfo(minfo,this->getActivityName(),"updateURL", "(Ljava/lang/String;)V");
    
    if (!isHave)
    {
        CCLog("jni:updateURL 函数不存在");
    }
    else
    {
        //调用此函数
        jstring jmsg = minfo.env->NewStringUTF(url);
        minfo.env->CallVoidMethod(activityObj, minfo.methodID, jmsg);
    }
}

void CCWebView::updateURL(const char* url)
{
    //1. 获取activity静态对象
    JniMethodInfo minfo;
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 this->getActivityName(),
                                                 "getJavaActivity",
                                                 "()Ljava/lang/Object;");
    jobject activityObj;
    if (isHave)
    {
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    
    //2. 查找updateURL接口，并用jobj调用
    isHave = JniHelper::getMethodInfo(minfo,this->getActivityName(),"updateURL", "(Ljava/lang/String;)V");
    
    if (!isHave)
    {
        CCLog("jni:updateURL 函数不存在");
    }
    else
    {
        //调用此函数
        jstring jmsg = minfo.env->NewStringUTF(url);
        minfo.env->CallVoidMethod(activityObj, minfo.methodID, jmsg);
    }
}

void CCWebView::removeWebView()
{
    //1. 获取activity静态对象
    JniMethodInfo minfo;
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 this->getActivityName(),
                                                 "getJavaActivity",
                                                 "()Ljava/lang/Object;");
    jobject activityObj;
    if (isHave)
    {
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    
    //2. 查找updateURL接口，并用jobj调用
    isHave = JniHelper::getMethodInfo(minfo,this->getActivityName(),"removeWebView", "()V"); 
    
    if (!isHave)
    {
        CCLog("jni:updateURL 函数不存在");
    }
    else
    {
        //调用此函数
        minfo.env->CallVoidMethod(activityObj, minfo.methodID);
    }
}

const char* CCWebView::getActivityName()
{
	CCLOG("CCWebView::getActivityName %d", this->_activityName);
	if(this->_activityName)
	{
		return this->_activityName->getCString();
	}
	return "";
}

