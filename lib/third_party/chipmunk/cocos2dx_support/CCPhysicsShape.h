
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

    cpShape *getShape(void);

    float getElasticity(void);
    void setElasticity(float elasticity);

    float getFriction(void);
    void setFriction(float friction);

    bool isSensor(void);
    void setIsSensor(bool isSensor);

    int getCollisionType(void);
    void setCollisionType(int collisionType);

	bool isMarkRemoved(void);
	void markRemoved(void);

private:
    CCPhysicsShape(cpShape *shape)
    : m_shape(shape)
	, m_isRemoved(false)
    {
    }

    cpShape *m_shape;
	bool m_isRemoved;
};

#endif // __CCPHYSICS_SHAPE_H_
