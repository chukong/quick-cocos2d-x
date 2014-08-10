/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/
#ifndef __CC_JOINT_H_
#define __CC_JOINT_H_
#include "cocos2d.h"
#include "chipmunk.h"
#include "CCPhysicsSupport.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"
#include "script_support/CCScriptSupport.h"

using namespace cocos2d;

enum JointType
{
	UNKNOWN = 0,
	PIN_JOINT = 1,
	SLIDE_JOINT = 2
};

class CCJoint: public CCObject
{
public:

	CCJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, JointType jointType);
	virtual ~CCJoint();
	
	CCPhysicsBody *getBodyA();
	CCPhysicsBody *getBodyB();
	
	virtual JointType getJointType() = 0;
	virtual cpConstraint *getConstraint() = 0;
	virtual void breakJoint();

protected:
	CCPhysicsWorld *world;
	CCPhysicsBody *bodyA;
	CCPhysicsBody *bodyB;
	
	JointType jointType;
};

class CCPinJoint : public CCJoint
{
public:
	CCPinJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect vectOfBodyA, cpVect vectOfBodyB);
	CCPinJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB);
	~CCPinJoint();

	cpFloat getDist();
	void setDist(cpFloat dist);

	JointType getJointType();
	cpConstraint *getConstraint();
	void breakJoint();
private:
	cpPinJoint *m_pinJoint;
};
#endif

