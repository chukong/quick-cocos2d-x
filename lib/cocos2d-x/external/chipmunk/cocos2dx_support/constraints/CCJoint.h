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
	SLIDE_JOINT = 2,
	DAMPED_SPRING = 5,
};

class CCJoint: public CCObject
{
public:

	CCJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, JointType jointType);
	virtual ~CCJoint();
	
	CCPhysicsBody *getBodyA();
	CCPhysicsBody *getBodyB();

	virtual cpConstraint *getConstraint();
	virtual JointType getJointType();
	virtual void breakJoint();

	cpFloat getMaxForce();
	void setMaxForce(cpFloat maxForce);

	cpFloat getErrorBias();
	void setErrorBias(cpFloat errorBias);

	cpFloat getMaxBias();
	void setMaxBias(cpFloat maxBias);

	cpFloat getImpulse();
protected:
	CCPhysicsWorld *world;
	CCPhysicsBody *bodyA;
	CCPhysicsBody *bodyB;
	
	cpConstraint *m_constraint;
	JointType jointType;
};

class CCPinJoint : public CCJoint
{
public:
	CCPinJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect vectOfBodyA, cpVect vectOfBodyB);
	~CCPinJoint();

	cpFloat getDist();
	void setDist(cpFloat dist);
};

class CCDampedSpringJoint : public CCJoint
{
public:
	CCDampedSpringJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB,
		cpVect vectOfBodyA, cpVect vectOfBodyB,
		cpFloat restLength, cpFloat stiffness, cpFloat damping);

	~CCDampedSpringJoint();
};
#endif

