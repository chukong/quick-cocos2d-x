/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/
#include "CCJoint.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"

CCPivotJoint::CCPivotJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB,
	cpVect anchrA, cpVect anchrB) : CCJoint(world, bodyA, bodyB, PIVOT_JOINT)
{
	this->m_constraint = cpSpaceAddConstraint(world->getSpace(),
		cpPivotJointNew2(bodyA->getBody(), bodyB->getBody(), anchrA, anchrB));
}

CCPivotJoint::CCPivotJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, cpVect pivot) : CCJoint(world, bodyA, bodyB, PIVOT_JOINT)
{
	this->m_constraint = cpSpaceAddConstraint(world->getSpace(),
		cpPivotJointNew(bodyA->getBody(), bodyB->getBody(), pivot));
}

CCPivotJoint::~CCPivotJoint()
{
}

CCPhysicsVector *CCPivotJoint::getAnchrA()
{
	return CCPhysicsVector::create(cpPivotJointGetAnchr1(this->m_constraint));
}

void CCPivotJoint::setAnchrA(CCPhysicsVector *anchrA)
{
	cpPivotJointSetAnchr1(this->m_constraint, anchrA->getVector());
}

CCPhysicsVector *CCPivotJoint::getAnchrB()
{
	return CCPhysicsVector::create(cpPivotJointGetAnchr2(this->m_constraint));
}

void CCPivotJoint::setAnchrB(CCPhysicsVector *anchrB)
{
	cpPivotJointSetAnchr2(this->m_constraint, anchrB->getVector());
}