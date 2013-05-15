
#include "CCPhysicsWorld.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsDebugNode.h"

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
    CC_SAFE_RELEASE(m_bodies);
    CC_SAFE_RELEASE(m_defaultStaticBody);
    cpSpaceFree(m_space);
}

bool CCPhysicsWorld::init(void)
{
    m_space = cpSpaceNew();
    cpSpaceSetGravity(m_space, cpvzero);
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

CCPhysicsBody *CCPhysicsWorld::addCircleShape(float mass, float radius, float offsetX/*= 0*/, float offsetY/*= 0*/)
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
    return body;
}

CCPhysicsBody *CCPhysicsWorld::addBoxShape(float mass, float width, float height)
{
    float moment = cpMomentForBox(mass, width, height);
    CCPhysicsBody *body = CCPhysicsBody::create(this, mass, moment);
    body->addBoxShape(width, height);
    return body;
}

CCPhysicsBody *CCPhysicsWorld::addPolygonShape(float mass, CCPointArray *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpVectArray *cpVertexes = cpVectArray::createFromCCPointArray(vertexes);
    return addPolygonShape(mass, cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}

CCPhysicsBody *CCPhysicsWorld::addPolygonShape(float mass, cpVectArray *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    return addPolygonShape(mass, vertexes->count(), vertexes->data(), offsetX, offsetY);
}

CCPhysicsBody *CCPhysicsWorld::addPolygonShape(float mass, int numVertexes, cpVect *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    float moment = cpMomentForPoly(mass, numVertexes, vertexes, cpv(offsetX, offsetY));
    CCPhysicsBody *body = CCPhysicsBody::create(this, mass, moment);
    body->addPolygonShape(numVertexes, vertexes, offsetX, offsetY);
    return body;
}

#if CC_LUA_ENGINE_ENABLED > 0
CCPhysicsBody *CCPhysicsWorld::addPolygonShape(float mass, int vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpVectArray *cpVertexes = cpVectArray::createFromLuaTable(vertexes);
    return addPolygonShape(mass, cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}
#endif

void CCPhysicsWorld::bindNodeToBody(CCNode *node, CCPhysicsBody *body)
{
    CCAssert(node != NULL, "CCPhysicsWorld::bindNodeToBody() - invalid node");
    CCAssert(body != NULL, "CCPhysicsWorld::bindNodeToBody() - invalid body");
    CCAssert(m_bodies.find(node) == m_bodies.end(), "CCPhysicsWorld::bindNodeToBody() - Node already in world");
    node->retain();
    body->retain();
    m_bodies[node] = body;
}

void CCPhysicsWorld::unbindNode(CCNode *node)
{
    PhysicsWorldBodyMapIterator it = m_bodies.find(node);
    CCAssert(it != m_bodies.end(), "CCPhysicsWorld::unbindNode() - Node not in world");
    node->release();
    it->second->release();
    m_bodies.erase(it);
}

void CCPhysicsWorld::unbindAllNodes(void)
{
    for (PhysicsWorldBodyMapIterator it = m_bodies.begin(); it != m_bodies.end(); ++it)
    {
        it->first->release();
        it->second->release();
    }
    m_bodies.clear();
}

CCPhysicsBody *CCPhysicsWorld::getBodyByNode(CCNode *node)
{
    PhysicsWorldBodyMapIterator it = m_bodies.find(node);
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

void CCPhysicsWorld::update(float dt)
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

void CCPhysicsWorld::onExit(void)
{
    stop();
}
