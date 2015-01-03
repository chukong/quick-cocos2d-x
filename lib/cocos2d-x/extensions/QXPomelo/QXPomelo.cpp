#include "QXPomelo.h"

USING_NS_CC;


QXPomelo::QXPomelo()
{
    ccp_pInstance = CCPomelo::getInstance();
}

void QXPomelo::connect(const char* _addr, unsigned short _port, LUA_FUNCTION listener)
{
    connect_listener = listener;
    if(ccp_pInstance->connect(_addr, _port, this, callfuncND_selector(QXPomelo::connectCB))) {
        CCLOG("fail to connect server.\n");
    }else{
        CCLOG("DONE");
    }
}

int QXPomelo::request(const char* route, const char* msg, LUA_FUNCTION listener)
{
//    const char *route = "connector.connectorHandler.enter";
    json_error_t error;
    json_t *msgJSON = json_loads(msg, 0, &error);
    return (int)ccp_pInstance->request(route, msgJSON, this, listener, callfuncND_selector(QXPomelo::requestCB));
}

void QXPomelo::notify(const char* route, const char* msg)
{
    json_error_t error;
    json_t *msgJSON = json_loads(msg, 0, &error);
    ccp_pInstance->notify(route, msgJSON, this, callfuncND_selector(QXPomelo::notifyCB));
}

void QXPomelo::destroy()
{
    ccp_pInstance->destroy();
}
//注册事件监听
void QXPomelo::addListener(const char* event)
{
    ccp_pInstance->addListener(event, this, callfuncND_selector(QXPomelo::eventCB));
}


void QXPomelo::notifyCB(cocos2d::CCNode *node, void *resp)
{
    CCPomeloReponse *ccpomeloresp = (CCPomeloReponse*)resp;
}


//连接成功回调
void QXPomelo::connectCB(cocos2d::CCNode *node, void *resp)
{
    CCPomeloReponse *ccpomeloresp = (CCPomeloReponse*)resp;
    CCLuaValueDict dict;
    dict["status"] = CCLuaValue::intValue(ccpomeloresp->status);
    dict["request"] = CCLuaValue::ccobjectValue(this, "QXPomelo");
    CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
    stack->clean();
    stack->pushCCLuaValueDict(dict);
    stack->executeFunctionByHandler(connect_listener, 1);
}

//连接成功回调
void QXPomelo::requestCB(cocos2d::CCNode *node, void *resp)
{
    CCPomeloReponse *ccpomeloresp = (CCPomeloReponse*)resp;
    CCLuaValueDict dict;
    int luaHandle = ccpomeloresp->luaHandler;
    if (luaHandle) {
        dict["status"] = CCLuaValue::intValue(ccpomeloresp->status);
        dict["request"] = CCLuaValue::ccobjectValue(this, "QXPomelo");
//        dict["rout"] = CCLuaValue::stringValue(ccpomeloresp->rout);
        json_t *docs = ccpomeloresp->docs;
        char *json_str = json_dumps(docs, 0);
        dict["msg"] = CCLuaValue::stringValue(json_str);
        CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->clean();
        stack->pushCCLuaValueDict(dict);
        stack->executeFunctionByHandler(luaHandle, 1);
    }
}

void QXPomelo::bindEventHandle(LUA_FUNCTION listener)
{
    event_listener = listener;
}

void QXPomelo::eventCB(cocos2d::CCNode *node, void *resp)
{
    CCPomeloReponse *ccpomeloresp = (CCPomeloReponse*)resp;
    CCLuaValueDict dict;
    if (event_listener) {
        dict["event"] = CCLuaValue::stringValue(ccpomeloresp->event);
        json_t *docs = ccpomeloresp->docs;
        char *json_str = json_dumps(docs, 0);
        dict["msg"] = CCLuaValue::stringValue(json_str);
        CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->clean();
        stack->pushCCLuaValueDict(dict);
        stack->executeFunctionByHandler(event_listener, 1);
    }
}
