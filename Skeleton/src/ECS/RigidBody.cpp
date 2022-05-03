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

		//Conversor de vector3 de bullet al nuestro
		inline Utilities::Vector3<float> cvt(const btVector3& V) {
			return Utilities::Vector3(V.x(), V.y(), V.z());
		}

		//Conversor de nuestro vector3 al de bullet
		inline btVector3 cvt(const Utilities::Vector3<float>& V) {
			return btVector3(V.x, V.y, V.z);
		}

		//Conversor del cuaternion de bullet al nuestro
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
			stateMode = (RBState)2;
			mass = 1;
		}

		RigidBody::~RigidBody()
		{
			if (col) delete col;
			col = nullptr;
			Physics::PhysicsManager::getInstance()->destroyRigidBody(rigidBody);
			//delete rigidBody;
			rigidBody = nullptr;
		}

		void  RigidBody::init()
		{
			try
			{
				if (!gameObject->getComponent<Transform>())
					throw "Error, el objeto con RB no tiene Tranform";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			tr = gameObject->getComponent<Transform>();
			Utilities::Vector3<float> pos = *(tr->getPos());
			Utilities::Vector3<float> rotvector3 = *(tr->getRot());
			Utilities::Vector4<float> rot(rotvector3.x, rotvector3.y, rotvector3.z, 0.0);
			if (rigidBody == nullptr) {
				//Creamos un RB y se anade al PhysicsManager

				if (colliderScale->x == -1 && colliderScale->y == -1 && colliderScale->z == -1) colliderScale = tr->getScale();

				rigidBody = Physics::PhysicsManager::getInstance()->createRB(pos, *(colliderScale), mass, (int)shape, rot);
				setRestitution(restitution);
				setTrigger(trigger);
				//rigidBody->setDamping(0, 0);

				if (stateMode == RBState::Static) {
					setStatic(true);
				}
				else if (stateMode == RBState::Kinematic) {
					setKinematic(true);
				}
				else if (stateMode == RBState::Dynamic) {
					setDynamic(true);
				}
			}
			col = new LoveEngine::Physics::Collider();
			col->setGO(gameObject);
			rigidBody->setUserPointer((void*)col);
		}

		void RigidBody::stepPhysics()
		{
			const auto& worldTransform = rigidBody->getWorldTransform();

			Utilities::Vector3<float> newPos = cvt(worldTransform.getOrigin());
			btScalar rotX, rotY, rotZ;
			worldTransform.getRotation().getEulerZYX(rotZ, rotY, rotX);
			btVector3 rot = { rotX,rotY,rotZ };
			Utilities::Vector3<float> newRot = cvt(rot);

			Utilities::Vector3<float> newRotToVec4(newRot.x, newRot.y, newRot.z);

			tr->setPos(newPos);
			tr->setRot(newRotToVec4);
		}

		void RigidBody::setRotation(Utilities::Vector3<int> axis,float angle)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			btTransform& rbTr = rigidBody->getWorldTransform();
			btVector3 _axis(axis.x, axis.y, axis.z);

			btQuaternion rot;
		
			rot.setRotation(_axis, angle);
				 
			rbTr.setRotation(rot);
		}

		void RigidBody::setDamping(float r, float s)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch(const char* e){
				std::cout << e << std::endl;
			}

			rigidBody->setDamping(r, s);
		}

		void RigidBody::receiveMessage(Utilities::StringFormatter& sf)
		{
			//trigger = false;
			sf.tryGetBool("trigger", trigger);
			//setTrigger(trigger);
			setShape(sf.getString("shape"));
			sf.tryGetFloat("restitution", restitution);
			sf.tryGetFloat("mass", mass);

			colliderScale = new Utilities::Vector3<float>(-1, -1, -1);
			sf.tryGetVector3("colliderScale", *(colliderScale));

			std::string str;
			if (sf.tryGetString("state", str)) {

				if (str == "kinematic") {
					stateMode = RBState::Kinematic;
				}
				else  if (str == "static") {
					stateMode = RBState::Static;
				}
				else if (str == "dynamic") {
					stateMode = RBState::Dynamic;
				}
			}
		}

		void RigidBody::addForce(Utilities::Vector3<float> force, Utilities::Vector3<float> relativePos, ForceMode mode)
		{
			if (enabled) {
				if (relativePos == Utilities::Vector3(0.0f, 0.0f, 0.0f)) {
					if (mode == ForceMode::FORCE)
						rigidBody->applyCentralForce(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)));
					else if (mode == ForceMode::IMPULSE)
						rigidBody->applyCentralImpulse(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)));
					else if (mode == ForceMode::ACCELERATION) {
						force = force * mass;
						rigidBody->applyCentralImpulse(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)));
					}
				}
				else {
					if (mode == ForceMode::FORCE)
						rigidBody->applyForce(
							(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z))),
							(btVector3(btScalar(relativePos.x), btScalar(relativePos.y), btScalar(relativePos.z))));
					else if (mode == ForceMode::IMPULSE)
						rigidBody->applyImpulse(
							(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z))),
							(btVector3(btScalar(relativePos.x), btScalar(relativePos.y), btScalar(relativePos.z))));
					else if (mode == ForceMode::ACCELERATION) {
					force = force * mass;
					rigidBody->applyImpulse((btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z))),
						(btVector3(btScalar(relativePos.x), btScalar(relativePos.y), btScalar(relativePos.z))));
				}

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
			else if (nameS_ == "capsule") {
				shape = TipoForma::Capsule;
			}
			else {
				shape = TipoForma::Cube;
			}
		}

		void RigidBody::setLinearVelocity(Utilities::Vector3<float> vel)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}
			rigidBody->setLinearVelocity(cvt(vel));
		}

		void RigidBody::setAngularVelocity(Utilities::Vector3<float> vel)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}
			rigidBody->setAngularVelocity(cvt(vel));
		}

		void RigidBody::setTrigger(bool trigger_)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}
			trigger = trigger_;
			if (trigger) {
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
			}
			else {
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
			}
		}

		void RigidBody::setKinematic(bool kin_)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}
			if (kin_) {
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			}
			else {
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
			}
		}


		void RigidBody::setStatic(bool static_)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			if (static_) {
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
			}
			else {
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & ~btCollisionObject::CF_STATIC_OBJECT);
			}
		}

		void RigidBody::setDynamic(bool dinamic_)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			if (dinamic_) {
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_DYNAMIC_OBJECT);
			}
			else {
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & ~btCollisionObject::CF_DYNAMIC_OBJECT);
			}
		}

		void RigidBody::setRBGravity(Utilities::Vector3<float> newRBGrav)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			rigidBody->setGravity(cvt(newRBGrav));
		}

		void RigidBody::setRestitution(float resti)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			if (enabled) {
				//restricciones
				if (resti < 0) {
					restitution = 0;
				}
				else if (resti > 1) {
					restitution = 1;
				}

				rigidBody->setRestitution(restitution);
			}
		}

		void RigidBody::setFriccion(float friction)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			if (enabled) {
				rigidBody->setFriction(friction);
			}
		}

		void RigidBody::setLinearFactor(Utilities::Vector3<float> vect)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			rigidBody->setLinearFactor(cvt(vect));
		}

		void RigidBody::setAngularFactor(Utilities::Vector3<float> vect)
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			rigidBody->setAngularFactor(cvt(vect));
		}

		Utilities::Vector3<float>* RigidBody::getVelocity() const noexcept
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			auto vel = rigidBody->getLinearVelocity();
			return new Utilities::Vector3<float>(vel.x(), vel.y(), vel.z());
		}

		Utilities::Vector4<float>* RigidBody::getRotation() const noexcept
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			return new Utilities::Vector4<float>(cvt(rigidBody->getWorldTransform().getRotation()));
		}

		Utilities::Vector3<float>* RigidBody::getGravity() const
		{
			try {
				if (rigidBody == nullptr)
					throw "El RB no esta inicializado";
			}
			catch (const char* e) {
				std::cout << e << std::endl;
			}

			return new Utilities::Vector3<float>(cvt(rigidBody->getGravity()));
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
