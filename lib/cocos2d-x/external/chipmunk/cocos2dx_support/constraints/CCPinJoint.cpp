#include "CCJoint.h"

CCPinJoint::CCPinJoint(CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect vectOfBodyA, cpVect vectOfBodyB) : CCJoint(bodyA, bodyB, PIN_JOINT)
{
	this->m_pinJoint = (cpPinJoint *)cpPinJointNew(bodyA->getBody(), bodyB->getBody(), vectOfBodyA, vectOfBodyB);
}

CCPinJoint::CCPinJoint(CCPhysicsBody *bodyA, CCPhysicsBody *bodyB) : CCJoint(bodyA, bodyB, PIN_JOINT)
{
	float bodyAPosX = bodyA->getPositionX();
	float bodyAPosY = bodyA->getPositionY();

	float bodyBPosX = bodyB->getPositionX();
	float bodyBPosY = bodyB->getPositionY();

	this->m_pinJoint = (cpPinJoint *)cpPinJointNew(bodyA->getBody(), bodyB->getBody(), cpv(bodyAPosX, bodyAPosY), cpv(bodyBPosX, bodyBPosY));
}


CCPinJoint::~CCPinJoint()
{
	this->bodyA->removeJoint(this);
	this->bodyB->removeJoint(this);
	cpConstraintFree((cpConstraint*)this->m_pinJoint);
}

cpConstraint *CCPinJoint::getConstraint()
{
	return (cpConstraint*)this->m_pinJoint;
}

JointType CCPinJoint::getJointType()
{
	return this->jointType;
}

cpFloat CCPinJoint::getDist()
{
	return cpPinJointGetDist((cpConstraint*)this->m_pinJoint);
}

void CCPinJoint::setDist(cpFloat dist)
{
	cpPinJointSetDist((cpConstraint*)this->m_pinJoint, dist);
}