/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/
#include "CCJoint.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"

CCDampedSpringJoint::CCDampedSpringJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, 
	cpVect anchrA, cpVect anchrB,
	cpFloat restLength, cpFloat stiffness, cpFloat damping) : CCJoint(world, bodyA, bodyB, DAMPED_SPRING)
{
	this->m_constraint = cpSpaceAddConstraint(world->getSpace(),
		cpDampedSpringNew(bodyA->getBody(), bodyB->getBody(), 
		anchrA, anchrB,
		restLength, stiffness, damping));
}

CCDampedSpringJoint::~CCDampedSpringJoint()
{
}

CCPhysicsVector *CCDampedSpringJoint::getAnchrA()
{
	return CCPhysicsVector::create(cpDampedSpringGetAnchr1(this->m_constraint));
}

void CCDampedSpringJoint::setAnchrA(CCPhysicsVector *anchrA)
{
	cpDampedSpringSetAnchr1(this->m_constraint, anchrA->getVector());
}

CCPhysicsVector *CCDampedSpringJoint::getAnchrB()
{
	return CCPhysicsVector::create(cpDampedSpringGetAnchr2(this->m_constraint));
}

void CCDampedSpringJoint::setAnchrB(CCPhysicsVector *anchrB)
{
	cpDampedSpringSetAnchr2(this->m_constraint, anchrB->getVector());
}