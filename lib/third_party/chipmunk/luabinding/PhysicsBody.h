
#ifndef __PHYSICS_BODY_H_
#define __PHYSICS_BODY_H_

#include "cocos2d.h"
#include "chipmunk.h"

using namespace std;
using namespace cocos2d;

class PhysicsWorld;
class PhysicsShape;

class PhysicsBody : public CCObject
{
public:
    static PhysicsBody *defaultStaticBody(PhysicsWorld *world);
    static PhysicsBody *createStaticBody(PhysicsWorld *world);
    static PhysicsBody *create(PhysicsWorld *world, float mass, float moment);
    virtual ~PhysicsBody(void);
    
    cpBody *getBody(void) {
        return m_body;
    }
    
    void setMass(float mass);
    void setInertia(float inertia);
    void setPosition(float x, float y);
    
    PhysicsShape *addSegmentShape(float lowerLeftX, float lowerLeftY, float lowerRightX, float lowerRightY, float thickness);
    PhysicsShape *addCircleShape(float radius, float offsetX = 0, float offsetY = 0);
    PhysicsShape *addBoxShape(float width, float height);
    PhysicsShape *addPolygonShape(CCPointArray *vertexs, float offsetX = 0, float offsetY = 0);
    PhysicsShape *addPolygonShape(int numVertexs, CCPoint *vertexs, float offsetX = 0, float offsetY = 0);
    PhysicsShape *addPolygonShape(int numVertexs, cpVect *vertexs, float offsetX = 0, float offsetY = 0);
    
    void removeShapeAtIndex(int index);
    void removeShape(PhysicsShape *shapeObject);
    void removeAllShape(void);
    
private:
    PhysicsBody(PhysicsWorld *world);
    bool initWithDefaultStaticBody(void);
    bool initWithStaticBody(void);
    bool initWithBody(float mass, float moment);
    
    PhysicsWorld *m_world;
    cpSpace *m_space;
    cpBody *m_body;
    CCArray *m_shapes;
    
    PhysicsShape *addShape(cpShape *shape);
};

#endif // __PHYSICS_BODY_H_
