
#include "CCPhysicsShape.h"

CCPhysicsShape *CCPhysicsShape::create(cpShape *shape)
{
    CCPhysicsShape *shapeObject = new CCPhysicsShape(shape);
    shapeObject->autorelease();
    return shapeObject;
}

CCPhysicsShape::~CCPhysicsShape(void)
{
    cpShapeFree(m_shape);
}

cpShape *CCPhysicsShape::getShape(void)
{
    return m_shape;
}

float CCPhysicsShape::getElasticity(void)
{
    return cpShapeGetElasticity(m_shape);
}

void CCPhysicsShape::setElasticity(float elasticity)
{
    cpShapeSetElasticity(m_shape, elasticity);
}

float CCPhysicsShape::getFriction(void)
{
    return cpShapeGetFriction(m_shape);
}

void CCPhysicsShape::setFriction(float friction)
{
    cpShapeSetFriction(m_shape, friction);
}

bool CCPhysicsShape::isSensor(void) {
    return cpShapeGetSensor(m_shape);
}

void CCPhysicsShape::setIsSensor(bool isSensor) {
    cpShapeSetSensor(m_shape, isSensor);
}

int CCPhysicsShape::getCollisionType(void)
{
    return cpShapeGetCollisionType(m_shape);
}

void CCPhysicsShape::setCollisionType(int collisionType)
{
    cpShapeSetCollisionType(m_shape, (cpCollisionType)collisionType);
}

bool CCPhysicsShape::isMarkedRemove(void)
{
	return m_postRemove;
}

void CCPhysicsShape::markRemove(void)
{
	m_postRemove = true;
}
