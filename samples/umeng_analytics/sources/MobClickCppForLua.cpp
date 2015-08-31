
#include "MobClickCppForLua.h"
#include "MobClickCpp.h"

eventDict* str2Map(const char* pStr) {
    if (NULL == pStr) {
        return NULL;
    }
    int nStrLen = strlen(pStr);
    if (0 == nStrLen) {
        return NULL;
    }
    
    eventDict *pDict = new eventDict();
    
    char* pSearchStr = (char*)pStr;
    char* pFoundStr = NULL;
    while (true) {
        //search key
        pFoundStr = strchr(pSearchStr, ',');
        if (NULL == pFoundStr) {
            break;
        }
        string key;
        key.assign(pSearchStr, pFoundStr - pSearchStr);
        
        //search value
        pSearchStr = pFoundStr + 1;
        pFoundStr = strchr(pSearchStr, '|');
        if (NULL == pFoundStr) {
            //think as it's last one
            pFoundStr = (char*)(pStr + nStrLen);
        }
        string val;
        val.assign(pSearchStr, pFoundStr - pSearchStr);
        
        pDict->insert(pair<string, string>(key, val));
        
        pSearchStr = pFoundStr + 1;
        if (pSearchStr >= pStr + nStrLen) {
            break;
        }
    }
    
    return pDict;
}

void MobClickCppForLua::setAppVersion(const char* appVersion) {
    MobClickCpp::setAppVersion(appVersion);
}

void MobClickCppForLua::setCrashReportEnabled(bool value) {
    MobClickCpp::setCrashReportEnabled(value);
}

void MobClickCppForLua::setLogEnabled(bool value) {
    MobClickCpp::setLogEnabled(value);
}

/*void MobClickCppForLua::initJniForCocos2dx3(void* vm, void* context) {
    MobClickCpp::initJniForCocos2dx3(vm, context);
}

void MobClickCppForLua::initJniForCocos2dx2(void* vm, const char *activityName) {
    MobClickCpp::initJniForCocos2dx2(vm, activityName);
}*/

void MobClickCppForLua::startWithAppkey(const char * appKey, const char * channelId) {
    MobClickCpp::startWithAppkey(appKey, channelId);
}

void MobClickCppForLua::applicationDidEnterBackground() {
    MobClickCpp::applicationDidEnterBackground();
}

void MobClickCppForLua::applicationWillEnterForeground() {
    MobClickCpp::applicationWillEnterForeground();
}

void MobClickCppForLua::endAnalytics() {
    MobClickCpp::end();
}

void MobClickCppForLua::event(const char * eventId, const char * label) {
    MobClickCpp::event(eventId, label);
}

void MobClickCppForLua::eventCustom(const char * eventId, const char * attributes, int counter) {
    eventDict *pDict = str2Map(attributes);
    MobClickCpp::event(eventId, pDict, counter);
    delete pDict;
}

void MobClickCppForLua::beginEvent(const char * eventId) {
    MobClickCpp::beginEvent(eventId);
}

void MobClickCppForLua::endEvent(const char * eventId) {
    MobClickCpp::endEvent(eventId);
}

void MobClickCppForLua::beginEventWithLabel(const char * eventId, const char * label) {
    MobClickCpp::beginEventWithLabel(eventId, label);
}

void MobClickCppForLua::endEventWithLabel(const char * eventId, const char * label) {
    MobClickCpp::endEventWithLabel(eventId, label);
}

void MobClickCppForLua::beginEventWithAttributes(const char * eventId, const char * primarykey, const char * attributes) {
    eventDict *pDict = str2Map(attributes);
    MobClickCpp::beginEventWithAttributes(eventId, primarykey, pDict);
    delete pDict;
}

void MobClickCppForLua::endEventWithAttributes(const char * eventId, const char * primarykey) {
    MobClickCpp::endEventWithAttributes(eventId, primarykey);
}

void MobClickCppForLua::beginLogPageView(const char *pageName) {
    MobClickCpp::beginLogPageView(pageName);
}

void MobClickCppForLua::endLogPageView(const char *pageName) {
    MobClickCpp::endLogPageView(pageName);
}

void MobClickCppForLua::checkUpdate() {
    MobClickCpp::checkUpdate();
}

void MobClickCppForLua::checkUpdate(const char * title, const char * cancelTitle, const char * otherTitle) {
    MobClickCpp::checkUpdate(title, cancelTitle, otherTitle);
}

void MobClickCppForLua::setUpdateOnlyWifi(bool updateOnlyWifi) {
    MobClickCpp::setUpdateOnlyWifi(updateOnlyWifi);
}

void MobClickCppForLua::updateOnlineConfig() {
    MobClickCpp::updateOnlineConfig();
}

const char* MobClickCppForLua::getConfigParams(const char * key) {
    string val = MobClickCpp::getConfigParams(key);
    return val.c_str();
}

void MobClickCppForLua::setUserLevel(const char * level) {
    MobClickCpp::setUserLevel(level);
}

void MobClickCppForLua::setUserInfo(const char * userId, int sex, int age, const char * platform) {
    MobClickCpp::setUserInfo(userId, (MobClickCpp::Sex)sex, age, platform);
}

void MobClickCppForLua::startLevel(const char * level) {
    MobClickCpp::startLevel(level);
}

void MobClickCppForLua::finishLevel(const char * level) {
    MobClickCpp::finishLevel(level);
}

void MobClickCppForLua::failLevel(const char * level) {
    MobClickCpp::failLevel(level);
}

void MobClickCppForLua::pay(double cash, int source, double coin) {
    MobClickCpp::pay(cash, source, coin);
}

void MobClickCppForLua::pay(double cash, int source, const char * item, int amount, double price) {
    MobClickCpp::pay(cash, source, item, amount, price);
}

void MobClickCppForLua::buy(const char *item, int amount, double price) {
    MobClickCpp::buy(item, amount, price);
}

void MobClickCppForLua::use(const char * item, int amount, double price) {
    MobClickCpp::use(item, amount, price);
}

void MobClickCppForLua::bonus(double coin, int source) {
    MobClickCpp::bonus(coin, source);
}

void MobClickCppForLua::bonus(const char * item, int amount, double price, int source) {
    MobClickCpp::bonus(item, amount, price, source);
}

void MobClickCppForLua::beginScene(const char* sceneName) {
    MobClickCpp::beginScene(sceneName);
}

void MobClickCppForLua::endScene(const char* sceneName) {
    MobClickCpp::endScene(sceneName);
}

