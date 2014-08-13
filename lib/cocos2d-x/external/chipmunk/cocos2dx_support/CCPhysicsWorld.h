
#ifndef __CCPHYSICS_WORLD_H_
#define __CCPHYSICS_WORLD_H_

#include <map>
#include "cocos2d.h"
#include "chipmunk.h"
#include "CCPhysicsSupport.h"
#include "script_support/CCScriptSupport.h"

using namespace std;
using namespace cocos2d;

class CCPhysicsBody;
class CCPhysicsDebugNode;
class CCPhysicsShape;

typedef map<cpBody*, CCPhysicsBody*> CCPhysicsBodyMap;
typedef CCPhysicsBodyMap::iterator CCPhysicsBodyMapIterator;

class CCPhysicsWorld : public CCNode
{
public:
    static CCPhysicsWorld *create(float gravityX, float gravityY);
    static CCPhysicsWorld *create(void);
    virtual ~CCPhysicsWorld(void);

    cpSpace *getSpace(void);
    CCPhysicsDebugNode *createDebugNode(void);

    // world properties
    const CCPoint getGravity(void);
    void getGravity(float *gravityX, float *gravityY);
    void setGravity(float gravityX, float gravityY);

    float getIdleSpeedThreshold(void);
    void setIdleSpeedThreshold(float threshold);

    float getDamping(void);
    void setDamping(float damping);

    bool isLocked(void);

    float getStepInterval(void);
    void setStepInterval(float interval);

    // body management
    CCPhysicsBody *createCircleBody(float mass, float radius, float offsetX = 0, float offsetY = 0);
    CCPhysicsBody *createBoxBody(float mass, float width, float height);
    CCPhysicsBody *createPolygonBody(float mass, CCPointArray *vertexes, float offsetX = 0, float offsetY = 0);
    CCPhysicsBody *createPolygonBody(float mass, CCPhysicsVectorArray *vertexes, float offsetX = 0, float offsetY = 0);
    CCPhysicsBody *createPolygonBody(float mass, int numVertexes, cpVect *vertexes, float offsetX = 0, float offsetY = 0);
#if CC_LUA_ENGINE_ENABLED > 0
    CCPhysicsBody *createPolygonBody(float mass, int vertexes, float offsetX = 0, float offsetY = 0);
#endif

    CCArray *getAllBodies(void);

    void addBody(CCPhysicsBody *body);
    CCPhysicsBody *getBodyByTag(int tag);
    void removeBodyByTag(int tag, bool unbindNow = true);
    void removeBody(CCPhysicsBody *body, bool unbindNow = true);
    void removeAllBodies(bool unbindNow = true);

    CCPhysicsBody *getBodyByCpBody(cpBody *cpBody);

    // operation
    void start(void);
    void stop(void);

    // events
#if CC_LUA_ENGINE_ENABLED > 0
    void addCollisionScriptListener(int handler, int collisionTypeA, int collisionTypeB);
    void removeCollisionScriptListener(int collisionTypeA, int collisionTypeB);
#endif
    void removeAllCollisionListeners(void);

    // delegate
    virtual void step(float dt);
    virtual void update(float dt);
    virtual void onExit(void);

private:
    CCPhysicsWorld(void)
    : m_space(NULL)
    , m_stepInterval(0)
    , m_defaultStaticBody(NULL)
    , m_bodiesArray(NULL)
    , m_removedBodies(NULL)
    , m_removedShapes(NULL)
    , m_addedBodies(NULL)
    , m_addedShapes(NULL)
    , m_listeners(NULL)
    {
    }
    bool init(void);

    cpSpace *m_space;
    float m_stepInterval;
    CCPhysicsBody *m_defaultStaticBody;
    CCPhysicsBodyMap m_bodies;
    CCArray *m_bodiesArray;
    CCArray *m_removedBodies;
    CCArray *m_removedShapes;
    CCArray *m_addedBodies;
    CCArray *m_addedShapes;
    CCArray *m_listeners;

    static const char *POST_STEP_CALLBACK_KEY;

    // helper
    friend class CCPhysicsBody;
    void addShape(CCPhysicsShape *shape);
    void removeShape(CCPhysicsShape *shape);

    // callbacks
    static int collisionBeginCallback(cpArbiter *arbiter, struct cpSpace *space, void *data);
    static int collisionPreSolveCallback(cpArbiter *arbiter, struct cpSpace *space, void *data);
    static void collisionPostSolveCallback(cpArbiter *arbiter, struct cpSpace *space, void *data);
    static void collisionSeparateCallback(cpArbiter *arbiter, struct cpSpace *space, void *data);
};

#endif // __CCPHYSICS_WORLD_H_
