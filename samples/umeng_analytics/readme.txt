本例是集成友盟的 游戏统计分析cocos2d-x Beta v1.0 (2014-03-17)
详细文档参见 http://dev.umeng.com/game/game-cocos2d/quick-start



关于集成友盟统计的步骤
================================================

1.
拷贝$(QUICK_COCOS2DX_ROOT)/lib/sdk/umeng_analytics/include中的
MobClickCpp.h
MobClickCppForLua_luabinding.cpp
MobClickCppForLua_luabinding.h
MobClickCppForLua.cpp
MobClickCppForLua.h
五个文件到工程中的sources中

2.1 IOS相关

2.1.1
拷贝$(QUICK_COCOS2DX_ROOT)/lib/sdk/umeng_analytics/umeng_analytics_ios/libMobClickCppWithLibCpp.a
到工程中proj.ios/sdk/umeng_analytics_ios/中

2.1.2
并把步骤1中的五个文件加到xcode工程源文件中

2.2 android相关

2.2.1
拷贝$(QUICK_COCOS2DX_ROOT)/lib/sdk/umeng_analytics/umeng_analytics_android/*
到工程中proj.android/中

2.2.2
修改proj.android/jni/Android.mk，
在其中加入
LOCAL_SRC_FILES :=
    ../../sources/MobClickCppForLua_luabinding.cpp \
    ../../sources/MobClickCppForLua.cpp

LOCAL_LDLIBS := $(LOCAL_PATH)/../libs/cocos2dx2_libMobClickCpp.a

2.2.3
修改proj.android/jni/helloCpp/main.cpp
在其中的JNI_OnLoad函数中加入
MobClickCpp::initJniForCocos2dx2((void*)vm,
        "此处填写上一步修改的activity的名字 如org/cocos2d_x/samples/umeng_analytics/Umeng_analytics");

2.2.4
修改游戏中主activity，见样例中的Umeng_analytics

3.android,ios都有
在
AppDelegate::applicationDidFinishLaunching
AppDelegate::applicationDidEnterBackground
AppDelegate::applicationWillEnterForeground
调用MobClickCpp对应的函数

AppDelegate::applicationDidFinishLaunching中还需要调用luaopen_MobClickCppForLua_luabinding函数

4.在lua中通过MobClickCppForLua调用MobClickCpp的各种函数
参见MainScene中的用法



注意:
---------------------------------------------------------------------
基本上MobClickCpp中的函数都可以通过MobClickCppForLua调用到

MobClickCpp中有需要传eventDict类型参数，已改为传string类型，对应格式为 “k,v” 或 “k,v|k,v”

因为参数的改变，MobClickCppForLua把MobClickCpp中的
static void event(const char * eventId, eventDict * attributes, int counter = 0);
函数名改为
void eventCustom(const char * eventId, const char * attributes, int counter = 0);
用法实例在 MainScene 中



友盟在http://dev.umeng.com/game/game-cocos2d/quick-start中没提到android需要ACCESS_WIFI_STATE权限，
实际发现，没有这个权限，每次友盟都会认为是一个新用户
