#pragma once

#include "Component.h"

class btCollisionShape;
class GameObject;
class btRigidBody;
class Transform;

template <typename T>
class Vector3;

enum class ForceMode {
	FORCE,
	ACCELERATION,
	IMPULSE,
	VELOCITY_CHANGE
};

class RigidBody : public Component
{
private:
	//Masa del Rigidbody
	float mass;

	//Rigidbody principal
	btRigidBody* rb;

	Transform* tr;

public:
	RigidBody();
	virtual ~RigidBody();


	void init();
	void update(float deltaTime);
	void stepPhysics();

	void setPosition(const Vector3<float>& newPos);

	void setGravity(const Vector3<float>& newGrav);

	void setTrigger(bool trigger_);

	void setKinematic(bool kinematic_);

	void setStatic(bool _static);

	void setRestitution(float restitution);

	void setLinearVelocity(const Vector3<float>& vel);

	void setFriction(float friction);

	void setCollisionShape(btCollisionShape* newShape);

	void setLinearFactor(const Vector3<float>& axis);

	void setAngularFactor(const Vector3<float>& axis);

	const Vector3<float>& getLinearVelocity() const;

	bool isTrigger() const;

	bool isKinematic() const;

	bool isStatic() const;

	btCollisionShape* getShape() const;

	btRigidBody* getBtRb() const;

	int getMask()const;

	void addForce(const Vector3<float>& force, Vector3<float>& relativePos, int type = (int) ForceMode::FORCE);

	bool onCollisionEnter(const std::string& id) const;
};
