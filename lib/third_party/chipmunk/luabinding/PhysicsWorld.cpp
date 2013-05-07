
#include "PhysicsWorld.h"
#include "PhysicsBody.h"

using namespace cocos2d;

int PhysicsWorld::m_nodeId = 0;

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
    cpSpaceSetGravity(m_space, m_gravity);
    return true;
}

void PhysicsWorld::getGravity(float *gravityX, float *gravityY)
{
    *gravityX = m_gravity.x;
    *gravityY = m_gravity.y;
}

void PhysicsWorld::setGravity(float gravityX, float gravityY)
{
    m_gravity = cpv(gravityX, gravityY);
    cpSpaceSetGravity(m_space, m_gravity);
}

int PhysicsWorld::getDrawMode(void)
{
    return m_drawMode;
}

void PhysicsWorld::setDrawMode(int drawMode)
{
    m_drawMode = drawMode;
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

PhysicsBody *PhysicsWorld::bindNodeToNewBody(CCNode *node, float mass, float inertia /* = 0 */)
{
    CCAssert(m_bodies.find(node) == m_bodies.end(), "PhysicsWorld::bindNodeToNewBody() - Node already in world");
    PhysicsBody *body = PhysicsBody::create(this, mass, inertia);
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

void PhysicsWorld::start(bool allowSleep)
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
        node->setRotation(cpBodyGetAngle(body));
        node->setPosition(pos.x, pos.y);
    }
    
    cpSpaceStep(m_space, dt);
}
