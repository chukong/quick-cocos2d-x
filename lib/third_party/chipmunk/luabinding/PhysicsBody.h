
#ifndef __PHYSICS_BODY_H_
#define __PHYSICS_BODY_H_

#include <vector>
#include "cocos2d.h"
#include "chipmunk.h"

using namespace std;
using namespace cocos2d;

class PhysicsWorld;

typedef vector<cpShape*> PhysicsShapeVector;
typedef PhysicsShapeVector::iterator PhysicsShapeVectorIterator;

class PhysicsBody : public CCObject
{
public:
    static PhysicsBody *defaultStaticBody(PhysicsWorld *world);
    static PhysicsBody *createStaticBody(PhysicsWorld *world);
    static PhysicsBody *create(PhysicsWorld *world, float mass, float inertia);
    virtual ~PhysicsBody(void);
    
    cpBody *getBody(void) {
        return m_body;
    }
    
    void setMass(float mass);
    void setInertia(float inertia);
    
    int addCircleShape(float radius, float offsetX, float offsetY);
    
    void removeShapeAtIndex(int index);
    void removeAllShape(void);
    
private:
    PhysicsBody(PhysicsWorld *world);
    bool initWithDefaultStaticBody(void);
    bool initWithStaticBody(void);
    bool initWithBody(float mass, float inertia);
    
    PhysicsWorld *m_world;
    cpSpace *m_space;
    cpBody *m_body;
    PhysicsShapeVector m_shapes;
};

#endif // __PHYSICS_BODY_H_
