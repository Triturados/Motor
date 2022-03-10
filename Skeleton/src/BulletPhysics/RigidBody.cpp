#include "Rigidbody.h"
#include <cmath>

#include "LinearMath/btDefaultMotionState.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h"
#include "BulletCollision/NarrowPhaseCollision/btPointCollector.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h"
#include "BulletCollision/CollisionShapes/btConvexShape.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

#include "Vector3.h"

RigidBody::RigidBody() : Component(), rb(nullptr), tr(nullptr), mass(1.0f)
{

}

RigidBody::~RigidBody()
{
	
}

void RigidBody::init()
{
	
}

void RigidBody::update(float deltaTime)
{
	
}

void RigidBody::stepPhysics()
{

}

void RigidBody::setPosition(const Vector3<float>& newPos)
{
	
}

void RigidBody::setGravity(const Vector3<float>& newGrav)
{

}

void RigidBody::setTrigger(const bool trigger) {
	
}

void RigidBody::setKinematic(const bool kinematic) {

}

void RigidBody::setStatic(const bool static) {

	
}

void RigidBody::setRestitution(float restitution)
{
	
}

void RigidBody::setLinearVelocity(const Vector3<float>& vel)
{

}

void RigidBody::setFriction(float friction)
{

}

void RigidBody::setCollisionShape(btCollisionShape* newShape)
{

}


const Vector3<float>& RigidBody::getLinearVelocity() const
{
	return Vector3<float>();
}

bool RigidBody::isTrigger() const
{
	return true;
}

bool RigidBody::isKinematic() const
{
	return rb->isKinematicObject();
}

bool RigidBody::isStatic() const
{
	return rb->isStaticObject();
}

btCollisionShape* RigidBody::getShape() const
{
	return rb->getCollisionShape();
}

btRigidBody* RigidBody::getBtRb() const
{
	return rb;
}

int RigidBody::getMask() const
{
	return 0;
}

void RigidBody::addForce(const Vector3<float>& force, Vector3<float>& relativePos, int type)
{
	
}

bool RigidBody::onCollisionEnter(const std::string& id) const
{
	return true;
}
