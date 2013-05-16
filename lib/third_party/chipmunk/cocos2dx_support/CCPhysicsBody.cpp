
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"
#include "CCPhysicsShape.h"

CCPhysicsBody *CCPhysicsBody::defaultStaticBody(CCPhysicsWorld *world)
{
    CCPhysicsBody *body = new CCPhysicsBody(world);
    body->initWithDefaultStaticBody();
    body->autorelease();
    return body;
}

CCPhysicsBody *CCPhysicsBody::createStaticBody(CCPhysicsWorld *world)
{
    CCPhysicsBody *body = new CCPhysicsBody(world);
    body->initWithStaticBody();
    body->autorelease();
    return body;
}

CCPhysicsBody *CCPhysicsBody::create(CCPhysicsWorld *world, float mass, float moment)
{
    CCPhysicsBody *body = new CCPhysicsBody(world);
    body->initWithBody(mass, moment);
    body->autorelease();
    return body;
}

CCPhysicsBody::CCPhysicsBody(CCPhysicsWorld *world)
: m_world(world)
, m_body(NULL)
, m_shapes(NULL)
, m_node(NULL)
, m_tag(0)
{
    m_world->retain();
    m_space = m_world->getSpace();
    m_shapes = CCArray::create();
    m_shapes->retain();
}

CCPhysicsBody::~CCPhysicsBody(void)
{
    removeAllShape();
    if (m_body != m_space->staticBody)
    {
        cpSpaceRemoveBody(m_space, m_body);
        cpBodyFree(m_body);
    }
    CC_SAFE_RELEASE(m_world);
    CC_SAFE_RELEASE(m_shapes);
    CC_SAFE_RELEASE(m_node);
}

bool CCPhysicsBody::initWithDefaultStaticBody(void)
{
    m_body = m_space->staticBody;
    return true;
}

bool CCPhysicsBody::initWithStaticBody(void)
{
    m_body = cpBodyNewStatic();
    return true;
}

bool CCPhysicsBody::initWithBody(float mass, float moment)
{
    m_body = cpBodyNew(mass, moment);
    cpSpaceAddBody(m_space, m_body);
    return true;
}

cpBody *CCPhysicsBody::getBody(void)
{
    return m_body;
}

const char *CCPhysicsBody::getName(void)
{
    return m_name.c_str();
}

void CCPhysicsBody::setName(const char *name)
{
    m_name = name ? name : "";
}

int CCPhysicsBody::getTag(void)
{
    return m_tag;
}

void CCPhysicsBody::setTag(int tag)
{
    m_tag = tag;
}

float CCPhysicsBody::getMass(void)
{
    return cpBodyGetMass(m_body);
}

void CCPhysicsBody::setMass(float mass)
{
    cpBodySetMass(m_body, mass);
}

float CCPhysicsBody::getInertia(void)
{
    return cpBodyGetMoment(m_body);
}

void CCPhysicsBody::setInertia(float inertia)
{
    cpBodySetMoment(m_body, inertia);
}

CCPoint CCPhysicsBody::getVelocity(void)
{
    const cpVect v = cpBodyGetVel(m_body);
    return CCPoint(v.x, v.y);
}

void CCPhysicsBody::getVelocity(float *velocityX, float *velocityY)
{
    const cpVect v = cpBodyGetVel(m_body);
    *velocityX = v.x;
    *velocityY = v.y;
}

void CCPhysicsBody::setVelocity(const CCPoint &velocity)
{
    cpBodySetVel(m_body, cpv(velocity.x, velocity.y));
}

void CCPhysicsBody::setVelocity(CCPhysicsVector* velocity)
{
    cpBodySetVel(m_body, velocity->getVector());
}

void CCPhysicsBody::setVelocity(float velocityX, float velocityY)
{
    cpBodySetVel(m_body, cpv(velocityX, velocityY));
}

float CCPhysicsBody::getVelocityLimit(void)
{
    return cpBodyGetVelLimit(m_body);
}

void CCPhysicsBody::setVelocityLimit(float limit)
{
    cpBodySetVelLimit(m_body, limit);
}

float CCPhysicsBody::getAngleVelocity(void)
{
    return -cpBodyGetAngVel(m_body);
}

void CCPhysicsBody::setAngleVelocity(float velocity)
{
    cpBodySetAngVel(m_body, -velocity);
}

float CCPhysicsBody::getAngleVelocityLimit(void)
{
    return -cpBodyGetAngVelLimit(m_body);
}

void CCPhysicsBody::setAngleVelocityLimit(float limit)
{
    cpBodySetAngVelLimit(m_body, -limit);
}

CCPoint CCPhysicsBody::getForce(void)
{
    const cpVect f = cpBodyGetForce(m_body);
    return CCPoint(f.x, f.y);
}

void CCPhysicsBody::getForce(float *forceX, float *forceY)
{
    const cpVect f = cpBodyGetForce(m_body);
    *forceX = f.x;
    *forceY = f.y;
}

void CCPhysicsBody::setForce(const CCPoint &force)
{
    cpBodySetForce(m_body, cpv(force.x, force.y));
}

void CCPhysicsBody::setForce(CCPhysicsVector *force)
{
    cpBodySetForce(m_body, force->getVector());
}

void CCPhysicsBody::setForce(float forceX, float forceY)
{
    cpBodySetForce(m_body, cpv(forceX, forceY));
}

float CCPhysicsBody::getTorque(void)
{
    return cpBodyGetTorque(m_body);
}

void CCPhysicsBody::setTorque(float force)
{
    cpBodySetTorque(m_body, force);
}

void CCPhysicsBody::resetForces(void)
{
    cpBodyResetForces(m_body);
}

void CCPhysicsBody::applyForce(float forceX, float forceY, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyForce(m_body, cpv(forceX, forceY), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyForce(const CCPoint &force, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyForce(m_body, cpv(force.x, force.y), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyForce(CCPhysicsVector *force, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyForce(m_body, force->getVector(), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyImpulse(float forceX, float forceY, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyImpulse(m_body, cpv(forceX, forceY), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyImpulse(const CCPoint &force, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyImpulse(m_body, cpv(force.x, force.y), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyImpulse(CCPhysicsVector *force, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyImpulse(m_body, force->getVector(), cpv(offsetX, offsetY));
}

CCPoint CCPhysicsBody::getPosition(void)
{
    const cpVect p = cpBodyGetPos(m_body);
    return CCPoint(p.x, p.y);
}

void CCPhysicsBody::getPosition(float *x, float *y)
{
    const cpVect p = cpBodyGetPos(m_body);
    *x = p.x;
    *y = p.y;
}

void CCPhysicsBody::setPosition(float x, float y)
{
    cpBodySetPos(m_body, cpv(x, y));
    cpSpaceReindexShapesForBody(m_space, m_body);
    if (m_node)
    {
        m_node->setPosition(x, y);
    }
}

void CCPhysicsBody::setPosition(const CCPoint &pos)
{
    cpBodySetPos(m_body, cpv(pos.x, pos.y));
    cpSpaceReindexShapesForBody(m_space, m_body);
    if (m_node)
    {
        m_node->setPosition(pos);
    }
}

void CCPhysicsBody::setPosition(CCPhysicsVector *pos)
{
    cpBodySetPos(m_body, pos->getVector());
    cpSpaceReindexShapesForBody(m_space, m_body);
    if (m_node)
    {
        m_node->setPosition(pos->getValue());
    }
}

float CCPhysicsBody::getAngle(void)
{
    return cpBodyGetAngle(m_body);
}

void CCPhysicsBody::setAngle(float angle)
{
    cpBodySetAngle(m_body, angle);
    if (m_node)
    {
        m_node->setRotation(CC_RADIANS_TO_DEGREES(-angle));
    }
}

float CCPhysicsBody::getRotation(void)
{
    return CC_RADIANS_TO_DEGREES(-(cpBodyGetAngle(m_body)));
}

void CCPhysicsBody::setRotation(float rotation)
{
    cpBodySetAngle(m_body, CC_DEGREES_TO_RADIANS(-rotation));
    if (m_node)
    {
        m_node->setRotation(rotation);
    }
}

float CCPhysicsBody::getElasticity(void)
{
    float maxElasticity = -99999;
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        float elasticity = static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->getElasticity();
        if (elasticity > maxElasticity) maxElasticity = elasticity;
    }
    return maxElasticity;
}

void CCPhysicsBody::setElasticity(float elasticity)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setElasticity(elasticity);
    }
}

float CCPhysicsBody::getFriction(void)
{
    float maxFriction = -99999;
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        float friction = static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->getFriction();
        if (friction > maxFriction) maxFriction = friction;
    }
    return maxFriction;
}

void CCPhysicsBody::setFriction(float friction)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setFriction(friction);
    }
}

bool CCPhysicsBody::isSensor(void)
{
    bool isSensor = false;
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        isSensor = isSensor || static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->isSensor();
    }
    return isSensor;
}

void CCPhysicsBody::setIsSensor(bool isSensor)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setIsSensor(isSensor);
    }
}

int CCPhysicsBody::getCollisionType(void)
{
    return m_shapes->count() > 0 ? static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(0))->getCollisionType() : 0;
}

void CCPhysicsBody::setCollisionType(int collisionType)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setCollisionType(collisionType);
    }
}

float CCPhysicsBody::dist(CCPhysicsBody *other)
{
    return cpvdist(cpBodyGetPos(m_body), cpBodyGetPos(other->getBody()));
}

void CCPhysicsBody::bind(CCNode *node)
{
    unbind();
    m_node = node;
    m_node->retain();
    setPosition(m_node->getPosition());
    setRotation(m_node->getRotation());
}

void CCPhysicsBody::unbind(void)
{
    CC_SAFE_RELEASE_NULL(m_node);
}

CCPhysicsShape *CCPhysicsBody::addSegmentShape(const CCPoint lowerLeft, const CCPoint lowerRight, float thickness)
{
    return addShape(cpSegmentShapeNew(m_body, cpv(lowerLeft.x, lowerLeft.y), cpv(lowerRight.x, lowerRight.y), thickness));
}

CCPhysicsShape *CCPhysicsBody::addCircleShape(float radius, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    return addShape(cpCircleShapeNew(m_body, radius, cpv(offsetX, offsetY)));
}

CCPhysicsShape *CCPhysicsBody::addBoxShape(float width, float height)
{
    return addShape(cpBoxShapeNew(m_body, width, height));
}

CCPhysicsShape *CCPhysicsBody::addPolygonShape(CCPointArray *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsVectorArray *cpVertexes = CCPhysicsVectorArray::createFromCCPointArray(vertexes);
    return addPolygonShape(cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}

CCPhysicsShape *CCPhysicsBody::addPolygonShape(int numVertexes, CCPoint *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsVectorArray *cpVertexes = CCPhysicsVectorArray::createFromCCPoint(numVertexes, vertexes);
    return addPolygonShape(cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}

CCPhysicsShape *CCPhysicsBody::addPolygonShape(int numVertexes, cpVect *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    return addShape(cpPolyShapeNew(m_body, numVertexes, vertexes, cpv(offsetX, offsetY)));
}

#if CC_LUA_ENGINE_ENABLED > 0
CCPhysicsShape *CCPhysicsBody::addPolygonShape(int vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsVectorArray *cpVertexes = CCPhysicsVectorArray::createFromLuaTable(vertexes);
    return addPolygonShape(cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}
#endif

void CCPhysicsBody::removeShapeAtIndex(int index)
{
    CCAssert(index >= 0 && index < m_shapes->count(), "CCPhysicsBody::removeShapeAtIndex() - Invalid index");
    CCPhysicsShape *shapeObject = static_cast<CCPhysicsShape *>(m_shapes->objectAtIndex(index));
    cpSpaceRemoveShape(m_space, shapeObject->getShape());
    m_shapes->removeObjectAtIndex(index);
}

void CCPhysicsBody::removeShape(CCPhysicsShape *shapeObject)
{
    removeShapeAtIndex(m_shapes->indexOfObject(shapeObject));
}

void CCPhysicsBody::removeAllShape(void)
{
    for (int index = m_shapes->count(); index > 0; --index)
    {
        CCPhysicsShape *shapeObject = static_cast<CCPhysicsShape *>(m_shapes->objectAtIndex(index));
        cpSpaceRemoveShape(m_space, shapeObject->getShape());
    }
    m_shapes->removeAllObjects();
}

void CCPhysicsBody::update(float dt)
{
    if (!m_node) return;
    m_node->setPosition(getPosition());
    m_node->setRotation(getRotation());
}

CCPhysicsShape *CCPhysicsBody::addShape(cpShape *shape)
{
    cpSpaceAddShape(m_space, shape);
    CCPhysicsShape *shapeObject = CCPhysicsShape::create(shape);
    m_shapes->addObject(shapeObject);
    return shapeObject;
}
