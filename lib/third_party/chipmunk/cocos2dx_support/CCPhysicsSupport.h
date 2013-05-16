
#ifndef __CCPHYSICS_WORLD_DATA_SUPPORT_H_
#define __CCPHYSICS_WORLD_DATA_SUPPORT_H_

#include "cocos2d.h"
#include "chipmunk.h"
#include "CCScriptSupport.h"

using namespace cocos2d;

class CCPhysicsVectArray : public CCObject
{
public:
    static CCPhysicsVectArray *createFromCCPointArray(CCPointArray *points);
    static CCPhysicsVectArray *createFromCCPoint(unsigned int numPoints, CCPoint *points);

#if CC_LUA_ENGINE_ENABLED > 0
    static CCPhysicsVectArray *createFromLuaTable(int vertexes);
#endif

    ~CCPhysicsVectArray(void);

    unsigned int count(void);
    cpVect *data(void);

private:
    CCPhysicsVectArray(void)
    : m_verts(NULL)
    , m_count(0)
    {
    }
    bool initWithCCPointArray(CCPointArray *points);
    bool initWithCCPoint(CCPoint *points, unsigned int numPoints);

#if CC_LUA_ENGINE_ENABLED > 0
    bool initWithLuaTable(int vertexes);
#endif

    cpVect *m_verts;
    unsigned int m_count;
};

// ----------------------------------------

class CCPhysicsWorld;
class CCPhysicsBody;

class CCPhysicsCollisionEvent : public CCObject
{
public:
    static CCPhysicsCollisionEvent *create(CCPhysicsWorld *world, cpArbiter *arbiter);
    ~CCPhysicsCollisionEvent(void);

    CCPhysicsWorld *getWorld(void);

    CCPhysicsBody *getBody1(void);
    CCPhysicsBody *getBody2(void);

    bool isFirstContact(void);

    float getElasticity(void);
    void setElasticity(float elasticity);

    float getFriction(void);
    void setFriction(float friction);

    const CCPoint getSurfaceVelocities(void);
    void setSurfaceVelocities(const CCPoint velocities);

    void *getUserData(void);
    void setUserData(void *userdata);

private:
    CCPhysicsCollisionEvent(cpArbiter *arbiter)
    : m_world(NULL)
    , m_arbiter(arbiter)
    , m_body1(NULL)
    , m_body2(NULL)
    {
    }
    bool initWithWorld(CCPhysicsWorld *world);

    CCPhysicsWorld *m_world;
    cpArbiter *m_arbiter;
    cpBody *m_body1;
    cpBody *m_body2;
};

// ----------------------------------------

class CCPhysicsCollisionDelegate
{
public:
    virtual bool collisionBegin(CCPhysicsCollisionEvent *event) { return true; }
    virtual bool collisionPreSolve(CCPhysicsCollisionEvent *event) { return true; }
    virtual void collisionPostSolve(CCPhysicsCollisionEvent *event) {}
    virtual void collisionSeparate(CCPhysicsCollisionEvent *event) {}
};

// ----------------------------------------

class CCPhysicsCollisionProxy : public CCPhysicsCollisionDelegate, public CCObject
{
public:
    static CCPhysicsCollisionProxy *createWithDelegate(CCPhysicsWorld *world, CCPhysicsCollisionDelegate *delegate, int collisionTypeA, int collisionTypeB);
    static CCPhysicsCollisionProxy *createWithScriptHandler(CCPhysicsWorld *world, int handler, int collisionTypeA, int collisionTypeB);
    ~CCPhysicsCollisionProxy(void);

    CCPhysicsWorld *getWorld(void);
    int getCollisionTypeA(void);
    int getCollisionTypeB(void);

    virtual bool collisionBegin(CCPhysicsCollisionEvent *event);
    virtual bool collisionPreSolve(CCPhysicsCollisionEvent *event);
    virtual void collisionPostSolve(CCPhysicsCollisionEvent *event);
    virtual void collisionSeparate(CCPhysicsCollisionEvent *event);

private:
    CCPhysicsCollisionProxy(int collisionTypeA, int collisionTypeB)
    : m_world(NULL)
    , m_delegate(NULL)
    , m_handler(0)
    , m_collisionTypeA(collisionTypeA)
    , m_collisionTypeB(collisionTypeB)
    {
    }
    bool initWithDelegate(CCPhysicsWorld *world, CCPhysicsCollisionDelegate *delegate);
    bool initWithScriptHandler(CCPhysicsWorld *world, int handler);

    CCPhysicsWorld *m_world;
    CCPhysicsCollisionDelegate *m_delegate;
    int m_handler;
    int m_collisionTypeA;
    int m_collisionTypeB;
};

#endif // __CCPHYSICS_WORLD_DATA_SUPPORT_H_
