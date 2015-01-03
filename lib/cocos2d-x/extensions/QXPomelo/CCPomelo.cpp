//
//  ProtocolHandler.cpp
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-4-17.
//
//

#include "CCPomelo.h"
#include <errno.h>


class CCPomeloContent_ {
public:
    CCPomeloContent_(){
        pTarget = NULL;
        pSelector = NULL;
        pLuaHandler = 0;
    }
    ~CCPomeloContent_(){
        
    }
    CCObject* pTarget;
    SEL_CallFuncND pSelector;
    int pLuaHandler;
};
class CCPomeloReponse_ {
public:
    CCPomeloReponse_(){
        request = NULL;
        docs = NULL;
    }
    ~CCPomeloReponse_(){
        
    }
    int status;
    pc_request_t *request;
    json_t *docs;
};
class CCPomeloEvent_ {
public:
    CCPomeloEvent_(){
        docs = NULL;
    }
    ~CCPomeloEvent_(){
        
    }
    int status;
    std::string event;
    json_t *docs;
};

class CCPomeloNotify_ {
public:
    CCPomeloNotify_(){
        notify = NULL;
    }
    ~CCPomeloNotify_(){
        
    }
    int status;
    pc_notify_t *notify;
};

static CCPomelo *s_CCPomelo = NULL; // pointer to singleton

void cc_pomelo_on_notify_cb(pc_notify_t *ntf, int status){
    
    s_CCPomelo->lockNotifyQeueue();
    
    CCPomeloNotify_ *notify = new CCPomeloNotify_;
    notify->notify = ntf;
    notify->status = status;
    
    s_CCPomelo->pushNotiyf(notify);
    
    s_CCPomelo->unlockNotifyQeueue();
}


void cc_pomelo_on_event_cb(pc_client_t *client, const char *event, void *data) {
    
    s_CCPomelo->lockEventQeueue();
    
    CCPomeloEvent_ *ev = new CCPomeloEvent_;
    ev->event = event;
    ev->docs = (json_t *)data;
    json_incref(ev->docs);
    
    s_CCPomelo->pushEvent(ev);
    
    s_CCPomelo->unlockEventQeueue();
    
}

void on_close(pc_client_t *client, const char *event, void *data)
{
    CCLOG("client closed: %d.\n", client->state);
}
void CCPomelo::onChatCallback(pc_client_t *client, const char *event, void *data)
{
    json_t* json = (json_t* )data;
    const char* msg = json_dumps(json, 0);
    CCLOG("%s %s", event, msg);
//    messageQueue->addObject(CCString::create(msg));
//    return;
}

void CCPomelo::onAddCallback(pc_client_t *client, const char *event, void *data)
{
//    if (!userQueue) {
//        return;
//    }
    json_t* json = (json_t* )data;
    json_t* user = json_object_get(json, "user");
    const char* msg = json_string_value(user);
    CCLOG("%s %s", event, msg);
//    userQueue->addObject(CCString::create(msg));
    return;
}

void CCPomelo::onLeaveCallback(pc_client_t *client, const char *event, void *data)
{
//    if (!userQueue) {
//        return;
//    }
    json_t* json = (json_t* )data;
    json_t* user = json_object_get(json, "user");
    const char* msg = json_string_value(user);
    CCLOG("%s %s", event,msg);
//    for (unsigned int i=0; i<userQueue->count(); i++) {
//        CCString* cstring = (CCString* )userQueue->objectAtIndex(i);
//        if (strcmp(cstring->getCString(),msg) == 0) {
//            userQueue->removeObjectAtIndex(i);
//            break;
//        }
//    }
    return;
}

void CCPomelo::onDisconnectCallback(pc_client_t *client, const char *event, void *data)
{
    CCLOG("%s", event);
    return;
}


void cc_pomelo_on_connect_cb(pc_connect_t *conn_req, int status){
    s_CCPomelo->lockConnect();
    printf("data = %p\n", conn_req->data);
    pc_connect_req_destroy(conn_req);
    s_CCPomelo->connect_stage = KCCPomeloConnectStageDone;//连接完成 等待分发状态
    s_CCPomelo->connect_status = status;
    if(-1==status){
        printf("Connected error.\n");
    } else {
//        working = 1;
    }
//    pc_add_listener(s_CCPomelo->getClient(), PC_EVENT_DISCONNECT, on_close);
//    // add pomelo events listener
//    void (*on_disconnect)(pc_client_t *client, const char *event, void *data) = &CCPomelo::onDisconnectCallback;
//    void (*on_chat)(pc_client_t *client, const char *event, void *data) = &CCPomelo::onChatCallback;
//    void (*on_add)(pc_client_t *client, const char *event, void *data) = &CCPomelo::onAddCallback;
//    void (*on_leave)(pc_client_t *client, const char *event, void *data) = &CCPomelo::onLeaveCallback;
//    
//    pc_add_listener(s_CCPomelo->getClient(), "disconnect", on_disconnect);
//    pc_add_listener(s_CCPomelo->getClient(), "onChat", on_chat);
//    pc_add_listener(s_CCPomelo->getClient(), "onAdd", on_add);
//    pc_add_listener(s_CCPomelo->getClient(), "onLeave", on_leave);
    s_CCPomelo->unlockConnect();
}

void cc_pomelo_on_request_cb(pc_request_t *request, int status, json_t *docs) {
    
    s_CCPomelo->lockReponsQeueue();
//    char *json_str = json_dumps(docs, 0);
//    CCLOG("server response: %s \n", json_str);
    CCPomeloReponse_ *response = new CCPomeloReponse_;
    response->request = request;
    response->status = status;
    response->docs = docs;
    json_incref(docs);
    
    s_CCPomelo->pushReponse(response);
    
    s_CCPomelo->unlockReponsQeueue();
    
}

pc_client_t *CCPomelo::getClient()
{
    return this->client;
}

void CCPomelo::dispatchRequest(){
    lockReponsQeueue();
    CCPomeloReponse_ *response = popReponse();
    if (response) {
        CCPomeloContent_ * content = NULL;
        if (request_content.find(response->request)!=request_content.end()) {
            content = request_content[response->request];
            request_content.erase(response->request);
        }
        if (content) {
            if (log_level>0)
            CCLog("dispatch response:\r\nevent:%s\r\nmsg:%s\r\nstatus:%d\r\ndocs:%s\r\n",response->request->route,json_dumps(response->request->msg,0),response->status,json_dumps(response->docs,0));
            
            CCObject *pTarget = content->pTarget;
            SEL_CallFuncND pSelector = content->pSelector;
            int luaHandler = content->pLuaHandler;
            if (pTarget && pSelector)
            {
                CCPomeloReponse resp;
                resp.status = response->status;
                resp.docs = response->docs;
                resp.luaHandler = luaHandler;
                (pTarget->*pSelector)((CCNode *)this, &resp);
            }
        }else{
            CCLog("dispatch response:\r\nlost content");
        }
        json_decref(response->docs);
        json_decref(response->request->msg);
        pc_request_destroy(response->request);
        delete response;
    }
    unlockReponsQeueue();
}
void CCPomelo::dispatchEvent(){
    lockEventQeueue();
    CCPomeloEvent_ *event = popEvent();
    if (event) {
        CCPomeloContent_ * content = NULL;
        if (event_content.find(event->event)!=event_content.end()) {
            content = event_content[event->event];
        }
        if (content) {
            if (log_level>0)
            CCLog("dispatch event:\r\nevent:%s\r\nmsg:%s\r\nstatus:%d\r\n",event->event.c_str(),json_dumps(event->docs,0),event->status);
          
            CCObject *pTarget = content->pTarget;
            SEL_CallFuncND pSelector = content->pSelector;
            if (pTarget && pSelector)
            {
                CCPomeloReponse resp;
                resp.status = 0;
                resp.event = event->event.c_str();
                resp.docs = event->docs;
                (pTarget->*pSelector)((CCNode *)this,&resp);
            }
        }else{
            CCLog("dispatch event::\r\n lost %s content",event->event.c_str());
        }
        json_decref(event->docs);
        delete event;
    }
    unlockEventQeueue();
}
void CCPomelo::dispatchNotify(){
    lockNotifyQeueue();
    CCPomeloNotify_ *ntf = popNotify();
    if (ntf) {
        CCPomeloContent_ * content = NULL;
        if (notify_content.find(ntf->notify)!=notify_content.end()) {
            content = notify_content[ntf->notify];
            notify_content.erase(ntf->notify);
        }
        if (content) {
            if (log_level>0) {
                CCLog("dispatch notify:\r\nroute:%s\r\nmsg:%s\r\nstatus:%d\r\n",ntf->notify->route,json_dumps(ntf->notify->msg, 0),ntf->status);
            }

            CCObject *pTarget = content->pTarget;
            SEL_CallFuncND pSelector = content->pSelector;
            if (pTarget && pSelector)
            {
                CCPomeloReponse resp;
                resp.status = 0;
                resp.docs = NULL;
                (pTarget->*pSelector)((CCNode *)this,&resp);
            }
        }else{
            CCLog("dispatch notify:\r\nlost content");
        }
        json_decref(ntf->notify->msg);
        pc_notify_destroy(ntf->notify);
        delete ntf;
    }
    unlockNotifyQeueue();
}

void CCPomelo::dispatchConnectCallback()
{
    CCPomeloContent_ * content = NULL;
    content = s_CCPomelo->connectContent;
    if (content) {
        CCObject *pTarget = content->pTarget;
        SEL_CallFuncND pSelector = content->pSelector;
        if (pTarget && pSelector)
        {
            CCPomeloReponse resp;
            resp.status = s_CCPomelo->connect_status;
            resp.docs = NULL;
            (pTarget->*pSelector)((CCNode *)this, &resp);
        }
        s_CCPomelo->connectContent = NULL;
    }else{
        CCLog("dispatch notify:\r\nlost content");
    }
    
}

void CCPomelo::dispatchCallbacks(float delta){
    int _taskCount = 0;
    pthread_mutex_lock(&task_count_mutex);
    _taskCount = task_count;
    pthread_mutex_unlock(&task_count_mutex);
    if (_taskCount == 0) return;
    dispatchNotify();
    dispatchEvent();
    dispatchRequest();
}

CCPomelo::CCPomelo(){
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCPomelo::dispatchCallbacks), this, 0.05, false);
//    CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
    client = pc_client_new();
    pthread_mutex_init(&reponse_queue_mutex, NULL);
    pthread_mutex_init(&event_queue_mutex, NULL);
    pthread_mutex_init(&notify_queue_mutex, NULL);
    pthread_mutex_init(&task_count_mutex, NULL);
    pthread_mutex_init(&connect_mutex, NULL);
    log_level = 0;
    task_count = 0;
    connect_status = -1;
    connect_stage = KCCPomeloConnectStageWait;//等待连接
}

CCPomelo::~CCPomelo(){
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCPomelo::dispatchCallbacks), s_CCPomelo);
}
void CCPomelo::destroyInstance()
{
    if (s_CCPomelo) {
        s_CCPomelo->release();
    }
}

CCPomelo* CCPomelo::getInstance()
{
    if (s_CCPomelo == NULL) {
        s_CCPomelo = new CCPomelo();
    }
    return s_CCPomelo;
}

int isIPAddr(const char* pStr)
{
    int bRet = 1;
    if (NULL == pStr) return -1;
    const char* p = pStr;
    for (; *p != '\0'; p++)
    {
        if ((isalpha(*p)) && (*p != '.'))
        {
            bRet = 0;
            break;
        }
    }
    return bRet;
}

int getIPbyDomain(const char* domain, char* ip)
{
    struct hostent *answer;
    answer = gethostbyname(domain);
    if (NULL == answer)
    {
        herror("gethostbyname");//the error function of itself
        return -1;
    }
    if (answer->h_addr_list[0])
        inet_ntop(AF_INET, (answer->h_addr_list)[0], ip, 16);
    else
        return -1;
    return 0;
}

int CCPomelo::connect(const char* host,int port, CCObject* pTarget, SEL_CallFuncND pSelector){
    struct sockaddr_in address;
    char* ip = new char[40];
    if (isIPAddr(host)) {
        strcpy(ip, host);
    } else {
        int ret = getIPbyDomain(host, ip);
        if (ret) {
            CCLuaLog("域名解析失败");
            return 0;
        }
    }
    CCLuaLog(ip);
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip);
    if (client) {
        client = pc_client_new();
    }else{
        pc_client_destroy(client);
        client = pc_client_new();
    }
    
    s_CCPomelo->connectContent = new CCPomeloContent_;
    s_CCPomelo->connectContent->pTarget = pTarget;
    s_CCPomelo->connectContent->pSelector = pSelector;
    pc_connect_t *conn_req = pc_connect_req_new(&address);
    s_CCPomelo->connect_stage = KCCPomeloConnectStageDoing;//连接中
    int ret = pc_client_connect2(client, conn_req, cc_pomelo_on_connect_cb);
    if (ret) {
        CCLog("pc_client_connect error:%d",errno);
        pc_client_destroy(client);
        s_CCPomelo->connect_stage = KCCPomeloConnectStageDone;
        s_CCPomelo->connect_status = -1;
    }
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCPomelo::connectTick),this, 0.5,false);
    return ret;
}

void CCPomelo::connectTick(float dt)
{
    CCLOG("主线程连接检测");
    s_CCPomelo->lockConnect();
    if (s_CCPomelo->connect_stage == KCCPomeloConnectStageDone) {//连接成功或失败
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector( CCPomelo::connectTick), this);
        s_CCPomelo->dispatchConnectCallback();
    }
    s_CCPomelo->unlockConnect();
}

int CCPomelo::request(const char*route,json_t *msg,CCObject* pTarget, int luaHandler, SEL_CallFuncND pSelector){
    
    pc_request_t *req   = pc_request_new();
    CCPomeloContent_ *content = new CCPomeloContent_;
    content->pTarget = pTarget;
    content->pSelector = pSelector;
    content->pLuaHandler = luaHandler;
    request_content[req] = content;

    int ret = pc_request(client,req, route, json_deep_copy(msg), cc_pomelo_on_request_cb);
    return ret;
    // return 0;
}

int CCPomelo::notify(const char*route,json_t *msg,CCObject* pTarget, SEL_CallFuncND pSelector){
    
    pc_notify_t *notify = pc_notify_new();
    CCPomeloContent_ *content = new CCPomeloContent_;
    content->pTarget = pTarget;
    content->pSelector = pSelector;
    notify_content[notify] = content;
    pc_notify(client,notify, route, json_deep_copy(msg), cc_pomelo_on_notify_cb);
    
    return 0;
}

int CCPomelo::addListener(const char* event,CCObject* pTarget, SEL_CallFuncND pSelector){
    CCPomeloContent_ *content = new CCPomeloContent_;
    content->pTarget = pTarget;
    content->pSelector = pSelector;
    if (event_content.find(event)!=event_content.end()) {
        delete  event_content[event];
    }
    CCLog("CCPomelo::addListener event:%s",event);

    event_content[event] = content;
    return pc_add_listener(client, event, cc_pomelo_on_event_cb);
}

void CCPomelo::destroy()
{
    if (client) {
        pc_client_destroy(client);
    }
}

void CCPomelo::incTaskCount(){
    pthread_mutex_lock(&task_count_mutex);
    task_count++;
    pthread_mutex_unlock(&task_count_mutex);
//    CCDirector::sharedDirector()->getScheduler()->resumeTarget(s_CCPomelo);
}
void CCPomelo::desTaskCount(){
    pthread_mutex_lock(&task_count_mutex);
    task_count--;
    pthread_mutex_unlock(&task_count_mutex);
}

void CCPomelo::lockReponsQeueue(){
    pthread_mutex_lock(&reponse_queue_mutex);
}

void CCPomelo::lockConnect()
{
    pthread_mutex_lock(&connect_mutex);
}

void CCPomelo::unlockConnect()
{
    pthread_mutex_unlock(&connect_mutex);
}


void CCPomelo::unlockReponsQeueue(){
    pthread_mutex_unlock(&reponse_queue_mutex);
}

void CCPomelo::lockEventQeueue(){
    pthread_mutex_lock(&event_queue_mutex);
}

void CCPomelo::unlockEventQeueue(){
    pthread_mutex_unlock(&event_queue_mutex);
}

void CCPomelo::lockNotifyQeueue(){
    pthread_mutex_lock(&notify_queue_mutex);
}

void CCPomelo::unlockNotifyQeueue(){
    pthread_mutex_unlock(&notify_queue_mutex);
}
void CCPomelo::pushReponse(CCPomeloReponse_*response){
    reponse_queue.push(response);
    incTaskCount();
}
void CCPomelo::pushConnectStatus(int _connect_status)
{
    connect_status = _connect_status;
    incTaskCount();
}
void CCPomelo::pushEvent(CCPomeloEvent_* event){
    event_queue.push(event);
    incTaskCount();
}
void CCPomelo::pushNotiyf(CCPomeloNotify_*notify){
    notify_queue.push(notify);
    incTaskCount();
}
void CCPomelo::setLogLevel(int logLevel){
     this->log_level = logLevel;
}

CCPomeloReponse_*CCPomelo::popReponse(){
    if (reponse_queue.size()>0) {
        CCPomeloReponse_ *response = reponse_queue.front();
        reponse_queue.pop();
        desTaskCount();
        return  response;
    }else{
        return  NULL;
    }
}
CCPomeloEvent_*CCPomelo::popEvent(){
    if (event_queue.size()>0) {
        CCPomeloEvent_ *event = event_queue.front();
        event_queue.pop();
        desTaskCount();
        return  event;
    }else{
        return  NULL;
    }
}
CCPomeloNotify_*CCPomelo::popNotify(){
    if (notify_queue.size()>0) {
        CCPomeloNotify_ *ntf = notify_queue.front();
        notify_queue.pop();
        desTaskCount();
        return  ntf;
    }else{
        return  NULL;
    }
}



