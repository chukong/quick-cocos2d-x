#ifndef __CC_JOINT_H_
#define __CC_JOINT_H_
#include "cocos2d.h"
#include "chipmunk.h"
#include "CCPhysicsSupport.h"
#include "CCPhysicsBody.h"
#include "script_support/CCScriptSupport.h"

using namespace cocos2d;

enum JointType
{
	UNKNOWN = 0,
	PIN_JOINT = 1,
	SLIDE_JOINT = 2
};

class CCJoint : public CCNode
{
public:
	CCJoint(CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, JointType jointType);
	virtual ~CCJoint();
	
	CCPhysicsBody *getBodyA();
	CCPhysicsBody *getBodyB();
	
	virtual JointType getJointType() = 0;
	virtual cpConstraint *getConstraint() = 0;

protected:
	CCPhysicsBody *bodyA;
	CCPhysicsBody *bodyB;
	
	JointType jointType;
};

class CCPinJoint : public CCJoint
{
public:
	CCPinJoint(CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect vectOfBodyA, cpVect vectOfBodyB);
	CCPinJoint(CCPhysicsBody *bodyA, CCPhysicsBody *bodyB);
	~CCPinJoint();

	cpFloat getDist();
	void setDist(cpFloat dist);

	JointType getJointType();
	cpConstraint *getConstraint();
private:
	cpPinJoint *m_pinJoint;
};
#endif

