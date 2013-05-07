
#ifndef __PHYSICS_DEBUG_NODE_H__
#define __PHYSICS_DEBUG_NODE_H__

#include "cocos2d.h"
#include "chipmunk.h"

using namespace cocos2d;

class PhysicsDebugNode : public CCDrawNode
{
protected:
    cpSpace *m_pSpacePtr;
    
public:
    /** Create a debug node for a regular Chipmunk space. */
    static PhysicsDebugNode* create(cpSpace *space);
    
    virtual ~PhysicsDebugNode();
    
    virtual void draw();
    
    cpSpace* getSpace() const;
    void setSpace(cpSpace *space);
    
    PhysicsDebugNode();
};

#endif // __PHYSICS_DEBUG_NODE_H__
