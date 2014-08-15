/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/
#include "CCJoint.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"

CCSlideJoint::CCSlideJoint(CCPhysicsWorld *world,
	CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect archA, cpVect archB,
	cpFloat min, cpFloat max) : CCJoint(world, bodyA, bodyB, SLIDE_JOINT)
{
	this->m_constraint = cpSpaceAddConstraint(world->getSpace(),
		cpSlideJointNew(bodyA->getBody(), bodyB->getBody(), archA, archB, min, max));
}

CCSlideJoint::~CCSlideJoint()
{
}

CCPhysicsVector *CCSlideJoint::getAnchrA()
{
	return CCPhysicsVector::create(cpSlideJointGetAnchr1(this->m_constraint));
}

void CCSlideJoint::setAnchrA(CCPhysicsVector *anchrA)
{
	cpSlideJointSetAnchr1(this->m_constraint, anchrA->getVector());
}

CCPhysicsVector *CCSlideJoint::getAnchrB()
{
	return CCPhysicsVector::create(cpSlideJointGetAnchr2(this->m_constraint));
}

void CCSlideJoint::setAnchrB(CCPhysicsVector *anchrB)
{
	cpSlideJointSetAnchr2(this->m_constraint, anchrB->getVector());
}

cpFloat CCSlideJoint::getMin()
{
	return cpSlideJointGetMin(this->m_constraint);
}

void CCSlideJoint::setMin(cpFloat min)
{
	cpSlideJointSetMin(this->m_constraint, min);
}

cpFloat CCSlideJoint::getMax()
{
	return cpSlideJointGetMax(this->m_constraint);
}

void CCSlideJoint::setMax(cpFloat max)
{
	cpSlideJointSetMax(this->m_constraint, max);
}