
#ifndef __CCPHYSICS_WORLD_H_
#define __CCPHYSICS_WORLD_H_

#include <map>
#include "cocos2d.h"
#include "chipmunk.h"
#include "CCPhysicsWorldDataSupport.h"

using namespace std;
using namespace cocos2d;

class CCPhysicsBody;
class CCPhysicsDebugNode;

class CCPhysicsWorld : public CCNode
{
public:
    static CCPhysicsWorld *create(float gravityX, float gravityY);
    static CCPhysicsWorld *create(void);
    virtual ~CCPhysicsWorld(void);
    
    cpSpace *getSpace(void);
    CCPhysicsDebugNode *createDebugNode(void);
    
    const CCPoint getGravity(void);
    void getGravity(float *gravityX, float *gravityY);
    void setGravity(float gravityX, float gravityY);
    
    CCPhysicsBody *addCircleShape(float mass, float radius, float offsetX = 0, float offsetY = 0);
    CCPhysicsBody *addBoxShape(float mass, float width, float height);
    CCPhysicsBody *addPolygonShape(float mass, CCPointArray *vertexes, float offsetX = 0, float offsetY = 0);
    CCPhysicsBody *addPolygonShape(float mass, cpVectArray *vertexes, float offsetX = 0, float offsetY = 0);
    CCPhysicsBody *addPolygonShape(float mass, int numVertexes, cpVect *vertexes, float offsetX = 0, float offsetY = 0);
#if CC_LUA_ENGINE_ENABLED > 0
    CCPhysicsBody *addPolygonShape(float mass, int vertexes, float offsetX = 0, float offsetY = 0);
#endif

    void addBody(CCPhysicsBody *body);
    
    CCPhysicsBody *getBodyByTag(int tag);
    void removeBodyByTag(int tag);
    void removeBody(CCPhysicsBody *body);
    void removeAllBodies(void);
    
    void start(void);
    void stop(void);
    
    virtual void update(float dt);
    virtual void onExit(void);
    
private:
    CCPhysicsWorld(void)
    : m_space(NULL)
    , m_defaultStaticBody(NULL)
    , m_bodies(NULL)
    {
    }
    bool init(void);
    
    cpSpace        *m_space;
    CCPhysicsBody  *m_defaultStaticBody;
    CCArray        *m_bodies;
};

#endif // __CCPHYSICS_WORLD_H_
