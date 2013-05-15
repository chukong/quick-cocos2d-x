
#ifndef __CCPHYSICS_BODY_H_
#define __CCPHYSICS_BODY_H_

#include "cocos2d.h"
#include "chipmunk.h"
#include "CCPhysicsWorldDataSupport.h"

using namespace std;
using namespace cocos2d;

class CCPhysicsWorld;
class CCPhysicsShape;

class CCPhysicsBody : public CCObject
{
public:
    static CCPhysicsBody *defaultStaticBody(CCPhysicsWorld *world);
    static CCPhysicsBody *createStaticBody(CCPhysicsWorld *world);
    static CCPhysicsBody *create(CCPhysicsWorld *world, float mass, float moment);
    virtual ~CCPhysicsBody(void);

    cpBody *getBody(void);

    float getMass(void);
    void setMass(float mass);
    
    float getInertia(void);
    void setInertia(float inertia);
    
    CCPoint getVelocity(void);
    void getVelocity(float *velocityX, float *velocityY);
    void setVelocity(const CCPoint &velocity);
    void setVelocity(float velocityX, float velocityY);
    
    float getVelocityLimit(void);
    void setVelocityLimit(float limit);
    
    float getAngleVelocity(void);
    void setAngleVelocity(float velocity);
    
    float getAngleVelocityLimit(void);
    void setAngleVelocityLimit(float limit);
    
    CCPoint getForce(void);
    void getForce(float *forceX, float *forceY);
    void setForce(const CCPoint &force);
    void setForce(float forceX, float forceY);
    
    float getTorque(void);
    void setTorque(float force);
    
    CCPoint getPosition(void);
    void getPosition(float *x, float *y);
    void setPosition(const CCPoint &pos);
    void setPosition(float x, float y);
    
    float getAngle(void);
    void setAngle(float angle);
    
    float getRotation(void);
    void setRotation(float rotation);
    
    void bindNode(CCNode *node);
    void unbind(void);
    void updateNode(void);

    CCPhysicsShape *addSegmentShape(const CCPoint lowerLeft, const CCPoint lowerRight, float thickness);
    CCPhysicsShape *addCircleShape(float radius, float offsetX = 0, float offsetY = 0);
    CCPhysicsShape *addBoxShape(float width, float height);
    CCPhysicsShape *addPolygonShape(CCPointArray *vertexes, float offsetX = 0, float offsetY = 0);
    CCPhysicsShape *addPolygonShape(int numVertexes, CCPoint *vertexes, float offsetX = 0, float offsetY = 0);
    CCPhysicsShape *addPolygonShape(int numVertexes, cpVect *vertexes, float offsetX = 0, float offsetY = 0);
#if CC_LUA_ENGINE_ENABLED > 0
    CCPhysicsShape *addPolygonShape(int vertexes, float offsetX = 0, float offsetY = 0);
#endif

    void removeShapeAtIndex(int index);
    void removeShape(CCPhysicsShape *shapeObject);
    void removeAllShape(void);

private:
    CCPhysicsBody(CCPhysicsWorld *world);
    bool initWithDefaultStaticBody(void);
    bool initWithStaticBody(void);
    bool initWithBody(float mass, float moment);

    CCPhysicsWorld *m_world;
    cpSpace        *m_space;
    cpBody         *m_body;
    CCArray        *m_shapes;
    CCNode         *m_node;

    CCPhysicsShape *addShape(cpShape *shape);
};

#endif // __CCPHYSICS_BODY_H_
