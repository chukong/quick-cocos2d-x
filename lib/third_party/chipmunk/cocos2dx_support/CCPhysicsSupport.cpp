
#include "CCPhysicsSupport.h"
#include "CCPhysicsWorld.h"
#include "CCPhysicsBody.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#include "CCLuaStack.h"
#endif

CCPhysicsVectArray *CCPhysicsVectArray::createFromCCPointArray(CCPointArray *points)
{
    CCPhysicsVectArray *array = new CCPhysicsVectArray();
    array->initWithCCPointArray(points);
    array->autorelease();
    return array;
}

CCPhysicsVectArray *CCPhysicsVectArray::createFromCCPoint(unsigned int numPoints, CCPoint *points)
{
    CCPhysicsVectArray *array = new CCPhysicsVectArray();
    array->initWithCCPoint(points, numPoints);
    array->autorelease();
    return array;
}

CCPhysicsVectArray *CCPhysicsVectArray::createFromLuaTable(int vertexes)
{
    CCPhysicsVectArray *array = new CCPhysicsVectArray();
    array->initWithLuaTable(vertexes);
    array->autorelease();
    return array;
}

CCPhysicsVectArray::~CCPhysicsVectArray(void)
{
    free(m_verts);
}

bool CCPhysicsVectArray::initWithCCPointArray(CCPointArray *points)
{
    CCAssert(points->count() > 0, "CCPhysicsVectArray::initWithCCPointArray() - can't convert empty array");
    m_count = points->count();
    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    for (unsigned int i = 0; i < m_count; ++i)
    {
        const CCPoint pos = points->get(i);
        m_verts[i] = cpv(pos.x, pos.y);
    }
    return true;
}

bool CCPhysicsVectArray::initWithCCPoint(CCPoint *points, unsigned int numPoints)
{
    CCAssert(numPoints > 0, "CCPhysicsVectArray::initWithCCPoint() - can't convert empty array");
    m_count = numPoints;
    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    for (unsigned int i = 0; i < m_count; ++i)
    {
        const CCPoint &pos = points[i];
        m_verts[i] = cpv(pos.x, pos.y);
    }
    return true;
}

bool CCPhysicsVectArray::initWithLuaTable(int vertexes)
{
    lua_State *L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    if (!lua_istable(L, vertexes)) return NULL;

    m_count = 0;
    lua_pushnil(L);
    while (lua_next(L, vertexes) != 0)
    {
        if (lua_istable(L, -1)) m_count++;
        lua_pop(L, 1);
    }

    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    lua_pushnil(L);
    int i = 0;
    while (lua_next(L, vertexes) != 0)
    {
        if (!lua_istable(L, -1)) continue;
        lua_rawgeti(L, -1, 1);
        float x = (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_rawgeti(L, -1, 2);
        float y = (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
        m_verts[i] = cpv(x, y);
        i++;
        lua_pop(L, 1);
    }
    return true;
}

unsigned int CCPhysicsVectArray::count(void)
{
    return m_count;
}

cpVect *CCPhysicsVectArray::data(void)
{
    return m_verts;
}

// ----------------------------------------

CCPhysicsCollisionEvent *CCPhysicsCollisionEvent::create(CCPhysicsWorld *world, cpArbiter *arbiter)
{
    CCPhysicsCollisionEvent *event = new CCPhysicsCollisionEvent(arbiter);
    event->initWithWorld(world);
    event->autorelease();
    return event;
}

CCPhysicsCollisionEvent::~CCPhysicsCollisionEvent(void)
{
}

bool CCPhysicsCollisionEvent::initWithWorld(CCPhysicsWorld *world)
{
    m_world = world;
    cpArbiterGetBodies(m_arbiter, &m_body1, &m_body2);
    return true;
}

CCPhysicsWorld *CCPhysicsCollisionEvent::getWorld(void)
{
    return m_world;
}

CCPhysicsBody *CCPhysicsCollisionEvent::getBody1(void)
{
    return m_world->getBodyByCpBody(m_body1);
}

CCPhysicsBody *CCPhysicsCollisionEvent::getBody2(void)
{
    return m_world->getBodyByCpBody(m_body2);
}

bool CCPhysicsCollisionEvent::isFirstContact(void)
{
    return cpArbiterIsFirstContact(m_arbiter) == cpTrue;
}

float CCPhysicsCollisionEvent::getElasticity(void)
{
    return m_arbiter->e;
}

void CCPhysicsCollisionEvent::setElasticity(float elasticity)
{
    m_arbiter->e = elasticity;
}

float CCPhysicsCollisionEvent::getFriction(void)
{
    return m_arbiter->u;
}

void CCPhysicsCollisionEvent::setFriction(float friction)
{
    m_arbiter->u = friction;
}

const CCPoint CCPhysicsCollisionEvent::getSurfaceVelocities(void)
{
    return CCPoint(m_arbiter->surface_vr.x, m_arbiter->surface_vr.y);
}

void CCPhysicsCollisionEvent::setSurfaceVelocities(const CCPoint velocities)
{
    m_arbiter->surface_vr = cpv(velocities.x, velocities.y);
}

void *CCPhysicsCollisionEvent::getUserData(void)
{
    return m_arbiter->data;
}

void CCPhysicsCollisionEvent::setUserData(void *userdata)
{
    m_arbiter->data = userdata;
}

// ----------------------------------------

CCPhysicsCollisionProxy *CCPhysicsCollisionProxy::createWithDelegate(CCPhysicsWorld *world, CCPhysicsCollisionDelegate *delegate, int collisionTypeA, int collisionTypeB)
{
    CCPhysicsCollisionProxy *proxy = new CCPhysicsCollisionProxy(collisionTypeA, collisionTypeB);
    proxy->initWithDelegate(world, delegate);
    proxy->autorelease();
    return proxy;
}

CCPhysicsCollisionProxy *CCPhysicsCollisionProxy::createWithScriptHandler(CCPhysicsWorld *world, int handler, int collisionTypeA, int collisionTypeB)
{
    CCPhysicsCollisionProxy *proxy = new CCPhysicsCollisionProxy(collisionTypeA, collisionTypeB);
    proxy->initWithScriptHandler(world, handler);
    proxy->autorelease();
    return proxy;
}

CCPhysicsCollisionProxy::~CCPhysicsCollisionProxy(void)
{
    if (m_handler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_handler);
    }
}

bool CCPhysicsCollisionProxy::initWithDelegate(CCPhysicsWorld *world, CCPhysicsCollisionDelegate *delegate)
{
    m_world = world;
    m_delegate = delegate;
    return true;
}

bool CCPhysicsCollisionProxy::initWithScriptHandler(CCPhysicsWorld *world, int handler)
{
    m_world = world;
    m_handler = handler;
    return true;
}

CCPhysicsWorld *CCPhysicsCollisionProxy::getWorld(void)
{
    return m_world;
}

int CCPhysicsCollisionProxy::getCollisionTypeA(void)
{
    return m_collisionTypeA;
}

int CCPhysicsCollisionProxy::getCollisionTypeB(void)
{
    return m_collisionTypeB;
}

bool CCPhysicsCollisionProxy::collisionBegin(CCPhysicsCollisionEvent *event)
{
    if (m_delegate)
    {
        return m_delegate->collisionBegin(event);
    }
    else
    {
        CCLuaEngine *engine = dynamic_cast<CCLuaEngine*>(CCScriptEngineManager::sharedManager()->getScriptEngine());
        CCLuaStack *stack = engine->getLuaStack();
        stack->pushString("begin");
        stack->pushCCObject(event, "CCPhysicsCollisionEvent");
        return stack->executeFunctionByHandler(m_handler, 2) != 0;
    }
}

bool CCPhysicsCollisionProxy::collisionPreSolve(CCPhysicsCollisionEvent *event)
{
    if (m_delegate)
    {
        return m_delegate->collisionPreSolve(event);
    }
    else
    {
        CCLuaEngine *engine = dynamic_cast<CCLuaEngine*>(CCScriptEngineManager::sharedManager()->getScriptEngine());
        CCLuaStack *stack = engine->getLuaStack();
        stack->pushString("preSolve");
        stack->pushCCObject(event, "CCPhysicsCollisionEvent");
        return stack->executeFunctionByHandler(m_handler, 2) != 0;
    }
}

void CCPhysicsCollisionProxy::collisionPostSolve(CCPhysicsCollisionEvent *event)
{
    if (m_delegate)
    {
        m_delegate->collisionPostSolve(event);
    }
    else
    {
        CCLuaEngine *engine = dynamic_cast<CCLuaEngine*>(CCScriptEngineManager::sharedManager()->getScriptEngine());
        CCLuaStack *stack = engine->getLuaStack();
        stack->pushString("postSolve");
        stack->pushCCObject(event, "CCPhysicsCollisionEvent");
        stack->executeFunctionByHandler(m_handler, 2);
    }
}

void CCPhysicsCollisionProxy::collisionSeparate(CCPhysicsCollisionEvent *event)
{
    if (m_delegate)
    {
        m_delegate->collisionSeparate(event);
    }
    else
    {
        CCLuaEngine *engine = dynamic_cast<CCLuaEngine*>(CCScriptEngineManager::sharedManager()->getScriptEngine());
        CCLuaStack *stack = engine->getLuaStack();
        stack->pushString("separate");
        stack->pushCCObject(event, "CCPhysicsCollisionEvent");
        stack->executeFunctionByHandler(m_handler, 2);
    }
}
