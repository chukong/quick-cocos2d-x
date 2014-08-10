/**
* desc: declare all joint type
* author: dongxurr123@gmail.com/163.com
* create date:2014-08-03
**/
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
}

JointType CCJoint::getJointType()
{
	return this->jointType;
}
