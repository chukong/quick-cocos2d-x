
#include "PhysicsWorld.h"

PhysicsWorld *PhysicsWorld::create(void)
{
    PhysicsWorld *world = new PhysicsWorld();
    world->init();
    world->autorelease();
    return world;
}

PhysicsWorld::PhysicsWorld(void)
: m_world(NULL)
, m_stepInterval(1.0f / 60)
, m_gravityX(0)
, m_gravityY(9.8)
, m_scale(60)
, m_velocityIterations(3)
, m_positionIterations(8)
{
}

PhysicsWorld::~PhysicsWorld(void)
{
    b2Body *body = m_world->GetBodyList();
    while (body)
    {
        static_cast<CCNode*>(body->GetUserData())->release();
        body = body->GetNext();
    }
    CC_SAFE_DELETE(m_world);
}

bool PhysicsWorld::init(void)
{
    b2Vec2 gravity(m_gravityX, m_gravityY);
    m_world = new b2World(gravity);
    m_world->SetAllowSleeping(true);
    return true;
}

bool PhysicsWorld::addCircleBody(CCNode *target,
                                 b2BodyType bodyType,
                                 float radius,
                                 float density,
                                 float friction,
                                 float bounce,
                                 int filter)
{
    const CCPoint &pos = target->getPosition();

    b2BodyDef def;
    def.type = bodyType;
    def.position.Set(pos.x, pos.y);
    
    b2CircleShape shape;
    shape.m_radius = radius;
    
    b2Body *body = m_world->CreateBody(&def);
    if (!body) return false;

    target->retain();
    body->SetUserData(target);

    b2Fixture *fixture = body->CreateFixture(&shape, density);
    fixture->SetFriction(friction);
    fixture->SetRestitution(bounce);
    
    return true;
}

bool PhysicsWorld::removeBody(CCNode *target)
{
    b2Body *body = m_world->GetBodyList();
    CCNode *node;
    while (body)
    {
        node = static_cast<CCNode*>(body->GetUserData());
        body = body->GetNext();
        if (node == target)
        {
            node->release();
            m_world->DestroyBody(body);
            return true;
        }
    }
    return false;
}

void PhysicsWorld::start(bool allowSleep)
{
    m_stepInterval = CCDirector::sharedDirector()->getAnimationInterval();
    m_world->SetAllowSleeping(allowSleep);
    scheduleUpdate();
}

void PhysicsWorld::stop(void)
{
    unscheduleUpdate();
}

void PhysicsWorld::update(float dt)
{
    m_world->Step(m_stepInterval, m_velocityIterations, m_positionIterations);
    CCNode *node;
    b2Body *body = m_world->GetBodyList();
    while (body)
    {
        node = static_cast<CCNode*>(body->GetUserData());
        const b2Vec2& pos = body->GetPosition();
        node->setPosition(ccp(pos.x, pos.y));
        node->setRotation(CC_RADIANS_TO_DEGREES(body->GetAngle()));
        body = body->GetNext();
    }
}
