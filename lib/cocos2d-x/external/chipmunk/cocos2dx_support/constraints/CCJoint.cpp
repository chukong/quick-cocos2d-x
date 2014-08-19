/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/

#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"

#include "CCJoint.h"


CCJoint::CCJoint(CCPhysicsWorld* world, CCPhysicsBody *bodyA, CCPhysicsBody *bodyB, JointType jointType) :world(world), bodyA(bodyA), bodyB(bodyB), jointType(jointType)
{
	char errMsg[80];
	sprintf(errMsg, "body's joints count reach the MAX_JOINT:%d", CCPhysicsBody::MAX_JOINT);
	CCAssert(bodyA->m_joints->count() < CCPhysicsBody::MAX_JOINT, errMsg);
	CCAssert(bodyB->m_joints->count() < CCPhysicsBody::MAX_JOINT, errMsg);
}


CCJoint::~CCJoint()
{
	cpSpaceRemoveConstraint(this->world->getSpace(), this->m_constraint);
	cpConstraintFree(this->m_constraint);
}


CCPhysicsBody *CCJoint::getBodyA()
{
	return this->bodyA;
}

CCPhysicsBody *CCJoint::getBodyB()
{
	return this->bodyB;
}

void CCJoint::breakJoint()
{
	this->bodyA->removeJoint(this);
	this->bodyB->removeJoint(this);
	this->bodyA = NULL;
	this->bodyB = NULL;
	this->release();
}

JointType CCJoint::getJointType()
{
	return this->jointType;
}

cpConstraint *CCJoint::getConstraint()
{
	return this->m_constraint;
}

cpFloat CCJoint::getMaxForce()
{
	return cpConstraintGetMaxForce(this->m_constraint);
}

void CCJoint::setMaxForce(cpFloat maxForce)
{
	cpConstraintSetMaxForce(this->m_constraint, maxForce);
}

cpFloat CCJoint::getErrorBias()
{
	return cpConstraintGetErrorBias(this->m_constraint);
}

void CCJoint::setErrorBias(cpFloat errorBias)
{
	cpConstraintSetErrorBias(this->m_constraint, errorBias);
}

cpFloat CCJoint::getMaxBias()
{
	return cpConstraintGetMaxBias(this->m_constraint);
}

void CCJoint::setMaxBias(cpFloat maxBias)
{
	cpConstraintSetMaxBias(this->m_constraint, maxBias);
}

cpFloat CCJoint::getImpulse()
{
	return cpConstraintGetImpulse(this->m_constraint);
}
