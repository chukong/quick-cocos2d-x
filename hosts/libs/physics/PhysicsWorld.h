

#ifndef __PHYSICS_WORLD_H_
#define __PHYSICS_WORLD_H_

#include "cocos2d.h"
#include "Box2D.h"

using namespace cocos2d;

class PhysicsWorld : public CCNode
{
public:
    static PhysicsWorld *create(void);
    ~PhysicsWorld(void);
    
    void setGravity(float gravityX, float gravityY) {
        m_gravityX = gravityX;
        m_gravityY = gravityY;
        b2Vec2 gravity(m_gravityX, m_gravityY);
        m_world->SetGravity(gravity);
    }
    void getGravity(float *gravityX, float *gravityY) {
        const b2Vec2 &gravity = m_world->GetGravity();
        *gravityX = gravity.x;
        *gravityY = gravity.y;
    }
    
    void setScale(float scale) {
        m_scale = scale;
    }
    float getScale(void) {
        return m_scale;
    }
    
    void setVelocityIterations(int velocityIterations) {
        m_velocityIterations = velocityIterations;
    }
    int getVelocityIterations(void) {
        return m_velocityIterations;
    }
    
    void setPositionIterations(int positionIterations) {
        m_positionIterations = positionIterations;
    }
    int getPositionIterations(void) {
        return m_positionIterations;
    }
    
    bool addCircleBody(CCNode *target,
                       b2BodyType bodyType,
                       float radius,
                       float density,
                       float friction,
                       float bounce,
                       int filter);
    
    bool removeBody(CCNode *target);

    void start(bool allowSleep);
    void stop(void);
    
    virtual void update(float dt);
    
private:
    PhysicsWorld(void);
    bool init(void);
    
    b2World        *m_world;
    float           m_stepInterval;
    float           m_gravityX;
    float           m_gravityY;
    float           m_scale;
    int             m_velocityIterations;
    int             m_positionIterations;
};

#endif // __PHYSICS_WORLD_H_
