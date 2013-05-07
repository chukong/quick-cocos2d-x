
#include "PhysicsBody.h"
#include "PhysicsWorld.h"
#include "PhysicsShape.h"

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

PhysicsBody *PhysicsBody::create(PhysicsWorld *world, float mass, float moment)
{
    PhysicsBody *body = new PhysicsBody(world);
    body->initWithBody(mass, moment);
    body->autorelease();
    return body;
}

PhysicsBody::PhysicsBody(PhysicsWorld *world)
: m_world(world)
, m_body(NULL)
, m_shapes(NULL)
{
    m_world->retain();
    m_space = m_world->getSpace();
    m_shapes = CCArray::create();
    m_shapes->retain();
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
    m_shapes->release();
}

bool PhysicsBody::initWithDefaultStaticBody(void)
{
    m_body = m_space->staticBody;
    return true;
}

bool PhysicsBody::initWithStaticBody(void)
{
    m_body = cpBodyNewStatic();
    return true;
}

bool PhysicsBody::initWithBody(float mass, float moment)
{
    m_body = cpBodyNew(mass, moment);
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

void PhysicsBody::setPosition(float x, float y)
{
    cpBodySetPos(m_body, cpv(x, y));
    cpSpaceReindexShapesForBody(m_space, m_body);
}

PhysicsShape *PhysicsBody::addSegmentShape(float lowerLeftX, float lowerLeftY, float lowerRightX, float lowerRightY, float thickness)
{
    return addShape(cpSegmentShapeNew(m_body, cpv(lowerLeftX, lowerLeftY), cpv(lowerRightX, lowerRightY), thickness));
}

PhysicsShape *PhysicsBody::addCircleShape(float radius, float offsetX, float offsetY)
{
    return addShape(cpCircleShapeNew(m_body, radius, cpv(offsetX, offsetY)));
}

PhysicsShape *PhysicsBody::addBoxShape(float width, float height)
{
    return addShape(cpBoxShapeNew(m_body, width, height));
}

void PhysicsBody::removeShapeAtIndex(int index)
{
    CCAssert(index >= 0 && index < m_shapes->count(), "PhysicsBody::removeShapeAtIndex() - Invalid index");
    PhysicsShape *shapeObject = static_cast<PhysicsShape*>(m_shapes->objectAtIndex(index));
    cpSpaceRemoveShape(m_space, shapeObject->getShape());
    m_shapes->removeObjectAtIndex(index);
}

void PhysicsBody::removeShape(PhysicsShape *shapeObject)
{
    removeShapeAtIndex(m_shapes->indexOfObject(shapeObject));
}

void PhysicsBody::removeAllShape(void)
{
    for (int index = m_shapes->count(); index > 0; --index)
    {
        PhysicsShape *shapeObject = static_cast<PhysicsShape*>(m_shapes->objectAtIndex(index));
        cpSpaceRemoveShape(m_space, shapeObject->getShape());
    }
    m_shapes->removeAllObjects();
}

PhysicsShape *PhysicsBody::addShape(cpShape *shape)
{
    cpSpaceAddShape(m_space, shape);
    PhysicsShape *shapeObject = PhysicsShape::create(shape);
    m_shapes->addObject(shapeObject);
    return shapeObject;
}
