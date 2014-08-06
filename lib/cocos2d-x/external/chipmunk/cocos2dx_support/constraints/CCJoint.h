#ifndef __CC_JOINT_H_
#define __CC_JOINT_H_
#include "cocos2d.h"
#include "chipmunk.h"
#include "CCPhysicsSupport.h"
#include "CCPhysicsBody.h"
#include "script_support/CCScriptSupport.h"

using namespace cocos2d;

class CCJoint : public CCNode
{
public:
	CCJoint(CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, JointType jointType);
	~CCJoint();
	
	CCPhysicsBody *getBodyA();
	CCPhysicsBody *getBodyB();
	
	virtual JointType getJointType() = 0;
	virtual cpConstraint *getConstraint() = 0;

protected:
	CCPhysicsBody *bodyA;
	CCPhysicsBody *bodyB;
	
	JointType jointType;
};

enum JointType
{
	UNKNOWN = 0,
	PIN_JOINT = 1,
	SLIDE_JOINT = 2,
};

#endif

