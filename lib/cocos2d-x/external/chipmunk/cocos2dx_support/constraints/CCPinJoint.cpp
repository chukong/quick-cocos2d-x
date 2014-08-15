/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/
#include "CCJoint.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"

CCPinJoint::CCPinJoint(CCPhysicsWorld* world, 
	CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect anchrA, cpVect anchrB) : CCJoint(world, bodyA, bodyB, PIN_JOINT)
{
	this->m_constraint = cpSpaceAddConstraint(world->getSpace(),
		cpPinJointNew(bodyA->getBody(), bodyB->getBody(), anchrA, anchrB));
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

CCPhysicsVector *CCPinJoint::getAnchrA()
{
	return CCPhysicsVector::create(cpPinJointGetAnchr1(this->m_constraint));
}

void CCPinJoint::setAnchrA(CCPhysicsVector *anchrA)
{
	cpPinJointSetAnchr1(this->m_constraint, anchrA->getVector());
}

CCPhysicsVector *CCPinJoint::getAnchrB()
{
	return CCPhysicsVector::create(cpPinJointGetAnchr2(this->m_constraint));
}

void CCPinJoint::setAnchrB(CCPhysicsVector *anchrB)
{
	cpPinJointSetAnchr2(this->m_constraint, anchrB->getVector());
}