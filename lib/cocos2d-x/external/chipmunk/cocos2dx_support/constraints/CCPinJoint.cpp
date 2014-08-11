/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/
#include "CCJoint.h"

CCPinJoint::CCPinJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect vectOfBodyA, cpVect vectOfBodyB) : CCJoint(world, bodyA, bodyB, PIN_JOINT)
{
	this->m_pinJoint = (cpPinJoint *)cpSpaceAddConstraint(world->getSpace(), 
		cpPinJointNew(bodyA->getBody(), bodyB->getBody(), vectOfBodyA, vectOfBodyB));
}

CCPinJoint::CCPinJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB) : CCJoint(world, bodyA, bodyB, PIN_JOINT)
{
	float bodyAPosX = bodyA->getPositionX();
	float bodyAPosY = bodyA->getPositionY();

	float bodyBPosX = bodyB->getPositionX();
	float bodyBPosY = bodyB->getPositionY();
	this->m_pinJoint = (cpPinJoint *)cpSpaceAddConstraint(world->getSpace(), 
		cpPinJointNew(bodyA->getBody(), bodyB->getBody(), cpv(bodyAPosX, bodyAPosY), cpv(bodyBPosX, bodyBPosY)));
}


CCPinJoint::~CCPinJoint()
{//TODO die here
	cpSpaceRemoveConstraint(this->world->getSpace(), (cpConstraint*)this->m_pinJoint);
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

void CCPinJoint::breakJoint()
{
	CCJoint::breakJoint();
	this->release();
}