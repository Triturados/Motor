#include "Rigidbody.h"
#include <cmath>
#include <iostream>

#include "LinearMath/btDefaultMotionState.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h"
#include "BulletCollision/NarrowPhaseCollision/btPointCollector.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h"
#include "BulletCollision/CollisionShapes/btConvexShape.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

#include <StringFormatter.h>
#include "Vector3.h"
#include "Vector4.h"
#include "PhysicsManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"

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

		bool RigidBody::collidesWithGameObject(RigidBody* go) const
		{

			if (go == nullptr) return false;

			//Se obtiene el rb de la otra entidad
			//auto* otherRigidBody = reinterpret_cast<RigidBody*>(go->getComponent<RigidBody>());

			if (!go->isActive())
				return false;

			//Declaracion del algoritmo de Vorono
			btVoronoiSimplexSolver simplexSolver;
			btGjkEpaPenetrationDepthSolver epaPenSolver;
			btPointCollector collPoint;

			//Detector de colisiones
			btGjkPairDetector convexConvex(
				static_cast<btConvexShape*>(rigidBody->getCollisionShape()),
				static_cast<btConvexShape*>(go->rigidBody->getCollisionShape()),
				&simplexSolver, &epaPenSolver);

			//Mediante un input que guarda referencia de los dos objetos,
			//se genera un output (collPoint), de manera que, posteriormente, se puede
			//comprobar si se ha producido una colision.
			btGjkPairDetector::ClosestPointInput input;
			input.m_transformA = rigidBody->getWorldTransform();
			input.m_transformB = go->rigidBody->getWorldTransform();
			convexConvex.getClosestPoints(input, collPoint, nullptr);

			return collPoint.m_hasResult && collPoint.m_distance <= 0;
		}

		RigidBody::RigidBody() : tr(nullptr), rigidBody(nullptr)
		{
			stateMode = (RBState)0;
			mass = 1;
		}

		RigidBody::~RigidBody()
		{
			delete lastForce;
			delete acc;
			if (col) delete col;
			col = nullptr;
			delete tr;
			delete rigidBody;
		}

		void  RigidBody::init()
		{
			tr = gameObject->getComponent<Transform>();
			Utilities::Vector3<float> pos = *(tr->getPos());
			Utilities::Vector3<float> scale = *(tr->getScale());
			if (rigidBody == nullptr) {
				//Creamos un RB y se anade al PhysicsManager
				rigidBody = Physics::PhysicsManager::getInstance()->createRB(pos, scale, mass, (int)shape);
				rigidBody->setRestitution(restitution);

				/*btQuaternion q;
				Utilities::Vector4<float> vRot = *tr->getRot();
				q.getEulerZYX(vRot.x, vRot.y, vRot.z);
				rigidBody->setWorldTransform(btTransform(q, cvt(pos)));
				rigidBody->setMassProps(mass, btVector3(1.0, 1.0, 1.0));
				rigidBody->setDamping(0.5, 0.5);*/
			}
			col = new LoveEngine::Physics::Collider();
			col->setGO(gameObject);
		}

		void RigidBody::update()
		{
			const auto worldTransform = rigidBody->getWorldTransform();

			Utilities::Vector3<float> newPos = cvt(worldTransform.getOrigin());
			Utilities::Vector4<float> newRot = cvt(worldTransform.getRotation());
			
			tr->setPos(newPos);
			tr->setRot(newRot);

			/*if (onCollisionEnter(other)) {
				std::cout << "colisione" << std::endl;
			}*/
		}

		void RigidBody::stepPhysics()
		{
			const auto worldTransform = rigidBody->getWorldTransform();

			Utilities::Vector3<float> newPos = cvt(worldTransform.getOrigin());
			Utilities::Vector4<float> newRot = cvt(worldTransform.getRotation());
			//std::cout << "PosRB: " << newPos.x << ", " << newPos.y << ", " << newPos.z << std::endl;
			tr->setPos(newPos);
			tr->setRot(newRot);
		}

		void RigidBody::receiveMessage(Utilities::StringFormatter& sf)
		{
			setShape(sf.getString("shape"));
			sf.tryGetFloat("restitution", restitution);
			sf.tryGetFloat("mass", mass);

			std::string str;
			if (sf.tryGetString("state", str)) {

				if (str == "kinematic") {
					stateMode = RBState::Kinematic;
				}
				else if (str == "dynamic") {
					stateMode = RBState::Dynamic;
				}
				else  if (str == "static") {
					stateMode = RBState::Static;
				}
			}
		}

		void RigidBody::addForce(Utilities::Vector3<float> force, Utilities::Vector3<float> relativePos, int type)
		{
			lastForce->x = force.x; lastForce->y = force.y; lastForce->z = force.z;

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
		void RigidBody::setShape(std::string nameS_)
		{
			if (nameS_ == "cube") {
				shape = TipoForma::Cube;
			}
			else if (nameS_ == "sphere") {
				shape = TipoForma::Sphere;
			}
			else if (nameS_ == "plane") {
				shape = TipoForma::Plane;
			}
			else if (nameS_ == "cone") {
				shape = TipoForma::Cone;
			}
			else if (nameS_ == "cylinder") {
				shape = TipoForma::Cylinder;
			}
			else {
				shape = TipoForma::Cube;
			}
		}

		void RigidBody::setLinearVelocity(Utilities::Vector3<float> vel)
		{
			rigidBody->setLinearVelocity(cvt(vel));
		}

		Utilities::Vector3<float>* RigidBody::getVelocity() const noexcept
		{
			auto vel = rigidBody->getLinearVelocity();
			return new Utilities::Vector3<float>(vel.x(), vel.y(), vel.z());
		}

		void RigidBody::receiveComponent(int i, Component* c)
		{

			if (i == 1) {
				other = static_cast<RigidBody*>(c);
			}
		}


		bool RigidBody::onCollisionEnter(RigidBody* other)
		{

			//Devuelve true en caso de existir colision
			if (enabled) {
				
				return collidesWithGameObject(other);
			}

			return false;
		}
	}
}
