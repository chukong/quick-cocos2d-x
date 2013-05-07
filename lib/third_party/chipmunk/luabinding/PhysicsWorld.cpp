
#include "PhysicsWorld.h"
#include "PhysicsBody.h"
#include "PhysicsDebugNode.h"

using namespace cocos2d;

PhysicsWorld *PhysicsWorld::create(void)
{
    PhysicsWorld *world = new PhysicsWorld();
    world->init();
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

PhysicsDebugNode *PhysicsWorld::createDebugNode(void)
{
    return PhysicsDebugNode::create(m_space);
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

float PhysicsWorld::calcMomentForCircle(float mass, float innerRadius, float outerRadius, float offsetX, float offsetY)
{
    return cpMomentForCircle(mass, innerRadius, outerRadius, cpv(offsetX, offsetY));
}

PhysicsBody *PhysicsWorld::bindNodeToDefaultStaticBody(CCNode *node)
{
    CCAssert(m_bodies.find(node) == m_bodies.end(), "PhysicsWorld::bindNodeToDefaultStaticBody() - Node already in world");

    if (!m_defaultStaticBody)
    {
        m_defaultStaticBody = PhysicsBody::defaultStaticBody(this);
        m_defaultStaticBody->retain();
    }
    
    node->retain();
    m_defaultStaticBody->retain();
    m_bodies[node] = m_defaultStaticBody;
    
    return m_defaultStaticBody;
}

PhysicsBody *PhysicsWorld::bindNodeToNewStaticBody(CCNode *node)
{
    CCAssert(m_bodies.find(node) == m_bodies.end(), "PhysicsWorld::bindNodeToNewStaticBody() - Node already in world");
    PhysicsBody *body = PhysicsBody::createStaticBody(this);
    node->retain();
    body->retain();
    m_bodies[node] = body;
    return body;
}

PhysicsBody *PhysicsWorld::bindNodeToNewBody(CCNode *node, float mass, float moment)
{
    CCAssert(m_bodies.find(node) == m_bodies.end(), "PhysicsWorld::bindNodeToNewBody() - Node already in world");
    PhysicsBody *body = PhysicsBody::create(this, mass, moment);
    node->retain();
    body->retain();
    m_bodies[node] = body;
    return body;
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
