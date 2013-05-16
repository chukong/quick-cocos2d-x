
#include "CCPhysicsWorld.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsDebugNode.h"
#include "CCScriptSupport.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif

using namespace cocos2d;

CCPhysicsWorld *CCPhysicsWorld::create(void)
{
    CCPhysicsWorld *world = new CCPhysicsWorld();
    world->init();
    world->autorelease();
    return world;
}

CCPhysicsWorld *CCPhysicsWorld::create(float gravityX, float gravityY)
{
    CCPhysicsWorld *world = new CCPhysicsWorld();
    world->init();
    world->setGravity(gravityX, gravityY);
    world->autorelease();
    return world;
}

CCPhysicsWorld::~CCPhysicsWorld(void)
{
    removeAllCollisionListeners();
    removeAllBodies();
    CC_SAFE_RELEASE(m_listeners);
    CC_SAFE_RELEASE(m_defaultStaticBody);
    cpSpaceFree(m_space);
}

bool CCPhysicsWorld::init(void)
{
    m_space = cpSpaceNew();
    cpSpaceSetGravity(m_space, cpvzero);
    cpSpaceSetUserData(m_space, (cpDataPointer)this);
    
    m_listeners = CCArray::create();
    m_listeners->retain();
    return true;
}

cpSpace *CCPhysicsWorld::getSpace(void)
{
    return m_space;
}

CCPhysicsDebugNode *CCPhysicsWorld::createDebugNode(void)
{
    return CCPhysicsDebugNode::create(m_space);
}

const CCPoint CCPhysicsWorld::getGravity(void)
{
    const cpVect gravity = cpSpaceGetGravity(m_space);
    return CCPoint(gravity.x, gravity.y);
}

void CCPhysicsWorld::getGravity(float *gravityX, float *gravityY)
{
    const cpVect gravity = cpSpaceGetGravity(m_space);
    *gravityX = gravity.x;
    *gravityY = gravity.y;
}

void CCPhysicsWorld::setGravity(float gravityX, float gravityY)
{
    cpSpaceSetGravity(m_space, cpv(gravityX, gravityY));
}

CCPhysicsBody *CCPhysicsWorld::createCircleBody(float mass, float radius, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsBody *body;
    if (mass <= 0)
    {
        body = CCPhysicsBody::createStaticBody(this);
    }
    else
    {
        float moment = cpMomentForCircle(mass, 0, radius, cpv(offsetX, offsetY));
        body = CCPhysicsBody::create(this, mass, moment);
    }
    body->addCircleShape(radius, offsetX, offsetY);
    addBody(body);
    return body;
}

CCPhysicsBody *CCPhysicsWorld::createBoxBody(float mass, float width, float height)
{
    CCPhysicsBody *body;
    if (mass <= 0)
    {
        body = CCPhysicsBody::createStaticBody(this);
    }
    else
    {
        float moment = cpMomentForBox(mass, width, height);
        body = CCPhysicsBody::create(this, mass, moment);
    }
    body->addBoxShape(width, height);
    addBody(body);
    return body;
}

CCPhysicsBody *CCPhysicsWorld::createPolygonBody(float mass, CCPointArray *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsVectArray *cpVertexes = CCPhysicsVectArray::createFromCCPointArray(vertexes);
    return createPolygonBody(mass, cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}

CCPhysicsBody *CCPhysicsWorld::createPolygonBody(float mass, CCPhysicsVectArray *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    return createPolygonBody(mass, vertexes->count(), vertexes->data(), offsetX, offsetY);
}

CCPhysicsBody *CCPhysicsWorld::createPolygonBody(float mass, int numVertexes, cpVect *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsBody *body;
    if (mass <= 0)
    {
        body = CCPhysicsBody::createStaticBody(this);
    }
    else
    {
        float moment = cpMomentForPoly(mass, numVertexes, vertexes, cpv(offsetX, offsetY));
        body = CCPhysicsBody::create(this, mass, moment);
    }
    body->addPolygonShape(numVertexes, vertexes, offsetX, offsetY);
    addBody(body);
    return body;
}

#if CC_LUA_ENGINE_ENABLED > 0
CCPhysicsBody *CCPhysicsWorld::createPolygonBody(float mass, int vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsVectArray *cpVertexes = CCPhysicsVectArray::createFromLuaTable(vertexes);
    return createPolygonBody(mass, cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}
#endif

void CCPhysicsWorld::addBody(CCPhysicsBody *body)
{
    body->retain();
    m_bodies[body->getBody()] = body;
}

CCPhysicsBody *CCPhysicsWorld::getBodyByTag(int tag)
{
    for (CCPhysicsBodyMapIterator it = m_bodies.begin(); it != m_bodies.end(); ++it)
    {
        if (it->second->getTag() == tag) return it->second;
    }
    return NULL;
}

void CCPhysicsWorld::removeBodyByTag(int tag, bool unbind/*= true*/)
{
    CCPhysicsBody *body = getBodyByTag(tag);
    if (body) removeBody(body, unbind);
}

void CCPhysicsWorld::removeBody(CCPhysicsBody *body, bool unbind/*= true*/)
{
    CCPhysicsBodyMapIterator it = m_bodies.find(body->getBody());
    if (it != m_bodies.end())
    {
        if (unbind) body->unbind();
        body->release();
        m_bodies.erase(it);
    }
}

void CCPhysicsWorld::removeAllBodies(bool unbind/*= true*/)
{
    for (CCPhysicsBodyMapIterator it = m_bodies.begin(); it != m_bodies.end(); ++it)
    {
        if (unbind) it->second->unbind();
        it->second->release();
    }
    m_bodies.clear();
}

CCPhysicsBody *CCPhysicsWorld::getBodyByCpBody(cpBody *cpBody)
{
    CCPhysicsBodyMapIterator it = m_bodies.find(cpBody);
    return it != m_bodies.end() ? it->second : NULL;
}

void CCPhysicsWorld::start(void)
{
    scheduleUpdate();
}

void CCPhysicsWorld::stop(void)
{
    unscheduleUpdate();
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCPhysicsWorld::addCollisionScriptListener(int handler, int collisionTypeA, int collisionTypeB)
{
    removeCollisionScriptListener(collisionTypeA, collisionTypeB);
    CCPhysicsCollisionProxy *proxy = CCPhysicsCollisionProxy::createWithScriptHandler(this, handler, collisionTypeA, collisionTypeB);
    m_listeners->addObject(proxy);
    
    cpSpaceAddCollisionHandler(m_space,
                               (cpCollisionType)collisionTypeA,
                               (cpCollisionType)collisionTypeB,
                               collisionBeginCallback,
                               collisionPreSolveCallback,
                               collisionPostSolveCallback,
                               collisionSeparateCallback,
                               proxy);
}

void CCPhysicsWorld::removeCollisionScriptListener(int collisionTypeA, int collisionTypeB)
{
    cpSpaceRemoveCollisionHandler(m_space, (cpCollisionType)collisionTypeA, (cpCollisionType)collisionTypeB);
    for (int i = m_listeners->count() - 1; i >= 0; --i)
    {
        CCPhysicsCollisionProxy *proxy = static_cast<CCPhysicsCollisionProxy*>(m_listeners->objectAtIndex(i));
        if (proxy->getCollisionTypeA() == collisionTypeA && proxy->getCollisionTypeB() == collisionTypeB)
        {
            m_listeners->removeObjectAtIndex(i);
        }
    }
}
#endif

void CCPhysicsWorld::removeAllCollisionListeners(void)
{
    for (int i = m_listeners->count() - 1; i >= 0; --i)
    {
        CCPhysicsCollisionProxy *proxy = static_cast<CCPhysicsCollisionProxy*>(m_listeners->objectAtIndex(i));
        cpSpaceRemoveCollisionHandler(m_space, (cpCollisionType)proxy->getCollisionTypeA(), (cpCollisionType)proxy->getCollisionTypeB());
    }
    m_listeners->removeAllObjects();
}

void CCPhysicsWorld::update(float dt)
{
    cpSpaceStep(m_space, dt);
    
    for (CCPhysicsBodyMapIterator it = m_bodies.begin(); it != m_bodies.end(); ++it)
    {
        it->second->update(dt);
    }
}

void CCPhysicsWorld::onExit(void)
{
    stop();
}

int CCPhysicsWorld::collisionBeginCallback(cpArbiter *arbiter, struct cpSpace *space, void *data)
{
    CCPhysicsCollisionProxy *proxy = static_cast<CCPhysicsCollisionProxy*>(data);
    CCPhysicsCollisionEvent *event = CCPhysicsCollisionEvent::create(proxy->getWorld(), arbiter);
    return proxy->collisionBegin(event) ? cpTrue : cpFalse;
}

int CCPhysicsWorld::collisionPreSolveCallback(cpArbiter *arbiter, struct cpSpace *space, void *data)
{
    CCPhysicsCollisionProxy *proxy = static_cast<CCPhysicsCollisionProxy*>(data);
    CCPhysicsCollisionEvent *event = CCPhysicsCollisionEvent::create(proxy->getWorld(), arbiter);
    return proxy->collisionPreSolve(event) ? cpTrue : cpFalse;
}

void CCPhysicsWorld::collisionPostSolveCallback(cpArbiter *arbiter, struct cpSpace *space, void *data)
{
    CCPhysicsCollisionProxy *proxy = static_cast<CCPhysicsCollisionProxy*>(data);
    CCPhysicsCollisionEvent *event = CCPhysicsCollisionEvent::create(proxy->getWorld(), arbiter);
    proxy->collisionPostSolve(event);
}

void CCPhysicsWorld::collisionSeparateCallback(cpArbiter *arbiter, struct cpSpace *space, void *data)
{
    CCPhysicsCollisionProxy *proxy = static_cast<CCPhysicsCollisionProxy*>(data);
    CCPhysicsCollisionEvent *event = CCPhysicsCollisionEvent::create(proxy->getWorld(), arbiter);
    proxy->collisionSeparate(event);
}
