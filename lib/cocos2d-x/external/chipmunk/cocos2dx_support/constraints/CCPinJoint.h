#ifndef __CC_PIN_JOINT_H_
#define __CC_PIN_JOINT_H_

#include "CCJoint.h"
using namespace std;
using namespace cocos2d;

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

