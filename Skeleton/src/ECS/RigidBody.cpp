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
#include "Vector4.h"
#include "PhysicsManager.h"
#include "Transform.h"

namespace LoveEngine {
	namespace ECS {


		inline Utilities::Vector3<float> cvt(const btVector3& V) {
			return Utilities::Vector3(V.x(), V.y(), V.z());
		}

		inline btVector3 cvt(const Utilities::Vector3<float>& V) {
			return btVector3(V.x, V.y, V.z);
		}

		inline Utilities::Vector4<float> cvt(const btQuaternion& V) {
			return Utilities::Vector4(V.x(), V.y(), V.z(), V.w());
		}

		RigidBody::RigidBody() : tr(nullptr), rigidBody(nullptr)
		{
		}

		RigidBody::~RigidBody()
		{
			delete lastForce;
			delete acc;

			delete tr;
			delete rigidBody;
		}

		void  RigidBody::init()
		{
			Utilities::Vector3<float> pos = *(tr->getPos());
			if (rigidBody == nullptr) {
				//Creamos un RB y se anade al PhysicsManager
				rigidBody = PhysicsManager::getInstance()->createRB(pos, 0, mass);
				btQuaternion q;
				Utilities::Vector4<float> vRot = *tr->getRot();
				q.getEulerZYX(vRot.x, vRot.y, vRot.z);
				rigidBody->setWorldTransform(btTransform(q, cvt(pos)));
				rigidBody->setMassProps(1.0f, btVector3(1.0, 1.0, 1.0));
				rigidBody->setDamping(0.5, 0.5);
			}
		}

		void RigidBody::update()
		{
			const auto worldTransform = rigidBody->getWorldTransform();

			Utilities::Vector3 newPos = cvt(worldTransform.getOrigin());
			Utilities::Vector4 newRot = cvt(worldTransform.getRotation());

			tr->setPos(&newPos);
			tr->setRot(&newRot);
		}

		void RigidBody::addForce(Utilities::Vector3<float>& force, Utilities::Vector3<float>& relativePos, int type)
		{
			lastForce = &force;
			if (enabled) {
				if (relativePos == Utilities::Vector3(0.0f, 0.0f, 0.0f)) {
					if (type == (int)ForceMode::FORCE)
						rigidBody->applyCentralForce(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)));
					else if (type == (int)ForceMode::IMPULSE)
						rigidBody->applyCentralImpulse(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)));
				}
				else {
					if (type == (int)ForceMode::FORCE)
						rigidBody->applyForce(
							(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z))),
							(btVector3(btScalar(relativePos.x), btScalar(relativePos.y), btScalar(relativePos.z))));
					else if (type == (int)ForceMode::IMPULSE)
						rigidBody->applyImpulse(
							(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z))),
							(btVector3(btScalar(relativePos.x), btScalar(relativePos.y), btScalar(relativePos.z))));
				}
			}
		}

		void RigidBody::setTransform(Transform* t_)
		{
			tr = t_;
		}

		void RigidBody::setMass(float mass_)
		{
			mass = mass_;
		}
	}
}
