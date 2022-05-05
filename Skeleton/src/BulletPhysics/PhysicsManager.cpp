#include "PhysicsManager.h"
#include <iostream>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <GameObject.h>
#include <OgreRenderer.h>
#include <Error_handling.h>
#include <SingletonInfo.h>
#include "DebugDrawer.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Collider.h"
#include "RigidBody.h"
#define PI 3.1415926535897932384


namespace LoveEngine {
	namespace Physics {
		PhysicsManager* PhysicsManager::instance_ = nullptr;

		PhysicsManager* PhysicsManager::getInstance() {
			return instance_;
		}

		PhysicsManager::PhysicsManager() {

			if (instance_ != nullptr) {
				assert("No se ha podido crear la instancia del PhysicsManager.", false);
			}

			init(Utilities::Vector3<float>(0, -60, 0));

			PhysicsManager::instance_ = this;
		}

		PhysicsManager::~PhysicsManager() {

			destroy();
		}

		void FunctCallbackEnter(btPersistentManifold* const& manifold) {

			const btCollisionObject* obA = manifold->getBody0();
			const btCollisionObject* obB = manifold->getBody1();

			if (obA != nullptr && obB != nullptr) {
				Collider* coA = static_cast<Collider*>(obA->getUserPointer());
				Collider* coB = static_cast<Collider*>(obB->getUserPointer());
				if (coB != nullptr && coA != nullptr) coA->onCollisionEnter(coB->getGO());

				if (coB != nullptr && coA != nullptr) coB->onCollisionEnter(coA->getGO());
				
			}
		}

		void FunctCallbackExit(btPersistentManifold* const& manifold) {

			// Call OnCollisionExit and OnTriggerExit of both objects
			const btCollisionObject* obA = manifold->getBody0();
			const btCollisionObject* obB = manifold->getBody1();

			// Si son entidades llamamos a sus callbacks respectivos
			if (obA != nullptr && obB != nullptr) {
				Collider* coA = static_cast<Collider*>(obA->getUserPointer());
				Collider* coB = static_cast<Collider*>(obB->getUserPointer());
				if (coB != nullptr && coA != nullptr && coB->getGO() != nullptr && coA->getGO() != nullptr) {
					coA->onCollisionExit(coB->getGO());
				}

				if (coB != nullptr && coA != nullptr) {
					coB->onCollisionExit(coA->getGO());
				}
			}
		}

		bool FunctCallbackStay(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) {

			// Call OnCollisionStay and OnTriggerStay of both objects
			void* obA = colObj0Wrap->getCollisionObject()->getUserPointer();
			void* obB = colObj1Wrap->getCollisionObject()->getUserPointer();

			// Si son entidades llamamos a sus callbacks respectivos
			if (obA != nullptr && obB != nullptr) {
				Collider* coA = static_cast<Collider*>(obA);
				Collider* coB = static_cast<Collider*>(obB);
				if (coA != nullptr && coB != nullptr) coB->onCollisionStay(coA->getGO());

				if (coB != nullptr && coA != nullptr) coB->onCollisionStay(coA->getGO());
			}

			return false;
		}

		void PhysicsManager::init(const Utilities::Vector3<float> gravity) {

			collConfig = new btDefaultCollisionConfiguration();

			collDispatcher = new btCollisionDispatcher(collConfig);

			broadPhaseInterface = new btDbvtBroadphase();
			constraintSolver = new btSequentialImpulseConstraintSolver();

			dynamicsWorld = new btDiscreteDynamicsWorld(collDispatcher, broadPhaseInterface,
				constraintSolver, collConfig);

			dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

			gContactStartedCallback = FunctCallbackEnter;
			gContactAddedCallback = FunctCallbackStay;
			gContactEndedCallback = FunctCallbackExit;

#ifdef _DEBUG
			debugDrawer = new OgreDebugDrawer(LoveEngine::Renderer::OgreRenderer::getInstance()->getSceneManager());
			debugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
			dynamicsWorld->setDebugDrawer(debugDrawer);
#endif

			checkExceptions();
		}

		void PhysicsManager::checkExceptions() {

			if (!collConfig || !collDispatcher || !broadPhaseInterface || !constraintSolver || !dynamicsWorld) {
				LoveEngine::ErrorHandling::throwError(__PROJECT_NAME__, __LINE__, __FILENAME__, "Error al inicializar Bullet Physics, alguna de las variables de configuracion del mundo tiene un valor no valido.");
			}
		}


		btDynamicsWorld* PhysicsManager::getWorld() const {

			return dynamicsWorld;
		}

		void PhysicsManager::update(float physicsFrameRate) {

			dynamicsWorld->stepSimulation(physicsFrameRate, 10);

#ifdef _DEBUG

			dynamicsWorld->debugDrawWorld();
#endif // _DEBUG
		}

		void PhysicsManager::fixedUpdate(float deltaTime) {
			dynamicsWorld->stepSimulation(deltaTime);
		}

		btRigidBody* PhysicsManager::createRB(Utilities::Vector3<float> pos_, Utilities::Vector3<float> scale_, float mass, int shape/*, int group = -1, int mask = -1*/,
			Utilities::Vector4<float> rot_) {

			//creamos el collider
			btCollisionShape* shapeBT;

			//diferentes tipos de caja de colision
			//diferentes tipos de caja de colision
			if (shape == 0) {

				shapeBT = new btBoxShape(btVector3(scale_.x, scale_.y, scale_.z));//cubo
			}
			else if (shape == 1) {
				shapeBT = new btSphereShape(btScalar(scale_.x));
			}
			else if (shape == 2) {
				shapeBT = new btStaticPlaneShape(btVector3(scale_.x, scale_.y, scale_.z), 0);
			}
			else if (shape == 3) {
				shapeBT = new btCapsuleShape(scale_.x, scale_.y);
			}
			else shapeBT = new btBoxShape(btVector3(scale_.x, scale_.y, scale_.z));//cubo

			//collisionShapes->push_back(shapeBT);

			btTransform startTransform;
			startTransform.setIdentity();

			//el rigidbody sera dinamico si su masa no es zero
			btVector3 localInertia(0, 0, 0);
			if (mass != 0.f) {
				shapeBT->calculateLocalInertia(mass, localInertia); 
			}

			startTransform.setOrigin(btVector3(pos_.x, pos_.y, pos_.z));
			btQuaternion quat;
			float x = rot_.x;
			float y = rot_.y;
			float z = rot_.z;
			
			quat.setEulerZYX(z, y, x);
			startTransform.setRotation(quat);
			btMotionState* myMotionState = new btDefaultMotionState(startTransform);

			btRigidBody* rb = new btRigidBody(mass, myMotionState, shapeBT, localInertia);

			rb->forceActivationState(DISABLE_DEACTIVATION);

			//collisionflags -->CAMBIAR MAS ADELANTE
			rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

			dynamicsWorld->addRigidBody(rb);
			bodies.push_back(rb);

			return rb;
		}

		void PhysicsManager::destroyRigidBody(btRigidBody* body) {

			auto it = contacts.begin();
			while (it != contacts.end()){
				if ((*it).first == body) it = contacts.erase(it);
				else ++it;
			}

			//dynamicsWorld->removeCollisionObject(body);
			//btMotionState* motionstate = body->getMotionState();

			//btCollisionShape* collisionshape = body->getCollisionShape();
			dynamicsWorld->removeRigidBody(body);
			if (body && body->getMotionState())
				delete body->getMotionState();
			//delete body;/*
			//delete collisionshape;
			//delete motionstate;*/
			auto i = std::begin(bodies);
			while (i != std::end(bodies)) {
				if (*i == body) break;
				++i;
			}
			if (i != std::end(bodies)) bodies.erase(i);
		}

		void PhysicsManager::destroyWorld() {

			delete collConfig; collConfig = nullptr;

			delete collDispatcher; collDispatcher = nullptr;

			delete broadPhaseInterface; broadPhaseInterface = nullptr;

			delete constraintSolver; constraintSolver = nullptr;

			delete dynamicsWorld; dynamicsWorld = nullptr;
#ifdef _DEBUG
			delete debugDrawer; debugDrawer = nullptr;

#endif // DEBUG

		}

		void PhysicsManager::destroy() {

			//remove the rigidbodies from the dynamics world and delete them

			for (int i = 0; i < bodies.size(); i++) {
				destroyRigidBody(bodies[i]);
			}

			destroyWorld();
		}

		btVector3 PhysicsManager::btConvert(const Utilities::Vector3<float>& v3) {

			return btVector3(v3.x, v3.y, v3.z);
		}

		Utilities::Vector3<float> PhysicsManager::v3Convert(const btVector3& v3) {

			return Utilities::Vector3<float>(v3.x(), v3.y(), v3.z());
		}
	}
}

