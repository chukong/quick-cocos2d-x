
#include "CCPhysicsSupport.h"
#include "CCPhysicsWorld.h"
#include "CCPhysicsBody.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#include "CCLuaStack.h"
#endif

CCPhysicsVector *CCPhysicsVector::create(float x, float y)
{
    CCPhysicsVector *vectorObject = new CCPhysicsVector(x, y);
    vectorObject->autorelease();
    return vectorObject;
}

CCPhysicsVector *CCPhysicsVector::create(const cpVect vector)
{
    CCPhysicsVector *vectorObject = new CCPhysicsVector(vector.x, vector.y);
    vectorObject->autorelease();
    return vectorObject;
}

CCPhysicsVector *CCPhysicsVector::create(const CCPoint vector)
{
    CCPhysicsVector *vectorObject = new CCPhysicsVector(vector.x, vector.y);
    vectorObject->autorelease();
    return vectorObject;
}

CCPhysicsVector *CCPhysicsVector::createForAngle(float angle)
{
    return CCPhysicsVector::create(cpvforangle(angle));
}

CCPhysicsVector *CCPhysicsVector::createForRotation(float degrees)
{
    return CCPhysicsVector::create(cpvforangle(CC_DEGREES_TO_RADIANS(degrees)));
}

CCPhysicsVector::CCPhysicsVector(float x, float y)
{
    m_vector = cpv(x, y);
}

const cpVect CCPhysicsVector::getVector(void)
{
    return m_vector;
}

void CCPhysicsVector::getValue(float *x, float *y)
{
    *x = m_vector.x;
    *y = m_vector.y;
}

const CCPoint CCPhysicsVector::getValue(void)
{
    return CCPoint(m_vector.x, m_vector.y);
}

bool CCPhysicsVector::equal(CCPhysicsVector *other)
{
    return cpveql(m_vector, other->m_vector);
}

bool CCPhysicsVector::equal(float x, float y)
{
    return cpveql(m_vector, cpv(x, y));
}

void CCPhysicsVector::add(CCPhysicsVector *other)
{
    m_vector = cpvadd(m_vector, other->m_vector);
}

void CCPhysicsVector::add(float x, float y)
{
    m_vector = cpvadd(m_vector, cpv(x, y));
}

void CCPhysicsVector::sub(CCPhysicsVector *other)
{
    m_vector = cpvsub(m_vector, other->m_vector);
}

void CCPhysicsVector::sub(float x, float y)
{
    m_vector = cpvsub(m_vector, cpv(x, y));
}

void CCPhysicsVector::negate(void)
{
    m_vector = cpvneg(m_vector);
}

void CCPhysicsVector::multi(float scale)
{
    m_vector = cpvmult(m_vector, scale);
}

float CCPhysicsVector::dot(CCPhysicsVector *other)
{
    return cpvdot(m_vector, other->m_vector);
}

float CCPhysicsVector::dot(float x, float y)
{
    return cpvdot(m_vector, cpv(x, y));
}

float CCPhysicsVector::cross(CCPhysicsVector *other)
{
    return cpvcross(m_vector, other->m_vector);
}

float CCPhysicsVector::cross(float x, float y)
{
    return cpvcross(m_vector, cpv(x, y));
}

CCPhysicsVector *CCPhysicsVector::perp(void)
{
    return CCPhysicsVector::create(cpvperp(m_vector));
}

CCPhysicsVector *CCPhysicsVector::rperp(void)
{
    return CCPhysicsVector::create(cpvrperp(m_vector));
}

void CCPhysicsVector::rotate(CCPhysicsVector *other)
{
    m_vector = cpvrotate(m_vector, other->getVector());
}

void CCPhysicsVector::rotate(float x, float y)
{
    m_vector = cpvrotate(m_vector, cpv(x, y));
}

float CCPhysicsVector::length(void)
{
    return cpvlength(m_vector);
}

float CCPhysicsVector::lengthsq(void)
{
    return cpvlengthsq(m_vector);
}

float CCPhysicsVector::dist(CCPhysicsVector *other)
{
    return cpvdist(m_vector, other->getVector());
}

float CCPhysicsVector::dist(float x, float y)
{
    return cpvdist(m_vector, cpv(x, y));
}

float CCPhysicsVector::distsq(CCPhysicsVector *other)
{
    return cpvdistsq(m_vector, other->getVector());
}

float CCPhysicsVector::distsq(float x, float y)
{
    return cpvdistsq(m_vector, cpv(x, y));
}

float CCPhysicsVector::angle(void)
{
    return cpvtoangle(m_vector);
}

float CCPhysicsVector::rotation(void)
{
    return CC_RADIANS_TO_DEGREES(-cpvtoangle(m_vector));
}

float CCPhysicsVector::sum(void)
{
    return fabsf(m_vector.x) + fabsf(m_vector.y);
}

// ----------------------------------------

CCPhysicsVectorArray *CCPhysicsVectorArray::createFromCCPointArray(CCPointArray *points)
{
    CCPhysicsVectorArray *array = new CCPhysicsVectorArray();
    array->initWithCCPointArray(points);
    array->autorelease();
    return array;
}

CCPhysicsVectorArray *CCPhysicsVectorArray::createFromCCPoint(unsigned int numPoints, CCPoint *points)
{
    CCPhysicsVectorArray *array = new CCPhysicsVectorArray();
    array->initWithCCPoint(points, numPoints);
    array->autorelease();
    return array;
}

CCPhysicsVectorArray *CCPhysicsVectorArray::createFromLuaTable(int vertexes)
{
    CCPhysicsVectorArray *array = new CCPhysicsVectorArray();
    array->initWithLuaTable(vertexes);
    array->autorelease();
    return array;
}

CCPhysicsVectorArray::~CCPhysicsVectorArray(void)
{
    free(m_verts);
}

bool CCPhysicsVectorArray::initWithCCPointArray(CCPointArray *points)
{
    CCAssert(points->count() > 0, "CCPhysicsVectorArray::initWithCCPointArray() - can't convert empty array");
    m_count = points->count();
    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    for (unsigned int i = 0; i < m_count; ++i)
    {
        const CCPoint pos = points->get(i);
        m_verts[i] = cpv(pos.x, pos.y);
    }
    return true;
}

bool CCPhysicsVectorArray::initWithCCPoint(CCPoint *points, unsigned int numPoints)
{
    CCAssert(numPoints > 0, "CCPhysicsVectorArray::initWithCCPoint() - can't convert empty array");
    m_count = numPoints;
    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    for (unsigned int i = 0; i < m_count; ++i)
    {
        const CCPoint &pos = points[i];
        m_verts[i] = cpv(pos.x, pos.y);
    }
    return true;
}

bool CCPhysicsVectorArray::initWithLuaTable(int vertexes)
{
    lua_State *L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    if (!lua_istable(L, vertexes)) return NULL;

    m_count = 0;
    do
    {
        lua_rawgeti(L, -1, m_count + 1);
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            break;
        }
        lua_pop(L, 1);
        m_count++;
    } while (true);

    if (m_count == 0 || m_count % 2 != 0)
    {
        m_count = 0;
        return false;
    }

    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    int vertIndex = 0;
    for (int i = 0; i < m_count; i += 2)
    {
        lua_rawgeti(L, -1, i + 1);
        float x = (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_rawgeti(L, -1, i + 2);
        float y = (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
        m_verts[vertIndex] = cpv(x, y);
        vertIndex++;
    }

    m_count = m_count / 2;
    return true;
}

unsigned int CCPhysicsVectorArray::count(void)
{
    return m_count;
}

cpVect *CCPhysicsVectorArray::data(void)
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

void CCPhysicsCollisionEvent::getSurfaceVelocities(float *velocityX, float *velocityY)
{
    *velocityX = m_arbiter->surface_vr.x;
    *velocityY = m_arbiter->surface_vr.y;
}

void CCPhysicsCollisionEvent::setSurfaceVelocities(float velocityX, float velocityY)
{
    m_arbiter->surface_vr = cpv(velocityX, velocityY);
}

void CCPhysicsCollisionEvent::setSurfaceVelocities(const CCPoint velocity)
{
    m_arbiter->surface_vr = cpv(velocity.x, velocity.y);
}

int CCPhysicsCollisionEvent::getCount(void)
{
    return cpArbiterGetCount(m_arbiter);
}

const CCPoint CCPhysicsCollisionEvent::getNormal(int index)
{
    const cpVect v = cpArbiterGetNormal(m_arbiter, index);
    return CCPoint(v.x, v.y);
}

void CCPhysicsCollisionEvent::getNormal(int index, float *x, float *y)
{
    const cpVect v = cpArbiterGetNormal(m_arbiter, index);
    *x = v.x;
    *y = v.y;
}

const CCPoint CCPhysicsCollisionEvent::getPoint(int index)
{
    const cpVect v = cpArbiterGetPoint(m_arbiter, index);
    return CCPoint(v.x, v.y);
}

void CCPhysicsCollisionEvent::getPoint(int index, float *x, float *y)
{
    const cpVect v = cpArbiterGetPoint(m_arbiter, index);
    *x = v.x;
    *y = v.y;
}

float CCPhysicsCollisionEvent::getDepth(int index)
{
    return cpArbiterGetDepth(m_arbiter, index);
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
