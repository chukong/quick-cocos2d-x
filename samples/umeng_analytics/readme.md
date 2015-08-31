
本例是集成友盟的 游戏统计分析cocos2d-x Beta v1.0 (2014-03-17)
详细文档参见 <http://dev.umeng.com/game/game-cocos2d/quick-start>



## 关于样例中集成友盟统计的步骤 ##

### 拷贝文件 ###

$(QUICK_COCOS2DX_ROOT)/lib/sdk/umeng_analytics/include中的
* MobClickCpp.h
* MobClickCppForLua_luabinding.cpp
* MobClickCppForLua_luabinding.h
* MobClickCppForLua.cpp
* MobClickCppForLua.h

五个文件到工程中的sources中


### IOS相关 ###

	1. 拷贝$(QUICK_COCOS2DX_ROOT)/lib/sdk/umeng_analytics/umeng_analytics_ios/libMobClickCppWithLibCpp.a到工程中proj.ios/sdk/umeng_analytics_ios/中
	
	2. 并把步骤1中的五个源文件加到xcode工程源文件中

### android相关 ###

	1. 拷贝$(QUICK_COCOS2DX_ROOT)/lib/sdk/umeng_analytics/umeng_analytics_android/* 到工程中proj.android/中
	
	2. 修改proj.android/jni/Android.mk，
	
	3. 在Android.mk中加入
	LOCAL_SRC_FILES :=
    	../../sources/MobClickCppForLua_luabinding.cpp \
    	../../sources/MobClickCppForLua.cpp
	LOCAL_LDLIBS := $(LOCAL_PATH)/../libs/cocos2dx2_libMobClickCpp.a
	
	4. 修改proj.android/jni/helloCpp/main.cpp, 在其中的JNI_OnLoad函数中加入
	MobClickCpp::initJniForCocos2dx2((void*)vm,
	"此处填写上一步修改的activity的名字 如org/cocos2d_x/samples/umeng_analytics/Umeng_analytics");
	
	5. 修改游戏中主activity，见样例中的Umeng_analytics

### android,ios都有 ###
	1. AppDelegate::applicationDidFinishLaunching中还需要调用luaopen_MobClickCppForLua_luabinding函数

	2. 在lua中调用cc.analytics:doCommand函数可间接调到MobClickCpp中提供的函数

	例如

	doCommand中的参数为
	{
		command = "setCrashReportEnabled",	--对应函数名字
		args = XXX 							--args中对应的参数为MobClickCpp中参数的名字
 		{
			value = boolean
		}
	}


### 注意: ###

基本上MobClickCpp中的函数都可以直接把doCommand中的参数command设置为函数名

MobClickCpp中有需要传eventDict类型参数，已改为传string类型，对应格式为 “k,v” 或 “k,v|k,v”

函数名与command不同的情况

***
command = event

void event(const char * eventId, const char * label = 0)
***
command = eventCustom

void eventCustom(const char * eventId, const char * attributes, int counter = 0)
***
command = payCoin

void pay(double cash, int source, double coin)
***
command = payItem

void pay(double cash, int source, const char * item, int amount, double price);
***
command = bonusCoin

void bonus(double coin, int source)
***
command = bonusItem

void bonus(const char * item, int amount, double price, int source)
***
command = checkUpdate

void checkUpdate()
***
command = checkUpdateWithArgs

void checkUpdate(const char * title, const char * cancelTitle, const char * otherTitle)
***

*友盟在http://dev.umeng.com/game/game-cocos2d/quick-start中没提到android需要ACCESS_WIFI_STATE权限，
实际发现，没有这个权限，每次友盟都会认为是一个新用户*
