/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/
#include "CCJoint.h"

CCDampedSpringJoint::CCDampedSpringJoint(CCPhysicsWorld* world, 
	CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, 
	cpVect vectOfBodyA, cpVect vectOfBodyB,
	cpFloat restLength, cpFloat stiffness, cpFloat damping) : CCJoint(world, bodyA, bodyB, DAMPED_SPRING)
{
	this->m_constraint = cpSpaceAddConstraint(world->getSpace(),
		cpDampedSpringNew(bodyA->getBody(), bodyB->getBody(), 
		vectOfBodyA, vectOfBodyB,
		restLength, stiffness, damping));
}

CCDampedSpringJoint::~CCDampedSpringJoint()
{
}