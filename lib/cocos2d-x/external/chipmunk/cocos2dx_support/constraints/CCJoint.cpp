#include "CCJoint.h"


CCJoint::CCJoint(CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, JointType jointType) :bodyA(bodyA), bodyB(bodyB), jointType(jointType)
{
}


CCJoint::~CCJoint()
{
}


CCPhysicsBody *CCJoint::getBodyA()
{
	return this->bodyA;
}

CCPhysicsBody *CCJoint::getBodyB()
{
	return this->bodyB;
}

JointType CCJoint::getJointType()
{
	return this->jointType;
}
