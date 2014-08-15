
#ifndef __CCPHYSICS_BODY_H_
#define __CCPHYSICS_BODY_H_

#include <string>
#include <vector>
#include "cocos2d.h"
#include "chipmunk.h"
#include "CCPhysicsSupport.h"
#include "constraints/CCJoint.h"

using namespace std;
using namespace cocos2d;

class CCPhysicsWorld;
class CCPhysicsShape;
class CCJoint;
class CCPinJoint;
class CCDampedSpringJoint;
class CCSlideJoint;
class CCPivotJoint;

class CCPhysicsBody : public CCObject
{
public:
    static CCPhysicsBody *defaultStaticBody(CCPhysicsWorld *world);
    static CCPhysicsBody *createStaticBody(CCPhysicsWorld *world);
    static CCPhysicsBody *create(CCPhysicsWorld *world, float mass, float moment);
    virtual ~CCPhysicsBody(void);

    cpBody *getBody(void);

    // extended properties
    const char *getName(void);
    void setName(const char *name);

    // body behaviors
    bool isSleeping(void);
    void activate(void);
    void sleep(void);

    // body properties
    int getTag(void);
    void setTag(int tag);

    float getMass(void);
    void setMass(float mass);

    float getInertia(void);
    void setInertia(float inertia);

    CCPoint getVelocity(void);
    void getVelocity(float *velocityX, float *velocityY);
    void setVelocity(const CCPoint &velocity);
    void setVelocity(CCPhysicsVector* velocity);
    void setVelocity(float velocityX, float velocityY);

    float getVelocityLimit(void);
    void setVelocityLimit(float limit);

    float getAngleVelocity(void);
    void setAngleVelocity(float velocity);

    float getAngleVelocityLimit(void);
    void setAngleVelocityLimit(float limit);

    CCPoint getForce(void);
    void getForce(float *forceX, float *forceY);
    void setForce(const CCPoint &force);
    void setForce(CCPhysicsVector *force);
    void setForce(float forceX, float forceY);

    float getTorque(void);
    void setTorque(float force);

    void resetForces(void);
    void applyForce(float forceX, float forceY, float offsetX = 0, float offsetY = 0);
    void applyForce(const CCPoint &force, float offsetX = 0, float offsetY = 0);
    void applyForce(CCPhysicsVector *force, float offsetX = 0, float offsetY = 0);
    void applyImpulse(float forceX, float forceY, float offsetX = 0, float offsetY = 0);
    void applyImpulse(const CCPoint &force, float offsetX = 0, float offsetY = 0);
    void applyImpulse(CCPhysicsVector *force, float offsetX = 0, float offsetY = 0);

    CCPoint getPosition(void);
    void getPosition(float *x, float *y);
    float getPositionX(void);
    float getPositionY(void);
    void setPosition(const CCPoint &pos);
    void setPosition(CCPhysicsVector *pos);
    void setPosition(float x, float y);
    void setPositionX(float x);
    void setPositionY(float y);

    float getAngle(void);
    void setAngle(float angle);

    float getRotation(void);
    void setRotation(float rotation);

    // shape properties
    float getElasticity(void);
    void setElasticity(float elasticity);
    float getFriction(void);
    void setFriction(float friction);
    bool isSensor(void);
    void setIsSensor(bool isSensor);
    int getCollisionType(void);
    void setCollisionType(int type);
    int getCollisionGroup(void);
    void setCollisionGroup(int group);
    int getCollisionLayers(void);
    void setCollisionLayers(int layers);

    // helper
    float dist(CCPhysicsBody *other);

    // binding to node
    void bind(CCNode *node);
    void unbind(void);
    CCNode *getNode(void);

    // shapes management
    CCPhysicsShape *addSegmentShape(const CCPoint lowerLeft, const CCPoint lowerRight, float thickness);
    CCPhysicsShape *addCircleShape(float radius, float offsetX = 0, float offsetY = 0);
	CCPhysicsShape *addBoxShape(float width, float height, float offsetX = 0, float offsetY = 0);

    CCPhysicsShape *addPolygonShape(CCPointArray *vertexes, float offsetX = 0, float offsetY = 0);
    CCPhysicsShape *addPolygonShape(int numVertexes, CCPoint *vertexes, float offsetX = 0, float offsetY = 0);
    CCPhysicsShape *addPolygonShape(int numVertexes, cpVect *vertexes, float offsetX = 0, float offsetY = 0);
#if CC_LUA_ENGINE_ENABLED > 0
	CCPhysicsShape *addPolygonShape(int vertexes, float offsetX = 0, float offsetY = 0);
#endif
    void removeShapeAtIndex(unsigned int index);
    void removeShape(CCPhysicsShape *shapeObject);
    void removeAllShape(void);

	// cleanup
	void removeSelf(bool unbindNow = true);

    // delegate
    virtual void update(float dt);


	// Joints management start
	static const unsigned int MAX_JOINT = 1024;

	CCPinJoint *pinJoint(CCPhysicsBody *otherBody);
	CCPinJoint *pinJoint(CCPhysicsBody *otherBody, CCPhysicsVector *archrThis, CCPhysicsVector *archrOther);

	CCDampedSpringJoint *dampedSpringJoint(CCPhysicsBody *otherBody,
                                           cpFloat restLength, cpFloat stiffness=0, cpFloat damping=0);
	CCDampedSpringJoint *dampedSpringJoint(CCPhysicsBody *otherBody, CCPhysicsVector *archrThis, CCPhysicsVector *archrOther,
                                           cpFloat restLength, cpFloat stiffness = 0, cpFloat damping = 0);

	CCSlideJoint *slideJoint(CCPhysicsBody *otherBody, cpFloat min, cpFloat max);
	CCSlideJoint *slideJoint(CCPhysicsBody *otherBody, CCPhysicsVector *archrThis, CCPhysicsVector *archrOther,
                             cpFloat min, cpFloat max);

	CCPivotJoint *pivotJoint(CCPhysicsBody *otherBody);
	CCPivotJoint *pivotJoint(CCPhysicsBody *otherBody, CCPhysicsVector *archrThis, CCPhysicsVector *archrOther);
	CCPivotJoint *pivotJoint(CCPhysicsBody *otherBody, CCPhysicsVector *pivot);

	void breakAllJoints(void);
	void breakJointByType(JointType jointType);

	// get all joints constraint with the otherBody
	CCArray *getJointsWith(CCPhysicsBody *otherBody);
	// Joints management end

private:
    CCPhysicsBody(CCPhysicsWorld *world);
    bool initWithDefaultStaticBody(void);
    bool initWithStaticBody(void);
    bool initWithBody(float mass, float moment);

    CCPhysicsWorld *m_world;
    cpSpace *m_space;
    cpBody *m_body;
    CCArray *m_shapes;
	CCArray *m_joints;
    CCNode *m_node;
    int m_tag;
    string m_name;

    cpBool m_postIsSleeping;

    // helper
    CCPhysicsShape *addShape(cpShape *shape);
	friend class CCJoint;

	// remove joint data
	void addJoint(CCJoint *joint);
	void removeJoint(CCJoint *joint);
    
	void checkJointWith(CCPhysicsBody *otherBody, JointType type);
};

#endif // __CCPHYSICS_BODY_H_
