
#include "PhysicsWorld.h"
#include "PhysicsBody.h"
#include "PhysicsDebugNode.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#include "CCLuaStack.h"
#endif

using namespace cocos2d;

cpVectArray *cpVectArray::createFromCCPointArray(CCPointArray *points)
{
    cpVectArray *array = new cpVectArray();
    array->initWithCCPointArray(points);
    array->autorelease();
    return array;
}

cpVectArray::~cpVectArray(void)
{
    free(m_verts);
}

bool cpVectArray::initWithCCPointArray(CCPointArray *points)
{
    CCAssert(points->count() > 0, "cpVectArray::initWithCCPointArray() - can't convert empty array");
    m_count = points->count();
    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    for (int i = 0; i < m_count; ++i)
    {
        const CCPoint pos = points->get(i);
        m_verts[i] = cpv(pos.x, pos.y);
    }
    return true;
}

// ----------------------------------------

PhysicsWorld *PhysicsWorld::create(void)
{
    PhysicsWorld *world = new PhysicsWorld();
    world->init();
    world->autorelease();
    return world;
}

PhysicsWorld *PhysicsWorld::create(float gravityX, float gravityY)
{
    PhysicsWorld *world = new PhysicsWorld();
    world->init();
    world->setGravity(gravityX, gravityY);
    world->autorelease();
    return world;
}

PhysicsWorld::~PhysicsWorld(void)
{
    unbindAllNodes();
    CC_SAFE_RELEASE(m_defaultStaticBody);
    cpSpaceFree(m_space);
}

bool PhysicsWorld::init(void)
{
    m_space = cpSpaceNew();
    cpSpaceSetGravity(m_space, cpvzero);
    return true;
}

cpSpace *PhysicsWorld::getSpace(void)
{
    return m_space;
}

PhysicsDebugNode *PhysicsWorld::createDebugNode(void)
{
    return PhysicsDebugNode::create(m_space);
}

const CCPoint PhysicsWorld::getGravity(void)
{
    const cpVect gravity = cpSpaceGetGravity(m_space);
    return CCPoint(gravity.x, gravity.y);
}

void PhysicsWorld::getGravity(float *gravityX, float *gravityY)
{
    const cpVect gravity = cpSpaceGetGravity(m_space);
    *gravityX = gravity.x;
    *gravityY = gravity.y;
}

void PhysicsWorld::setGravity(float gravityX, float gravityY)
{
    cpSpaceSetGravity(m_space, cpv(gravityX, gravityY));
}

PhysicsBody *PhysicsWorld::addCircleShape(float mass, float radius, const CCPoint offset/*= CCPointZero*/)
{
    return addCircleShape(mass, radius, offset.x, offset.y);
}

PhysicsBody *PhysicsWorld::addCircleShape(float mass, float radius, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    PhysicsBody *body;
    if (mass <= 0)
    {
        body = PhysicsBody::createStaticBody(this);
    }
    else
    {
        float moment = cpMomentForCircle(mass, 0, radius, cpv(offsetX, offsetY));
        body = PhysicsBody::create(this, mass, moment);
    }
    body->addCircleShape(radius, offsetX, offsetY);
    return body;
}

PhysicsBody *PhysicsWorld::addBoxShape(float mass, float width, float height)
{
    float moment = cpMomentForBox(mass, width, height);
    PhysicsBody *body = PhysicsBody::create(this, mass, moment);
    body->addBoxShape(width, height);
    return body;
}

PhysicsBody *PhysicsWorld::addPolygonShape(float mass, CCPointArray *vertexes, const CCPoint offset/*= CCPointZero*/)
{
    return addPolygonShape(mass, vertexes, offset.x, offset.y);
}

PhysicsBody *PhysicsWorld::addPolygonShape(float mass, CCPointArray *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpVectArray *verts = cpVectArray::createFromCCPointArray(vertexes);
    float moment = cpMomentForPoly(mass, verts->count(), verts->data(), cpv(offsetX, offsetY));
    PhysicsBody *body = PhysicsBody::create(this, mass, moment);
    body->addPolygonShape(verts->count(), verts->data(), offsetY, offsetY);
    return body;
}

#if CC_LUA_ENGINE_ENABLED > 0
PhysicsBody *PhysicsWorld::addPolygonShape(float mass, int vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    lua_State *L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    if (!lua_istable(L, vertexes)) return NULL;
    
    // count
    int count = 0;
    lua_pushnil(L);
    while (lua_next(L, vertexes) != 0)
    {
        if (lua_istable(L, -1)) count++;
        lua_pop(L, 1);
    }
    
    cpVect *verts = (cpVect*)malloc(sizeof(cpVect) * count);
    lua_pushnil(L);
    count = 0;
    while (lua_next(L, vertexes) != 0)
    {
        if (!lua_istable(L, -1)) continue;
        lua_rawgeti(L, -1, 1);
        float x = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_rawgeti(L, -1, 2);
        float y = lua_tonumber(L, -1);
        lua_pop(L, 1);
        verts[count] = cpv(x, y);
        count++;
        lua_pop(L, 1);
    }
        
    float moment = cpMomentForPoly(mass, count, verts, cpv(offsetX, offsetY));
    CCAssert(moment == moment, "PhysicsWorld::addPolygonShape() - invalid moment");
    PhysicsBody *body = PhysicsBody::create(this, mass, moment);
    body->addPolygonShape(count, verts, offsetY, offsetY);
    return body;
}
#endif

void PhysicsWorld::bindNodeToBody(CCNode *node, PhysicsBody *body)
{
    CCAssert(node != NULL, "PhysicsWorld::bindNodeToBody() - invalid node");
    CCAssert(body != NULL, "PhysicsWorld::bindNodeToBody() - invalid body");
    CCAssert(m_bodies.find(node) == m_bodies.end(), "PhysicsWorld::bindNodeToBody() - Node already in world");
    node->retain();
    body->retain();
    m_bodies[node] = body;
}

void PhysicsWorld::unbindNode(CCNode *node)
{
    PhysicsWorldBodyMapIterator it = m_bodies.find(node);
    CCAssert(it != m_bodies.end(), "PhysicsWorld::unbindNode() - Node not in world");
    node->release();
    it->second->release();
    m_bodies.erase(it);
}

void PhysicsWorld::unbindAllNodes(void)
{
    for (PhysicsWorldBodyMapIterator it = m_bodies.begin(); it != m_bodies.end(); ++it)
    {
        it->first->release();
        it->second->release();
    }
    m_bodies.clear();
}

PhysicsBody *PhysicsWorld::getBodyByNode(CCNode *node)
{
    PhysicsWorldBodyMapIterator it = m_bodies.find(node);
    return it != m_bodies.end() ? it->second : NULL;
}

void PhysicsWorld::start(void)
{
    scheduleUpdate();
}

void PhysicsWorld::stop(void)
{
    unscheduleUpdate();
}

void PhysicsWorld::update(float dt)
{
    for (PhysicsWorldBodyMapIterator it = m_bodies.begin(); it != m_bodies.end(); ++it)
    {
        cpBody *body = it->second->getBody();
        const cpVect pos = cpBodyGetPos(body);

        CCNode *node = it->first;
        node->setRotation(-CC_RADIANS_TO_DEGREES(cpBodyGetAngle(body)));
        node->setPosition(pos.x, pos.y);
    }

    cpSpaceStep(m_space, dt);
}

void PhysicsWorld::onExit(void)
{
    stop();
}
