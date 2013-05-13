
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

class cpVectArray : public CCObject
{
public:
    static cpVectArray *createFromCCPointArray(CCPointArray *points);
    ~cpVectArray(void);
    
    int count(void) {
        return m_count;
    }
    
    cpVect *data(void) {
        return m_verts;
    }
    
private:
    cpVectArray(void)
    : m_verts(NULL)
    , m_count(0)
    {
    }
    bool initWithCCPointArray(CCPointArray *points);
    
    cpVect *m_verts;
    int m_count;
};

class PhysicsWorld : public CCNode
{
public:
    static PhysicsWorld *create(float gravityX, float gravityY);
    static PhysicsWorld *create(void);
    virtual ~PhysicsWorld(void);
    
    cpSpace *getSpace(void);
    PhysicsDebugNode *createDebugNode(void);
    
    const CCPoint getGravity(void);
    void getGravity(float *gravityX, float *gravityY);
    void setGravity(float gravityX, float gravityY);
    
    // create shapes
    PhysicsBody *addCircleShape(float mass, float radius, const CCPoint offset = CCPointZero);
    PhysicsBody *addCircleShape(float mass, float radius, float offsetX = 0, float offsetY = 0);
    PhysicsBody *addBoxShape(float mass, float width, float height);
    PhysicsBody *addPolygonShape(float mass, CCPointArray *vertexes, const CCPoint offset = CCPointZero);
    PhysicsBody *addPolygonShape(float mass, CCPointArray *vertexes, float offsetX = 0, float offsetY = 0);
#if CC_LUA_ENGINE_ENABLED > 0
    PhysicsBody *addPolygonShape(float mass, int vertexes, float offsetX = 0, float offsetY = 0);
#endif
    
    // bind node to body
    void bindNodeToBody(CCNode *node, PhysicsBody *body);
    void unbindNode(CCNode *node);
    void unbindAllNodes(void);
    PhysicsBody *getBodyByNode(CCNode *node);
    
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
