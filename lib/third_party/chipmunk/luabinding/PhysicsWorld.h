
#ifndef __PHYSICS_WORLD_H_
#define __PHYSICS_WORLD_H_

#include <map>
#include "cocos2d.h"
#include "chipmunk.h"

using namespace std;
using namespace cocos2d;

#define PHYSICS_WORLD_DRAW_MODE_NORMAL  0
#define PHYSICS_WORLD_DRAW_MODE_HYBRID  1
#define PHYSICS_WORLD_DRAW_MODE_DEBUG   2

class PhysicsBody;

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
    
    void getGravity(float *gravityX, float *gravityY);
    void setGravity(float gravityX, float gravityY);
    
    int getDrawMode(void);
    void setDrawMode(int drawMode);

    PhysicsBody *bindNodeToDefaultStaticBody(CCNode *node);
    PhysicsBody *bindNodeToNewStaticBody(CCNode *node);
    PhysicsBody *bindNodeToNewBody(CCNode *node, float mass, float inertia = 0);
    void unbindNode(CCNode *node);
    void unbindAllNodes(void);
    
    void start(bool allowSleep);
    void stop(void);
    
    virtual void update(float dt);
    
private:
    PhysicsWorld(void)
    : m_space(NULL)
    , m_gravity({0, 0})
    , m_drawMode(PHYSICS_WORLD_DRAW_MODE_NORMAL)
    , m_defaultStaticBody(NULL)
    {
    }
    bool init(void);
    
    cpSpace            *m_space;
    cpVect              m_gravity;
    int                 m_drawMode;
    PhysicsWorldBodyMap m_bodies;
    PhysicsBody        *m_defaultStaticBody;
    
    static int          m_nodeId;
};

#endif // __PHYSICS_WORLD_H_
