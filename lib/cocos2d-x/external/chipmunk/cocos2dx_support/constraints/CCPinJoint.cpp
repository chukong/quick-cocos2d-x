/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/
#include "CCJoint.h"

CCPinJoint::CCPinJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect vectOfBodyA, cpVect vectOfBodyB) : CCJoint(world, bodyA, bodyB, PIN_JOINT)
{
	this->m_constraint = cpSpaceAddConstraint(world->getSpace(),
		cpPinJointNew(bodyA->getBody(), bodyB->getBody(), vectOfBodyA, vectOfBodyB));
}

CCPinJoint::~CCPinJoint()
{
}

cpFloat CCPinJoint::getDist()
{
	return cpPinJointGetDist(this->m_constraint);
}

void CCPinJoint::setDist(cpFloat dist)
{
	cpPinJointSetDist(this->m_constraint, dist);
}