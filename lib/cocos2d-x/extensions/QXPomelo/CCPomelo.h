//
//
//  Created by xudexin on 13-4-17.
//
//

#ifndef __CCPomelo__
#define __CCPomelo__

#include "cocos2d.h"
#include "jansson.h"
#include "pomelo.h"
#include "pthread.h"
#include<queue>
#define KCCPomeloConnectStageWait       1//等待连接
#define KCCPomeloConnectStageDoing      2//连接中
#define KCCPomeloConnectStageDone       3//连接成功
using namespace cocos2d;

class CCPomeloContent_;
class CCPomeloReponse_;
class CCPomeloEvent_ ;
class CCPomeloNotify_;

class CCPomeloReponse:public cocos2d::CCObject{
public:
    CCPomeloReponse(){}
    ~CCPomeloReponse(){}
    const char* rout;
    int status;
    json_t *docs;
    int luaHandler;//回调给Lua的fucntion handle --add by yangzhu
    const char* event;
};

class CCPomelo :public cocos2d::CCObject{
public:
    static CCPomelo *getInstance();
    static void destroyInstance();
    
    int connect(const char* addr,int port, CCObject* pTarget, SEL_CallFuncND pSelector);
    int request(const char*route,json_t *msg,CCObject* pTarget, int luaHandler, SEL_CallFuncND pSelector);
    int notify(const char*route,json_t *msg,CCObject* pTarget, SEL_CallFuncND pSelector);
    int addListener(const char* event,CCObject* pTarget, SEL_CallFuncND pSelector);
    void destroy();
    
    void setLogLevel(int logLevel);
    void setIsConnected(int _isConnected);

public:
    CCPomelo();
    virtual ~CCPomelo();
    
    void dispatchCallbacks(float delta);
    
    
    pc_client_t *getClient();
    void lockReponsQeueue();
    void unlockReponsQeueue();
    void lockEventQeueue();
    void unlockEventQeueue();
    void lockNotifyQeueue();
    void unlockNotifyQeueue();
    void lockConnect();
    void unlockConnect();
    void pushReponse(CCPomeloReponse_*resp);
    void pushEvent(CCPomeloEvent_*ev);
    void pushNotiyf(CCPomeloNotify_*ntf);
    void pushConnectStatus(int connectStatus);
    CCPomeloContent_ *connectContent;
    int connect_status;
    int connect_stage;//连接阶段 等待 连接 成功
    static void onChatCallback(pc_client_t *client, const char *event, void *data);
	static void onAddCallback(pc_client_t *client, const char *event, void *data);
	static void onLeaveCallback(pc_client_t *client, const char *event, void *data);
	static void onDisconnectCallback(pc_client_t *client, const char *event, void *data);

private:
    void incTaskCount();
    void desTaskCount();
    void connectTick(float dt);//连接检测
    CCPomeloReponse_*popReponse();
    CCPomeloEvent_*popEvent();
    CCPomeloNotify_*popNotify();
    
    std::map<pc_notify_t*,CCPomeloContent_*> notify_content;
    pthread_mutex_t  notify_queue_mutex;
    std::queue<CCPomeloNotify_*> notify_queue;
    
    std::map<std::string,CCPomeloContent_*> event_content;
    pthread_mutex_t  event_queue_mutex;
    std::queue<CCPomeloEvent_*> event_queue;
    
    std::map<pc_request_t *,CCPomeloContent_*> request_content;
    pthread_mutex_t  reponse_queue_mutex;
    std::queue<CCPomeloReponse_*> reponse_queue;
    
    pthread_mutex_t  task_count_mutex;
    pthread_mutex_t  connect_mutex;

    void dispatchRequest();
    void dispatchEvent();
    void dispatchNotify();
    void dispatchConnectCallback();
    

    pc_client_t *client;
    int task_count;
    int log_level;
};

#endif /* defined(__CCPomelo__) */
