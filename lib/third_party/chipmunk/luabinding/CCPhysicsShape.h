
#ifndef __CCPHYSICS_SHAPE_H_
#define __CCPHYSICS_SHAPE_H_

#include "cocos2d.h"
#include "chipmunk.h"

using namespace cocos2d;

class CCPhysicsShape : public CCObject
{
public:
    static CCPhysicsShape *create(cpShape *shape);
    ~CCPhysicsShape(void);

    cpShape *getShape(void) {
        return m_shape;
    }

    float getElasticity(void) {
        return cpShapeGetElasticity(m_shape);
    }
    void setElasticity(float elasticity) {
        cpShapeSetElasticity(m_shape, elasticity);
    }

    float getFriction(void) {
        return cpShapeGetFriction(m_shape);
    }
    void setFriction(float friction) {
        cpShapeSetFriction(m_shape, friction);
    }

private:
    CCPhysicsShape(cpShape *shape)
    : m_shape(shape)
    {
    }

    cpShape *m_shape;
};

#endif // __CCPHYSICS_SHAPE_H_
