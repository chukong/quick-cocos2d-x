
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
