
#include "PhysicsShape.h"

PhysicsShape *PhysicsShape::create(cpShape *shape)
{
    PhysicsShape *shapeObject = new PhysicsShape(shape);
    shapeObject->autorelease();
    return shapeObject;
}

PhysicsShape::~PhysicsShape(void)
{
    cpShapeFree(m_shape);
}
