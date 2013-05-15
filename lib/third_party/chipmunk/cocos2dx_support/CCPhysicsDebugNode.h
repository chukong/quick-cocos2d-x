
#ifndef __PHYSICS_DEBUG_NODE_H__
#define __PHYSICS_DEBUG_NODE_H__

#include "cocos2d.h"
#include "chipmunk.h"

using namespace cocos2d;

class CCPhysicsDebugNode : public CCDrawNode
{
protected:
    cpSpace *m_pSpacePtr;

public:
    /** Create a debug node for a regular Chipmunk space. */
    static CCPhysicsDebugNode * create(cpSpace *space);

    virtual ~CCPhysicsDebugNode();

    virtual void draw();

    cpSpace* getSpace() const;
    void setSpace(cpSpace *space);

    CCPhysicsDebugNode();
};

#endif // __PHYSICS_DEBUG_NODE_H__
