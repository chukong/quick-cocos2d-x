/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/

#include "CCJoint.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"

CCGrooveJoint::CCGrooveJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, 
	cpVect grooveA, cpVect grooveB, cpVect archrB) : CCJoint(world, bodyA, bodyB, GROOVE_JOINT)
{
	this->m_constraint = cpSpaceAddConstraint(world->getSpace(), cpGrooveJointNew(bodyA->getBody(), bodyB->getBody(), grooveA, grooveB, archrB));
}

CCGrooveJoint::~CCGrooveJoint()
{

}

CCPhysicsVector *CCGrooveJoint::getGrooveA()
{
	return CCPhysicsVector::create(cpGrooveJointGetGrooveA(this->m_constraint));
}

void CCGrooveJoint::setGrooveA(CCPhysicsVector *grooveA)
{
	cpGrooveJointSetGrooveA(this->m_constraint, grooveA->getVector());
}

CCPhysicsVector *CCGrooveJoint::getGrooveB()
{
	return CCPhysicsVector::create(cpGrooveJointGetGrooveB(this->m_constraint));
}

void CCGrooveJoint::setGrooveB(CCPhysicsVector *grooveB)
{
	cpGrooveJointSetGrooveB(this->m_constraint, grooveB->getVector());
}

CCPhysicsVector *CCGrooveJoint::getAnchrA()
{
	return CCPhysicsVector::create(0, 0);
}

void CCGrooveJoint::setAnchrA(CCPhysicsVector *anchrA)
{
	// nothing to do
}

CCPhysicsVector *CCGrooveJoint::getAnchrB()
{
	return CCPhysicsVector::create(cpGrooveJointGetAnchr2(this->m_constraint));
}

void CCGrooveJoint::setAnchrB(CCPhysicsVector *anchrB)
{
	cpGrooveJointSetAnchr2(this->m_constraint, anchrB->getVector());
}