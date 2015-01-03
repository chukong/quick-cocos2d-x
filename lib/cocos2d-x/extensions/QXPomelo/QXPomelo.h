#ifndef __CCPOMELO_H__
#define __CCPOMELO_H__
#include "cocos2d.h"
#ifdef _WINDOWS_
#include <Windows.h>
#else
#include <pthread.h>
#endif
#include "CCLuaEngine.h"
#include "CCPomelo.h"
//#include "cocos2dx_extra.h"
#define KCCPomeloConnectDone       1

class QXPomelo : public cocos2d::CCObject
{
public:
    QXPomelo();
    ~QXPomelo(){};

    void connect(const char* _addr, unsigned short _port, LUA_FUNCTION listener);
    LUA_STRING request(const char* route, const char* msg, LUA_FUNCTION listener);
    void notify(const char* route, const char* msg);
    void bindEventHandle(LUA_FUNCTION listener);
    void addListener(const char* event);
    void destroy();
// void onClosed(const char *event, void *data);
// int request(const char* route, const char* msg, LUA_FUNCTION listener);
//
// void onRequestCallback(int status, const char* msg);
// void onConnecting(void);
// static void *connectThread(void *userdata);

    void notifyCB(cocos2d::CCNode *node, void *resp);
    void connectCB(cocos2d::CCNode *node, void *resp);
    void requestCB(cocos2d::CCNode *node, void *resp);
    void eventCB(cocos2d::CCNode *node, void *resp);

protected:
    
private:
    CCPomelo* ccp_pInstance;
    int connect_listener;
    int event_listener;
};

#endif
