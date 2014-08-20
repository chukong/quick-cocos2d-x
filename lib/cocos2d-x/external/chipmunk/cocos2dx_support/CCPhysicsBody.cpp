
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"
#include "CCPhysicsShape.h"

CCPhysicsBody *CCPhysicsBody::defaultStaticBody(CCPhysicsWorld *world)
{
    CCPhysicsBody *body = new CCPhysicsBody(world);
    body->initWithDefaultStaticBody();
    body->autorelease();
    return body;
}

CCPhysicsBody *CCPhysicsBody::createStaticBody(CCPhysicsWorld *world)
{
    CCPhysicsBody *body = new CCPhysicsBody(world);
    body->initWithStaticBody();
    body->autorelease();
    return body;
}

CCPhysicsBody *CCPhysicsBody::create(CCPhysicsWorld *world, float mass, float moment)
{
    CCPhysicsBody *body = new CCPhysicsBody(world);
    body->initWithBody(mass, moment);
    body->autorelease();
    return body;
}

CCPhysicsBody::CCPhysicsBody(CCPhysicsWorld *world)
: m_world(world)
, m_body(NULL)
, m_shapes(NULL)
, m_node(NULL)
, m_joints(NULL)
, m_tag(0)
, m_postIsSleeping(false)
{
    m_space = m_world->getSpace();
    m_shapes = CCArray::create();
    m_shapes->retain();
	m_joints = CCArray::create();
	m_joints->retain();
}

CCPhysicsBody::~CCPhysicsBody(void)
{
    removeSelf();
    CC_SAFE_RELEASE(m_shapes);
    CC_SAFE_RELEASE(m_node);
	// wait to fix
	CC_SAFE_RELEASE(m_joints);
//    CCLOG("CCPhysicsBody::~CCPhysicsBody(void)");
}

bool CCPhysicsBody::initWithDefaultStaticBody(void)
{
    m_body = m_space->staticBody;
    return true;
}

bool CCPhysicsBody::initWithStaticBody(void)
{
    m_body = cpBodyNewStatic();
    return true;
}

bool CCPhysicsBody::initWithBody(float mass, float moment)
{
    m_body = cpBodyNew(mass, moment);
    return true;
}

cpBody *CCPhysicsBody::getBody(void)
{
    return m_body;
}

const char *CCPhysicsBody::getName(void)
{
    return m_name.c_str();
}

void CCPhysicsBody::setName(const char *name)
{
    m_name = name ? name : "";
}

bool CCPhysicsBody::isSleeping(void)
{
    return cpBodyIsSleeping(m_body);
}

void CCPhysicsBody::activate(void)
{
    m_postIsSleeping = cpFalse;
    if (!m_world->isLocked())
    {
        cpBodyActivate(m_body);
    }
}

void CCPhysicsBody::sleep(void)
{
    m_postIsSleeping = cpTrue;
    if (!m_world->isLocked())
    {
        cpBodySleep(m_body);
    }
}

int CCPhysicsBody::getTag(void)
{
    return m_tag;
}

void CCPhysicsBody::setTag(int tag)
{
    m_tag = tag;
}

float CCPhysicsBody::getMass(void)
{
    return cpBodyGetMass(m_body);
}

void CCPhysicsBody::setMass(float mass)
{
    cpBodySetMass(m_body, mass);
}

float CCPhysicsBody::getInertia(void)
{
    return cpBodyGetMoment(m_body);
}

void CCPhysicsBody::setInertia(float inertia)
{
    cpBodySetMoment(m_body, inertia);
}

CCPoint CCPhysicsBody::getVelocity(void)
{
    const cpVect v = cpBodyGetVel(m_body);
    return CCPoint(v.x, v.y);
}

void CCPhysicsBody::getVelocity(float *velocityX, float *velocityY)
{
    const cpVect v = cpBodyGetVel(m_body);
    *velocityX = v.x;
    *velocityY = v.y;
}

void CCPhysicsBody::setVelocity(const CCPoint &velocity)
{
    cpBodySetVel(m_body, cpv(velocity.x, velocity.y));
}

void CCPhysicsBody::setVelocity(CCPhysicsVector* velocity)
{
    cpBodySetVel(m_body, velocity->getVector());
}

void CCPhysicsBody::setVelocity(float velocityX, float velocityY)
{
    cpBodySetVel(m_body, cpv(velocityX, velocityY));
}

float CCPhysicsBody::getVelocityLimit(void)
{
    return cpBodyGetVelLimit(m_body);
}

void CCPhysicsBody::setVelocityLimit(float limit)
{
    cpBodySetVelLimit(m_body, limit);
}

float CCPhysicsBody::getAngleVelocity(void)
{
    return -cpBodyGetAngVel(m_body);
}

void CCPhysicsBody::setAngleVelocity(float velocity)
{
    cpBodySetAngVel(m_body, -velocity);
}

float CCPhysicsBody::getAngleVelocityLimit(void)
{
    return -cpBodyGetAngVelLimit(m_body);
}

void CCPhysicsBody::setAngleVelocityLimit(float limit)
{
    cpBodySetAngVelLimit(m_body, -limit);
}

CCPoint CCPhysicsBody::getForce(void)
{
    const cpVect f = cpBodyGetForce(m_body);
    return CCPoint(f.x, f.y);
}

void CCPhysicsBody::getForce(float *forceX, float *forceY)
{
    const cpVect f = cpBodyGetForce(m_body);
    *forceX = f.x;
    *forceY = f.y;
}

void CCPhysicsBody::setForce(const CCPoint &force)
{
    cpBodySetForce(m_body, cpv(force.x, force.y));
}

void CCPhysicsBody::setForce(CCPhysicsVector *force)
{
    cpBodySetForce(m_body, force->getVector());
}

void CCPhysicsBody::setForce(float forceX, float forceY)
{
    cpBodySetForce(m_body, cpv(forceX, forceY));
}

float CCPhysicsBody::getTorque(void)
{
    return cpBodyGetTorque(m_body);
}

void CCPhysicsBody::setTorque(float force)
{
    cpBodySetTorque(m_body, force);
}

void CCPhysicsBody::resetForces(void)
{
    cpBodyResetForces(m_body);
}

void CCPhysicsBody::applyForce(float forceX, float forceY, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyForce(m_body, cpv(forceX, forceY), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyForce(const CCPoint &force, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyForce(m_body, cpv(force.x, force.y), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyForce(CCPhysicsVector *force, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyForce(m_body, force->getVector(), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyImpulse(float forceX, float forceY, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyImpulse(m_body, cpv(forceX, forceY), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyImpulse(const CCPoint &force, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyImpulse(m_body, cpv(force.x, force.y), cpv(offsetX, offsetY));
}

void CCPhysicsBody::applyImpulse(CCPhysicsVector *force, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    cpBodyApplyImpulse(m_body, force->getVector(), cpv(offsetX, offsetY));
}

CCPoint CCPhysicsBody::getPosition(void)
{
    const cpVect p = cpBodyGetPos(m_body);
    return CCPoint(p.x, p.y);
}

void CCPhysicsBody::getPosition(float *x, float *y)
{
    const cpVect p = cpBodyGetPos(m_body);
    *x = p.x;
    *y = p.y;
}

float CCPhysicsBody::getPositionX(void)
{
    const cpVect p = cpBodyGetPos(m_body);
    return p.x;
}

float CCPhysicsBody::getPositionY(void)
{
    const cpVect p = cpBodyGetPos(m_body);
    return p.y;
}

void CCPhysicsBody::setPosition(const CCPoint &pos)
{
    cpBodySetPos(m_body, cpv(pos.x, pos.y));
    if (!m_world->isLocked()) cpSpaceReindexShapesForBody(m_space, m_body);
    if (m_node) m_node->setPosition(pos);
}

void CCPhysicsBody::setPosition(CCPhysicsVector *pos)
{
    cpBodySetPos(m_body, pos->getVector());
    if (!m_world->isLocked()) cpSpaceReindexShapesForBody(m_space, m_body);
    if (m_node) m_node->setPosition(pos->getValue());
}

void CCPhysicsBody::setPosition(float x, float y)
{
    cpBodySetPos(m_body, cpv(x, y));
    if (!m_world->isLocked()) cpSpaceReindexShapesForBody(m_space, m_body);
    if (m_node) m_node->setPosition(x, y);
}

void CCPhysicsBody::setPositionX(float x)
{
    setPosition(x, getPositionY());
}

void CCPhysicsBody::setPositionY(float y)
{
    setPosition(getPositionX(), y);
}

float CCPhysicsBody::getAngle(void)
{
    return -cpBodyGetAngle(m_body);
}

void CCPhysicsBody::setAngle(float angle)
{
    cpBodySetAngle(m_body, angle);
    if (m_node) m_node->setRotation(CC_RADIANS_TO_DEGREES(angle));
}

float CCPhysicsBody::getRotation(void)
{
    return CC_RADIANS_TO_DEGREES(-(cpBodyGetAngle(m_body)));
}

void CCPhysicsBody::setRotation(float rotation)
{
    cpBodySetAngle(m_body, -CC_DEGREES_TO_RADIANS(rotation));
    if (m_node) m_node->setRotation(rotation);
}

float CCPhysicsBody::getElasticity(void)
{
    float maxElasticity = -99999;
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        float elasticity = static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->getElasticity();
        if (elasticity > maxElasticity) maxElasticity = elasticity;
    }
    return maxElasticity;
}

void CCPhysicsBody::setElasticity(float elasticity)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setElasticity(elasticity);
    }
}

float CCPhysicsBody::getFriction(void)
{
    float maxFriction = -99999;
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        float friction = static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->getFriction();
        if (friction > maxFriction) maxFriction = friction;
    }
    return maxFriction;
}

void CCPhysicsBody::setFriction(float friction)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setFriction(friction);
    }
}

bool CCPhysicsBody::isSensor(void)
{
    bool isSensor = false;
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        isSensor = isSensor || static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->isSensor();
    }
    return isSensor;
}

void CCPhysicsBody::setIsSensor(bool isSensor)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setIsSensor(isSensor);
    }
}

int CCPhysicsBody::getCollisionType(void)
{
    return m_shapes->count() > 0 ? static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(0))->getCollisionType() : 0;
}

void CCPhysicsBody::setCollisionType(int type)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setCollisionType(type);
    }
}

int CCPhysicsBody::getCollisionGroup(void)
{
    return m_shapes->count() > 0 ? static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(0))->getCollisionGroup() : 0;
}

void CCPhysicsBody::setCollisionGroup(int group)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setCollisionGroup(group);
    }
}

int CCPhysicsBody::getCollisionLayers(void)
{
    return m_shapes->count() > 0 ? static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(0))->getCollisionLayers() : 0;
}

void CCPhysicsBody::setCollisionLayers(int layers)
{
    for (int i = m_shapes->count() - 1; i >= 0; --i)
    {
        static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i))->setCollisionLayers(layers);
    }
}

float CCPhysicsBody::dist(CCPhysicsBody *other)
{
    return cpvdist(cpBodyGetPos(m_body), cpBodyGetPos(other->getBody()));
}

void CCPhysicsBody::bind(CCNode *node)
{
    unbind();
    m_node = node;
    m_node->retain();
}

void CCPhysicsBody::unbind(void)
{
    CC_SAFE_RELEASE_NULL(m_node);
}

CCNode *CCPhysicsBody::getNode(void)
{
	return m_node;
}

CCPhysicsShape *CCPhysicsBody::addSegmentShape(const CCPoint lowerLeft, const CCPoint lowerRight, float thickness)
{
    return addShape(cpSegmentShapeNew(m_body, cpv(lowerLeft.x, lowerLeft.y), cpv(lowerRight.x, lowerRight.y), thickness));
}

CCPhysicsShape *CCPhysicsBody::addCircleShape(float radius, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    return addShape(cpCircleShapeNew(m_body, radius, cpv(offsetX, offsetY)));
}

/*CCPhysicsShape *CCPhysicsBody::addBoxShape(float width, float height)
{
    return addShape(cpBoxShapeNew(m_body, width, height));
}*/

CCPhysicsShape *CCPhysicsBody::addBoxShape(float width, float height, float offsetX, float offsetY)
{
	cpFloat hw = width / 2.0f;
	cpFloat hh = height / 2.0f;
	cpBB box = cpBBNew(-hw, -hh, hw, hh);
	cpVect verts[] = {
		cpv(box.l, box.b),
		cpv(box.l, box.t),
		cpv(box.r, box.t),
		cpv(box.r, box.b),
	};

	return addShape((cpShape *)cpPolyShapeInit(cpPolyShapeAlloc(), m_body, 4, verts, cpv(offsetX, offsetY)));
}

CCPhysicsShape *CCPhysicsBody::addPolygonShape(CCPointArray *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsVectorArray *cpVertexes = CCPhysicsVectorArray::createFromCCPointArray(vertexes);
    return addPolygonShape(cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}

CCPhysicsShape *CCPhysicsBody::addPolygonShape(int numVertexes, CCPoint *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsVectorArray *cpVertexes = CCPhysicsVectorArray::createFromCCPoint(numVertexes, vertexes);
    return addPolygonShape(cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}

CCPhysicsShape *CCPhysicsBody::addPolygonShape(int numVertexes, cpVect *vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    return addShape(cpPolyShapeNew(m_body, numVertexes, vertexes, cpv(offsetX, offsetY)));
}

#if CC_LUA_ENGINE_ENABLED > 0
CCPhysicsShape *CCPhysicsBody::addPolygonShape(int vertexes, float offsetX/*= 0*/, float offsetY/*= 0*/)
{
    CCPhysicsVectorArray *cpVertexes = CCPhysicsVectorArray::createFromLuaTable(vertexes);
    return addPolygonShape(cpVertexes->count(), cpVertexes->data(), offsetX, offsetY);
}
#endif

void CCPhysicsBody::removeShapeAtIndex(unsigned int index)
{
    CCAssert(index >= 0 && index < m_shapes->count(), "CCPhysicsBody::removeShapeAtIndex() - Invalid index");
    CCPhysicsShape *shapeObject = static_cast<CCPhysicsShape *>(m_shapes->objectAtIndex(index));
	m_world->removeShape(shapeObject);
    m_shapes->removeObjectAtIndex(index);
}

void CCPhysicsBody::removeShape(CCPhysicsShape *shapeObject)
{
    removeShapeAtIndex(m_shapes->indexOfObject(shapeObject));
}

void CCPhysicsBody::removeAllShape(void)
{
    unsigned int count = m_shapes->count();
    for (unsigned int i = 0; i < count; ++i)
    {
        m_world->removeShape(static_cast<CCPhysicsShape*>(m_shapes->objectAtIndex(i)));
    }
	m_shapes->removeAllObjects();
}


void CCPhysicsBody::removeSelf(bool unbindNow/*= true*/)
{
	if (unbindNow) unbind();
    removeAllShape();
	breakAllJoints();
	m_world->removeBody(this);
}

void CCPhysicsBody::update(float dt)
{
    if (!m_node) return;
    m_node->setPosition(getPosition());
    m_node->setRotation(getRotation());

    if (cpBodyIsSleeping(m_body) != m_postIsSleeping)
    {
        if (m_postIsSleeping)
        {
            cpBodySleep(m_body);
        }
        else
        {
            cpBodyActivate(m_body);
        }
    }
}

CCPinJoint *CCPhysicsBody::pinJoint(CCPhysicsBody *otherBody)
{
	this->checkJointWith(otherBody, SLIDE_JOINT);
	CCPhysicsVector *archrA = CCPhysicsVector::create(0, 0);
	CCPhysicsVector *archrB = CCPhysicsVector::create(0, 0);
	return this->pinJoint(otherBody, archrA, archrB);
}

CCPinJoint *CCPhysicsBody::pinJoint(CCPhysicsBody *otherBody, CCPhysicsVector *archrThis, CCPhysicsVector *archrOther)
{
	this->checkJointWith(otherBody, PIN_JOINT);
	CCPinJoint *pinJoint = new CCPinJoint(this->m_world, this, otherBody, archrThis->getVector(), archrOther->getVector());
	this->addJoint(pinJoint);
	otherBody->addJoint(pinJoint);
	return pinJoint;
}

CCDampedSpringJoint *CCPhysicsBody::dampedSpringJoint(CCPhysicsBody *otherBody,
	cpFloat restLength, cpFloat stiffness, cpFloat damping)
{
	this->checkJointWith(otherBody, SLIDE_JOINT);
	CCPhysicsVector *bodyAVect = CCPhysicsVector::create(0, 0);
	CCPhysicsVector *bodyBVect = CCPhysicsVector::create(0, 0);
	return this->dampedSpringJoint(otherBody, bodyAVect, bodyBVect, restLength, stiffness, damping);
}

CCDampedSpringJoint *CCPhysicsBody::dampedSpringJoint(CCPhysicsBody *otherBody, 
	CCPhysicsVector *archrThis, CCPhysicsVector *archrOther,
	cpFloat restLength, cpFloat stiffness, cpFloat damping)
{
	this->checkJointWith(otherBody, DAMPED_SPRING);
	CCDampedSpringJoint *dampedSpringJoint = new CCDampedSpringJoint(this->m_world, this, otherBody, 
		archrThis->getVector(), archrOther->getVector(),
		restLength, stiffness, damping);
	this->addJoint(dampedSpringJoint);
	otherBody->addJoint(dampedSpringJoint);
	return dampedSpringJoint;
}

CCSlideJoint *CCPhysicsBody::slideJoint(CCPhysicsBody *otherBody, cpFloat min, cpFloat max)
{
	this->checkJointWith(otherBody, SLIDE_JOINT);
	CCPhysicsVector *archrThis = CCPhysicsVector::create(0, 0);
	CCPhysicsVector *archrOther = CCPhysicsVector::create(0, 0);
	return this->slideJoint(otherBody, archrThis, archrOther, min, max);
}

CCSlideJoint *CCPhysicsBody::slideJoint(CCPhysicsBody *otherBody, CCPhysicsVector *archrThis, CCPhysicsVector *archrOther,
	cpFloat min, cpFloat max)
{
	this->checkJointWith(otherBody, SLIDE_JOINT);
	CCSlideJoint *slideJoint = new CCSlideJoint(this->m_world, 
		this, otherBody, archrThis->getVector(), archrOther->getVector(), min, max);
	this->addJoint(slideJoint);
	otherBody->addJoint(slideJoint);
	return slideJoint;
}

CCPivotJoint *CCPhysicsBody::pivotJoint(CCPhysicsBody *otherBody)
{
	this->checkJointWith(otherBody, PIVOT_JOINT);
	CCPhysicsVector *archrThis = CCPhysicsVector::create(0, 0);
	CCPhysicsVector *archrOther = CCPhysicsVector::create(0, 0);
	return this->pivotJoint(otherBody, archrThis, archrOther);
}

CCPivotJoint *CCPhysicsBody::pivotJoint(CCPhysicsBody *otherBody, CCPhysicsVector *archrThis, CCPhysicsVector *archrOther)
{
	this->checkJointWith(otherBody, PIVOT_JOINT);
	CCPivotJoint *pivotJoint = new CCPivotJoint(this->m_world, this, otherBody, archrThis->getVector(), archrOther->getVector());
	this->addJoint(pivotJoint);
	otherBody->addJoint(pivotJoint);
	return pivotJoint;
}

CCPivotJoint *CCPhysicsBody::pivotJoint(CCPhysicsBody *otherBody, CCPhysicsVector *pivot)
{
	this->checkJointWith(otherBody, PIVOT_JOINT);
	CCPivotJoint *pivotJoint = new CCPivotJoint(this->m_world, this, otherBody, pivot->getVector());
	this->addJoint(pivotJoint);
	otherBody->addJoint(pivotJoint);
	return pivotJoint;
}

void CCPhysicsBody::addJoint(CCJoint *joint)
{
	if (this->m_joints->count() >= MAX_JOINT)
	{
		char errMsg[80];
		sprintf(errMsg, "body's joints count reach the MAX_JOINT:%d", MAX_JOINT);
		CCAssert(this->m_joints->count() < MAX_JOINT, errMsg);
	}
	unsigned int index = this->m_joints->indexOfObject(joint);
	if (index >= UINT_MAX) // means this joint is not in m_joints
	{
		this->m_joints->addObject(joint);
	}
}

void CCPhysicsBody::removeJoint(CCJoint *joint)
{
	unsigned int index = this->m_joints->indexOfObject(joint);
	if (index < this->m_joints->count())
	{
		this->m_joints->removeObjectAtIndex(index);
	}
}

void CCPhysicsBody::breakAllJoints(void)
{
	unsigned int count = this->m_joints->count();
	count = count <= MAX_JOINT ? count : MAX_JOINT;
	vector<CCJoint*> tmpJoints;
	for (unsigned int i = 0; i < count; i++)
	{
		CCJoint* joint = static_cast<CCJoint*>(this->m_joints->objectAtIndex(i));
		if (joint != NULL)
		{
			tmpJoints.push_back(joint);
		}
	}
	vector<CCJoint*>::iterator p;
	p = tmpJoints.begin();
	for (; p != tmpJoints.end(); p++)
	{
		(*p)->breakJoint();
	}
	tmpJoints.clear();
}

void CCPhysicsBody::breakJointByType(JointType jointType)
{
	unsigned int count = this->m_joints->count();
	for (unsigned int i = 0; i < count; i++)
	{
		CCJoint* joint = static_cast<CCJoint*>(this->m_joints->objectAtIndex(i));
		if (joint != NULL && joint->getJointType() == jointType) {
			joint->breakJoint();
		}
	}
}

CCArray *CCPhysicsBody::getJointsWith(CCPhysicsBody *otherBody)
{
	CCArray *arr = CCArray::create();
	unsigned int count = this->m_joints->count();
	if (otherBody != NULL && otherBody != this && this->m_joints != NULL && count > 0)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			CCJoint* joint = static_cast<CCJoint*>(this->m_joints->objectAtIndex(i));
			if (joint->getBodyA() == otherBody || joint->getBodyB() == otherBody) {
				arr->addObject(joint);
			}
		}
	}
	return arr;
}

void CCPhysicsBody::checkJointWith(CCPhysicsBody *otherBody, JointType type)
{
	CCAssert(otherBody != NULL, "body can not joint with NULL");
	CCAssert(otherBody != this, "body can not joint with itself");
}

CCPhysicsShape *CCPhysicsBody::addShape(cpShape *shape)
{
    CCPhysicsShape *shapeObject = CCPhysicsShape::create(shape);
    m_world->addShape(shapeObject);
    m_shapes->addObject(shapeObject);
    return shapeObject;
}
