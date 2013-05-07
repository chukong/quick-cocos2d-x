
#ifndef __PHYSICS_WORLD_H_
#define __PHYSICS_WORLD_H_

#include <map>
#include "cocos2d.h"
#include "chipmunk.h"

using namespace std;
using namespace cocos2d;

class PhysicsBody;
class PhysicsDebugNode;

typedef map<CCNode*, PhysicsBody*> PhysicsWorldBodyMap;
typedef PhysicsWorldBodyMap::iterator PhysicsWorldBodyMapIterator;

class PhysicsWorld : public CCNode
{
public:
    static PhysicsWorld *create(void);
    virtual ~PhysicsWorld(void);
    
    cpSpace *getSpace(void) {
        return m_space;
    }
    
    PhysicsDebugNode *createDebugNode(void);
    
    void getGravity(float *gravityX, float *gravityY);
    void setGravity(float gravityX, float gravityY);
    
    float calcMomentForCircle(float mass, float innerRadius, float outerRadius, float offsetX, float offsetY);

    PhysicsBody *bindNodeToDefaultStaticBody(CCNode *node);
    PhysicsBody *bindNodeToNewStaticBody(CCNode *node);
    PhysicsBody *bindNodeToNewBody(CCNode *node, float mass, float moment);
    void unbindNode(CCNode *node);
    void unbindAllNodes(void);
    
    void start(void);
    void stop(void);
    
    virtual void update(float dt);
    virtual void onExit(void);
    
private:
    PhysicsWorld(void)
    : m_space(NULL)
    , m_defaultStaticBody(NULL)
    {
    }
    bool init(void);
    
    cpSpace            *m_space;
    PhysicsWorldBodyMap m_bodies;
    PhysicsBody        *m_defaultStaticBody;
};

#endif // __PHYSICS_WORLD_H_
