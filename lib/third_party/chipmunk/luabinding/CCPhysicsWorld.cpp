
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
    m_bodies = CCArray::create();
    m_bodies->retain();
    m_space = cpSpaceNew();
    cpSpaceSetGravity(m_space, cpvzero);
    cpSpaceSetUserData(m_space, (cpDataPointer)this);
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
    cpVectArray *cpVertexes = cpVectArray::createFromCCPointArray(vertexes);
    return createPolygonBody(mass, cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}

CCPhysicsBody *CCPhysicsWorld::createPolygonBody(float mass, cpVectArray *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
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
    cpVectArray *cpVertexes = cpVectArray::createFromLuaTable(vertexes);
    return createPolygonBody(mass, cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}
#endif

void CCPhysicsWorld::addBody(CCPhysicsBody *body)
{
    m_bodies->addObject(body);
}

CCPhysicsBody *CCPhysicsWorld::getBodyByTag(int tag)
{
    for (int i = m_bodies->count(); i >= 0; --i)
    {
        CCPhysicsBody *body = static_cast<CCPhysicsBody*>(m_bodies->objectAtIndex(i));
        if (body->getTag() == tag) return body;
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
    int i = m_bodies->indexOfObject(body);
    if (i >= 0)
    {
        if (unbind) body->unbind();
        m_bodies->removeObjectAtIndex(i, true);
    }
}

void CCPhysicsWorld::removeAllBodies(bool unbind/*= true*/)
{
    for (int i = m_bodies->count(); i >= 0; --i)
    {
        CCPhysicsBody *body = static_cast<CCPhysicsBody*>(m_bodies->objectAtIndex(i));
        if (unbind) body->unbind();
    }
    m_bodies->removeAllObjects();
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
    cpSpaceStep(m_space, dt);

    for (int i = m_bodies->count(); i >= 0; --i)
    {
        CCPhysicsBody *body = static_cast<CCPhysicsBody*>(m_bodies->objectAtIndex(i));
        body->update(dt);
    }
}

void CCPhysicsWorld::onExit(void)
{
    stop();
}
