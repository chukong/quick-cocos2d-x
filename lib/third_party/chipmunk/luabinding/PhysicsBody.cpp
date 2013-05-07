
#include "PhysicsBody.h"
#include "PhysicsWorld.h"

PhysicsBody *PhysicsBody::defaultStaticBody(PhysicsWorld *world)
{
    PhysicsBody *body = new PhysicsBody(world);
    body->initWithDefaultStaticBody();
    body->autorelease();
    return body;
}

PhysicsBody *PhysicsBody::createStaticBody(PhysicsWorld *world)
{
    PhysicsBody *body = new PhysicsBody(world);
    body->initWithStaticBody();
    body->autorelease();
    return body;
}

PhysicsBody *PhysicsBody::create(PhysicsWorld *world, float mass, float inertia)
{
    PhysicsBody *body = new PhysicsBody(world);
    body->initWithBody(mass, inertia);
    body->autorelease();
    return body;
}

PhysicsBody::PhysicsBody(PhysicsWorld *world)
: m_world(world)
, m_body(NULL)
{
    m_world->retain();
    m_space = m_world->getSpace();
}

PhysicsBody::~PhysicsBody(void)
{
    removeAllShape();
    if (m_body != m_space->staticBody)
    {
        cpSpaceRemoveBody(m_space, m_body);
        cpBodyFree(m_body);
    }
    m_world->release();
}

bool PhysicsBody::initWithDefaultStaticBody(void)
{
    m_body = m_space->staticBody;
    return true;
}

bool PhysicsBody::initWithStaticBody(void)
{
    m_body = cpBodyNewStatic();
    cpSpaceAddBody(m_space, m_body);
    return true;
}

bool PhysicsBody::initWithBody(float mass, float inertia)
{
    m_body = cpBodyNew(mass, inertia);
    cpSpaceAddBody(m_space, m_body);
    return true;
}

void PhysicsBody::setMass(float mass)
{
    cpBodySetMass(m_body, mass);
}

void PhysicsBody::setInertia(float inertia)
{
    cpBodySetMoment(m_body, inertia);
}

int PhysicsBody::addCircleShape(float radius, float offsetX, float offsetY)
{
    cpShape *shape = cpCircleShapeNew(m_body, radius, cpv(offsetX, offsetY));
    cpSpaceAddShape(m_space, shape);
    m_shapes.push_back(shape);
    return m_shapes.size() - 1;
}

void PhysicsBody::removeShapeAtIndex(int index)
{
    CCAssert(index >= 0 && index < m_shapes.size(), "PhysicsBody::removeShapeAtIndex() - Invalid index");
    cpShape *shape = m_shapes[index];
    cpSpaceRemoveShape(m_space, shape);
    cpShapeFree(shape);
    m_shapes.erase(m_shapes.begin() + index);
}

void PhysicsBody::removeAllShape(void)
{
    for (PhysicsShapeVectorIterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
    {
        cpSpaceRemoveShape(m_space, *it);
        cpShapeFree(*it);
    }
    m_shapes.clear();
}
