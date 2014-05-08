//
//  MobClickCpp.h
//  MobClickCpp
//
//  Created by zhangziqi on 13-9-22.
//  Copyright (c) 2013年 Umeng Inc. All rights reserved.
//

#ifndef __MobClickGameAnalytics__MobClickCpp__
#define __MobClickGameAnalytics__MobClickCpp__

#include <string>
#include <map>
using namespace std;

typedef map<string, string> eventDict;
typedef map<string, string> checkResultDict;


class MobClickCpp {
public:
    ///---------------------------------------------------------------------------------------
    /// @name  设置
    ///---------------------------------------------------------------------------------------
    
    /** 设置app版本号。由于历史原因需要和xcode3工程兼容,友盟提取的是Build号(CFBundleVersion),如果需要和App Store上的版本一致,需要调用此方法。此方法只有ios平台有效。
     
     @param appVersion 版本号，例如设置成`XcodeAppVersion`.
     @return void.
     */
    static void setAppVersion(const char* appVersion);
    
    
    /** 开启CrashReport收集, 默认是开启状态。此方法只有ios平台有效。
     
     @param value 设置成NO,就可以关闭友盟CrashReport收集.
     @return void.
     */
    static void setCrashReportEnabled(bool value);
    
    
    /** 设置是否打印sdk的log信息,默认不开启
     @param value 设置为true,umeng SDK 会输出log信息,记得release产品时要设置回false.
     @return .
     @exception .
     */
    
    static void setLogEnabled(bool value);
    
    ///---------------------------------------------------------------------------------------
    /// @name  开启统计
    ///---------------------------------------------------------------------------------------
    
//#if defined(ANDROID)
    /** 请根据cocos2dx的版本在main.cpp中对sdk初始化
     
     @param context <android_native_app_glue.h>中定义的android_app->activity->clazz 使用时强转为(void*)
     @return void
     */
    
    static void initJniForCocos2dx3(void* vm, void* context);
    
    static void initJniForCocos2dx2(void* vm, const char *activityName);
//#endif
    /** 开启友盟统计,默认以BATCH方式发送log.
     
     @param appKey 友盟appKey.
     @param channelId 渠道名称,为NULL或""时,ios默认会被被当作@"App Store"渠道，android默认为“Unknown”。
     @return void
     */
    static void startWithAppkey(const char * appKey, const char * channelId = NULL);
    
    /** 在AppDelegate的applicationDidEnterBackground中调用。
     
     @return void
     */
    static void applicationDidEnterBackground();
    
    /** 在AppDelegate的applicationWillEnterForeground中调用。
     
     @return void
     */
    static void applicationWillEnterForeground();
    
    /** 请在调用CCDirector的end()方法前调用。
     
     @return void
     */
    static void end();
    
    ///---------------------------------------------------------------------------------------
    /// @name  事件统计
    ///---------------------------------------------------------------------------------------
    
    
    /** 自定义事件,数量统计.
     使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
     
     @param  eventId 网站上注册的事件Id.
     @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为NULL或空字符串时后台会生成和eventId同名的标签.
     @return void.
     */
    static void event(const char * eventId, const char * label = NULL);
    /** 自定义事件,数量统计.
     使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
     */
    static void event(const char * eventId, eventDict * attributes, int counter = 0);
    
    /** 自定义事件,时长统计.
     使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
     beginEvent,endEvent要配对使用。
     
     @param  eventId 网站上注册的事件Id.
     @param  label 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为NULL或空字符串时后台会生成和eventId同名的标签.
     @param  primarykey 这个参数用于和event_id一起标示一个唯一事件，并不会被统计；对于同一个事件在beginEvent和endEvent 中要传递相同的eventId 和 primarykey
     @param millisecond 自己计时需要的话需要传毫秒进来
     @return void.
     
     
     @warning 每个event的attributes不能超过10个
     eventId、attributes中key和value都不能使用空格和特殊字符，且长度不能超过255个字符（否则将截取前255个字符）
     id， ts， du是保留字段，不能作为eventId及key的名称
     
     */
    static void beginEvent(const char * eventId);
    /** 自定义事件,时长统计.
     使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
     */
    static void endEvent(const char * eventId);
    /** 自定义事件,时长统计.
     使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
     */
    
    static void beginEventWithLabel(const char * eventId, const char * label);
    /** 自定义事件,时长统计.
     使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
     */
    
    static void endEventWithLabel(const char * eventId, const char * label);
    /** 自定义事件,时长统计.
     使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
     */
    
    static void beginEventWithAttributes(const char * eventId, const char * primarykey, eventDict * attributes);
    /** 自定义事件,时长统计.
     使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID.
     */
    
    static void endEventWithAttributes(const char * eventId, const char * primarykey);
    
    ///---------------------------------------------------------------------------------------
    /// @name  页面计时
    ///---------------------------------------------------------------------------------------
    
    
    /** 页面时长统计,记录某个view被打开多长时间,可以自己计时也可以调用beginLogPageView,endLogPageView自动计时
     
     @param pageName 需要记录时长的view名称.
     @return void.
     */
    
    static void beginLogPageView(const char *pageName);
    static void endLogPageView(const char *pageName);

    
    ///---------------------------------------------------------------------------------------
    /// @name  按渠道自动更新 只支持ios平台
    ///---------------------------------------------------------------------------------------
    
    
    /** 按渠道自动更新检测
     检查当前app是否有更新，有更新弹出UIAlertView提示用户,当用户点击升级按钮时app会跳转到您预先设置的网址。
     无更新不做任何操作。
     
     @param title 对应UIAlertView的title.
     @param cancelTitle 对应UIAlertView的cancelTitle.
     @param otherTitle 对应UIAlertView的otherTitle.
     @return void.
     */
    
    static void checkUpdate();
    /** 按渠道自动更新检测
     */
    
    //安卓平台此函数和checkUpdate()效果一致
    static void checkUpdate(const char * title, const char * cancelTitle, const char * otherTitle);
    
    //此方法只对android平台有效
    static void setUpdateOnlyWifi(bool updateOnlyWifi);
    
    /** 按渠道自动更新检测
     */
    
    
    ///---------------------------------------------------------------------------------------
    /// @name  在线参数
    ///---------------------------------------------------------------------------------------
    
    
    /** 使用在线参数功能，可以让你动态修改应用中的参数值,
     调用此方法您将自动拥有在线更改SDK端发送策略的功能,您需要先在服务器端设置好在线参数.
     请在startWithAppkey方法之后调用;
     @param 无.
     @return void.
     */
    
    static void updateOnlineConfig();
    
    /** 获取缓存的在线参数的数值
     带参数的方法获取某个key的值，不带参数的获取所有的在线参数.
     需要先调用updateOnlineConfig才能使用
     
     @param key
     @return const char *  .
     */
    
    static string getConfigParams(const char * key);
    
    //游戏统计开始
    
    ///---------------------------------------------------------------------------------------
    /// @name  玩家属性设置
    ///---------------------------------------------------------------------------------------
    
    /** 设置玩家的等级、游戏中的唯一Id、性别、年龄和来源.
     */
    
    /** 设置玩家等级属性.
     @param level 玩家等级
     @return void
     */
    static void setUserLevel(const char *level);
    
    /** 设置玩家等级属性.
     @param userId 玩家Id
     @param sex 性别
     @param age 年龄
     @param platform 来源
     @return void
     */
    
    enum Sex{
        Unkonwn = 0,
        Male = 1,
        Female = 2,
    };
    static void setUserInfo(const char * userId, Sex sex, int age, const char * platform);
    
    ///---------------------------------------------------------------------------------------
    /// @name  关卡统计
    ///---------------------------------------------------------------------------------------
    
    /** 记录玩家进入关卡，通过关卡及失败的情况.
     */
    
    
    /** 进入关卡.
     @param level 关卡 不允许NULL
     @return void
     */
    static void startLevel(const char * level);
    
    /** 通过关卡.
     @param level 关卡,不允许NULL
     @return void
     */
    static void finishLevel(const char * level);
    
    /** 未通过关卡.
     @param level 关卡,不允许NULL
     @return void
     */
    
    static void failLevel(const char * level);
    
    ///---------------------------------------------------------------------------------------
    /// @name  支付统计
    ///---------------------------------------------------------------------------------------
    
    /** 记录玩家使用真实货币的消费情况
     */
    
    
    /** 玩家支付货币兑换虚拟币.
     @param cash 真实货币数量
     @param source 支付渠道
     @param coin 虚拟币数量
     @return void
     */
    
    static void pay(double cash, int source, double coin);
    
    /** 玩家支付货币购买道具.
     @param cash 真实货币数量
     @param source 支付渠道
     @param item 道具名称
     @param amount 道具数量
     @param price 道具单价
     @return void
     */
    static void pay(double cash, int source, const char * item, int amount, double price);
    
    ///---------------------------------------------------------------------------------------
    /// @name  虚拟币购买统计
    ///---------------------------------------------------------------------------------------
    
    /** 记录玩家使用虚拟币的消费情况
     */
    
    
    /** 玩家使用虚拟币购买道具
     @param item 道具名称
     @param amount 道具数量
     @param price 道具单价
     @return void
     */
    static void buy(const char *item, int amount, double price);
    
    
    ///---------------------------------------------------------------------------------------
    /// @name  道具消耗统计
    ///---------------------------------------------------------------------------------------
    
    /** 记录玩家道具消费情况
     */
    
    
    /** 玩家使用虚拟币购买道具
     @param item 道具名称
     @param amount 道具数量
     @param price 道具单价
     @return void
     */
    
    static void use(const char * item, int amount, double price);
    
    
    ///---------------------------------------------------------------------------------------
    /// @name  虚拟币及道具奖励统计
    ///---------------------------------------------------------------------------------------
    
    /** 记录玩家获赠虚拟币及道具的情况
     */
    
    
    /** 玩家获虚拟币奖励
     @param coin 虚拟币数量
     @param source 奖励方式
     @return void
     */
    
    static void bonus(double coin, int source);
    
    /** 玩家获道具奖励
     @param item 道具名称
     @param amount 道具数量
     @param price 道具单价
     @param source 奖励方式
     @return void
     */
    
    static void bonus(const char * item, int amount, double price, int source);
    
    /** 场景统计
     @oaram sceneName 场景名称
     @return void
     */
    
    static void beginScene(const char* sceneName);
    
    static void endScene(const char* sceneName);
    //游戏统计结束
};

#endif
