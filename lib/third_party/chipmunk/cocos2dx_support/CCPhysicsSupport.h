
#ifndef __CCPHYSICS_WORLD_DATA_SUPPORT_H_
#define __CCPHYSICS_WORLD_DATA_SUPPORT_H_

#include "cocos2d.h"
#include "chipmunk.h"
#include "script_support/CCScriptSupport.h"

using namespace cocos2d;

class CCPhysicsVector : public CCObject
{
public:
    static CCPhysicsVector *create(float x, float y);
    static CCPhysicsVector *create(const cpVect vector);
    static CCPhysicsVector *create(const CCPoint vector);
    
    // Returns the unit length vector for the given angle (in radians).
    static CCPhysicsVector *createForAngle(float angle);
    
    // Returns the unit length vector for the given angle (in degrees).
    static CCPhysicsVector *createForRotation(float degrees);

    const cpVect getVector(void);
    void getValue(float *x, float *y);
    const CCPoint getValue(void);
    
    // Check if two vectors are equal
    bool equal(CCPhysicsVector *other);
    bool equal(float x, float y);
    
    // Add an other vectors
    void add(CCPhysicsVector *other);
    void add(float x, float y);
    
    // Subtract an other vectors
    void sub(CCPhysicsVector *other);
    void sub(float x, float y);
    
    // Negate a vector
    void negate(void);
    
    // Scalar multiplication
    void multi(float scale);
    
    // Vector dot product
    float dot(CCPhysicsVector *other);
    float dot(float x, float y);
    
    // 2D vector cross product analog
    float cross(CCPhysicsVector *other);
    float cross(float x, float y);
    
    // Returns a perpendicular vector. (90 degree rotation)
    CCPhysicsVector *perp(void);
    
    // Returns a perpendicular vector. (-90 degree rotation)
    CCPhysicsVector *rperp(void);
    
    // Uses complex multiplication to rotate v1 by v2. Scaling will occur if v1 is not a unit vector.
    void rotate(CCPhysicsVector *other);
    void rotate(float x, float y);
    
    // Returns the length.
    float length(void);
    
    // Returns the squared length. Faster than length() when you only need to compare lengths.
    float lengthsq(void);
    
    // Returns the distance between current vector to other.
    float dist(CCPhysicsVector *other);
    float dist(float x, float y);
    
    // Returns the squared distance between current vector and other. Faster than dist() when you only need to compare distances.
    float distsq(CCPhysicsVector *other);
    float distsq(float x, float y);
    
    // Returns the angular direction v is pointing in (in radians).
    float angle(void);
    
    // Returns the angular direction v is pointing in (in degrees).
    float rotation(void);
    
    // Returns the sum of abs(x) nad abs(y).
    float sum(void);
    
private:
    CCPhysicsVector(float x, float y);
    
    cpVect m_vector;
};

class CCPhysicsVectorArray : public CCObject
{
public:
    static CCPhysicsVectorArray *createFromCCPointArray(CCPointArray *points);
    static CCPhysicsVectorArray *createFromCCPoint(unsigned int numPoints, CCPoint *points);
    
#if CC_LUA_ENGINE_ENABLED > 0
    static CCPhysicsVectorArray *createFromLuaTable(int vertexes);
#endif
    
    ~CCPhysicsVectorArray(void);
    
    unsigned int count(void);
    cpVect *data(void);
    
private:
    CCPhysicsVectorArray(void)
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
    
    // Returns true if this is the first step the two shapes started touching. This can be useful for sound effects for instance. If it’s the first frame for a certain collision, check the energy of the collision in a postStep() callbock and use that to determine the volume of a sound effect to play.
    bool isFirstContact(void);
    
    // The calculated elasticity for this collision pair. Setting the value in a preSolve() callback will override the value calculated by the space.
    float getElasticity(void);
    void setElasticity(float elasticity);

    // The calculated friction for this collision pair. Setting the value in a preSolve() callback will override the value calculated by the space.
    float getFriction(void);
    void setFriction(float friction);
    
    // The calculated surface velocity for this collision pair. Setting the value in a preSolve() callback will override the value calculated by the space.
    const CCPoint getSurfaceVelocities(void);
    void getSurfaceVelocities(float *velocityX, float *velocityY);    
    void setSurfaceVelocities(float velocityX, float velocityY);
    void setSurfaceVelocities(const CCPoint velocity);
    
    // Get the number of contact points.
    int getCount(void);
    
    // Get the normal of the ith contact point.
    const CCPoint getNormal(int index);
    void getNormal(int index, float *x, float *y);
    
    // Get the position of the ith contact point.
    const CCPoint getPoint(int index);
    void getPoint(int index, float *x, float *y);
 	
    // Get the depth of the ith contact point.
    float getDepth(int index);
 	
    // A user definable pointer. The value will persist for the pair of shapes until the "separate" is called.
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
