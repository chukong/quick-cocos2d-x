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
#include "script_support/CCScriptSupport.h"

using namespace cocos2d;

class CCPhysicsBody;
class CCPhysicsWorld;


enum JointType
{
	UNKNOWN = 0,
	PIN_JOINT = 1,
	SLIDE_JOINT = 2,
	PIVOT_JOINT = 3,
	GROOVE_JOINT = 4,
	DAMPED_SPRING = 5,
	DAMPED_ROTARY_SPRING = 6,
	ROTARY_LIMIT = 7,
	RATCHET_JOINT = 8,
	GEAR_JOINT = 9,
	SIMPLE_MOTOR = 10
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

	virtual CCPhysicsVector *getAnchrA() = 0;
	virtual void setAnchrA(CCPhysicsVector *anchrA) = 0;
	virtual CCPhysicsVector *getAnchrB() = 0;
	virtual void setAnchrB(CCPhysicsVector *anchrB) = 0;
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
	CCPinJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect anchrA, cpVect anchrB);
	~CCPinJoint();

	cpFloat getDist();
	void setDist(cpFloat dist);

	CCPhysicsVector *getAnchrA();
	void setAnchrA(CCPhysicsVector *anchrA);
	CCPhysicsVector *getAnchrB();
	void setAnchrB(CCPhysicsVector *anchrB);
};

class CCDampedSpringJoint : public CCJoint
{
public:
	CCDampedSpringJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB,
		cpVect anchrA, cpVect anchrB,
		cpFloat restLength, cpFloat stiffness, cpFloat damping);

	~CCDampedSpringJoint();

	CCPhysicsVector *getAnchrA();
	void setAnchrA(CCPhysicsVector *anchrA);
	CCPhysicsVector *getAnchrB();
	void setAnchrB(CCPhysicsVector *anchrB);
};

class CCSlideJoint : public CCJoint
{
public:
	CCSlideJoint(CCPhysicsWorld *world,
		CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect archA, cpVect archB,
		cpFloat min, cpFloat max);

	~CCSlideJoint();

	CCPhysicsVector *getAnchrA();
	void setAnchrA(CCPhysicsVector *anchrA);
	CCPhysicsVector *getAnchrB();
	void setAnchrB(CCPhysicsVector *anchrB);

	cpFloat getMin();
	void setMin(cpFloat min);

	cpFloat getMax();
	void setMax(cpFloat max);
};

class CCPivotJoint : public CCJoint
{
public:
	CCPivotJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect anchrA, cpVect anchrB);
	CCPivotJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect pivot);
	~CCPivotJoint();

	CCPhysicsVector *getAnchrA();
	void setAnchrA(CCPhysicsVector *anchrA);
	CCPhysicsVector *getAnchrB();
	void setAnchrB(CCPhysicsVector *anchrB);
};

class CCGrooveJoint : public CCJoint
{
public:
	CCGrooveJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect grooveA, cpVect grooveB, cpVect archrB);
	~CCGrooveJoint();

	CCPhysicsVector *getGrooveA();
	void setGrooveA(CCPhysicsVector *grooveA);

	CCPhysicsVector *getGrooveB();
	void setGrooveB(CCPhysicsVector *grooveB);

	CCPhysicsVector *getAnchrA();
	void setAnchrA(CCPhysicsVector *anchrA);

	CCPhysicsVector *getAnchrB();
	void setAnchrB(CCPhysicsVector *anchrB);
};
#endif

