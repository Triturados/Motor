#include "PhysicsManager.h"
#include <iostream>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <GameObject.h>
#include <OgreRenderer.h>
#include <Error_handling.h>
#include <SingletonInfo.h>
#include "Vector3.h"
#include "DebugDrawer.h"
#include "Collider.h"
#include "RigidBody.h"

inline bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap,
	int partId1, int index1)
{
	std::cout << "colisione" << std::endl;
	return false;
}

inline void callFinish(btPersistentManifold* const& manifold) {
	manifold->getBody0();
	std::cout << "salgoCollision" << std::endl;
}

inline void callStart(btPersistentManifold* const& manifold) {
	std::cout << "entroCollision" << std::endl;
}


namespace LoveEngine {
	namespace Physics {
		PhysicsManager* PhysicsManager::instance_ = nullptr;

		PhysicsManager* PhysicsManager::getInstance() {

			if (instance_ == nullptr) {
				instance_ = static_cast<PhysicsManager*>(
					LoveEngine::Singleton::getElement(LoveEngine::Singleton::positions::Physics));
			}
			return instance_;
		}

		PhysicsManager::PhysicsManager() {

			if (instance_ != nullptr) {
				assert("No se ha podido crear la instancia del PhysicsManager.", false);
			}

			init(Utilities::Vector3<float>(0, -10, 0));

			PhysicsManager::instance_ = this;
			LoveEngine::Singleton::addElement(this, LoveEngine::Singleton::positions::Physics);
		}

		PhysicsManager::~PhysicsManager() {

			destroy();
		}

		void PhysicsManager::checkCollision() {

			std::map<const btCollisionObject*, std::pair< Collider*, Collider*>> newContacts;
			if (dynamicsWorld == nullptr) return;
			int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();

			for (int i = 0; i < numManifolds; i++) {
				btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
				const btCollisionObject* obA = contactManifold->getBody0();
				const btCollisionObject* obB = contactManifold->getBody1();
				/*Check all contacts points*/

				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++) {
					btManifoldPoint& pt = contactManifold->getContactPoint(j);
					if (pt.getDistance() < 0.f)
					{
						Collider* coA = static_cast<Collider*>(obA->getUserPointer());
						Collider* coB = static_cast<Collider*>(obB->getUserPointer());

						if (newContacts.find(obA) == newContacts.end())
						{
							newContacts[obA] = { coA,coB };
							newContacts[obB] = { coB,coA };
						}

					}
				}
			}

			/* Check for added contacts ... */
			std::map<const btCollisionObject*, std::pair< Collider*, Collider*>>::iterator it;

			if (!newContacts.empty())
			{
				for (it = newContacts.begin(); it != newContacts.end(); it++)
				{
					if (contacts.find((*it).first) == contacts.end())
					{
						(*it).second.first->onCollisionEnter((*it).second.second->getGO());
					}
					else
					{
						// Remove to filter no more active contacts
						(*it).second.first->onCollisionStay((*it).second.second->getGO());
						contacts.erase((*it).first);
					}
				}
			}


			/* ... and removed contacts */
			if (!contacts.empty())
			{
				for (it = contacts.begin(); it != contacts.end(); it++)
				{
					(*it).second.first->onCollisionExit((*it).second.second->getGO());
				}
				contacts.clear();
			}

			contacts = newContacts;
		}

		void PhysicsManager::init(const Utilities::Vector3<float> gravity) {

			collConfig = new btDefaultCollisionConfiguration();

			collDispatcher = new btCollisionDispatcher(collConfig);

			broadPhaseInterface = new btDbvtBroadphase();
			constraintSolver = new btSequentialImpulseConstraintSolver();

			dynamicsWorld = new btDiscreteDynamicsWorld(collDispatcher, broadPhaseInterface,
				constraintSolver, collConfig);

			dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

			//gContactAddedCallback
			//gContactAddedCallback = callbackFunc;
			//gContactStartedCallback = callStart;
			//gContactEndedCallback = callFinish;

			collisiones = new std::vector<collisionObj>();
			//gContactEndedCallback = 
			//collisionShapes = new btAlignedObjectArray<btCollisionShape*>();

		//#ifdef _DEBUG
		//	mDebugDrawer = new OgreDebugDrawer(OgreRenderer::instance->getSceneManager());
		//	mDebugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
		//	dynamicsWorld->setDebugDrawer(mDebugDrawer);
		//#endif // DEBUG

			checkExceptions();
		}

		void PhysicsManager::checkExceptions() {

			if (!collConfig || !collDispatcher || !broadPhaseInterface || !constraintSolver || !dynamicsWorld) {
				LoveEngine::ErrorHandling::throwError(__PROJECT_NAME__, __LINE__, __FILENAME__, "Error al inicializar Bullet Physics, alguna de las variables de configuracion del mundo tiene un valor no valido.");
			}
		}

		/*bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, 
			int partId1, int index1)
		{
			return false;
		}*/

		btDynamicsWorld* PhysicsManager::getWorld() const {

			return dynamicsWorld;
		}

		void PhysicsManager::update(float physicsFrameRate) {

			//physicsFrameRate = 1 / 60;
			dynamicsWorld->stepSimulation(1.f / 60.f, 10);
			checkCollision();

#ifdef _DEBUG
			dynamicsWorld->stepSimulation(physicsFrameRate);
			//dynamicsWorld->getDebugDrawer()->drawBox(btVector3(5, 5, 5), btVector3(10, 10, 10), btVector3(1, 0, 0));

			//dynamicsWorld->debugDrawWorld();
#endif // _DEBUG
		}

		void PhysicsManager::fixedUpdate(float deltaTime) {
			//checkCollision();
			dynamicsWorld->stepSimulation(deltaTime);
		}

		btRigidBody* PhysicsManager::createRB(Utilities::Vector3<float> pos_, Utilities::Vector3<float> scale_, float mass, int shape/*, int group = -1, int mask = -1*/) {

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
				shapeBT = new btCylinderShape(btVector3(scale_.x, scale_.y, scale_.z));
			}
			else {
				shapeBT = new btConeShape(scale_.x / 2, scale_.y);
			}

			//collisionShapes->push_back(shapeBT);

			btTransform startTransform;
			startTransform.setIdentity();

			//el rigidbody sera dinamico si su masa no es zero
			btVector3 localInertia(0, 0, 0);
			if (mass != 0.f) {
				shapeBT->calculateLocalInertia(mass, localInertia);
			}

			startTransform.setOrigin(btVector3(pos_.x, pos_.y, pos_.z));
			btMotionState* myMotionState = new btDefaultMotionState(startTransform);

			//btRigidBody::btRigidBodyConstructionInfo info(mass, new btDefaultMotionState(transform), groundShape);
			btRigidBody* rb = new btRigidBody(mass, myMotionState, shapeBT, localInertia);

			rb->forceActivationState(DISABLE_DEACTIVATION);

			//collisionflags -->CAMBIAR MAS ADELANTE
			rb->setCollisionFlags(rb->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

			dynamicsWorld->addRigidBody(rb);
			collisionObj collObj;
			collObj.rb = rb;
			collisiones->push_back(collObj);
			bodies.push_back(rb); //------> BORRAR??

			return rb;
		}

		std::vector<btRigidBody*>* PhysicsManager::sendContacts(btRigidBody* btRb)
		{
			int i = 0;
			while (i < collisiones->size() - 1)
			{
				if (collisiones->at(i).rb = btRb) {
					return collisiones->at(i).contactosObj;
				}
			}
			return nullptr;
		}


		void PhysicsManager::destroyRigidBody(btRigidBody* body) {

			dynamicsWorld->removeCollisionObject(body);
			delete body->getCollisionShape();
			delete body->getMotionState();
			delete body;
			body = nullptr;
		}



		void PhysicsManager::destroyWorld() {

			delete collConfig; collConfig = nullptr;

			delete collDispatcher; collDispatcher = nullptr;

			delete broadPhaseInterface; broadPhaseInterface = nullptr;

			delete constraintSolver; constraintSolver = nullptr;

			delete mDebugDrawer; mDebugDrawer = nullptr;

			delete dynamicsWorld; dynamicsWorld = nullptr;
		}

		void PhysicsManager::destroy() {

			//remove the rigidbodies from the dynamics world and delete them

			for (int i = 0; i < bodies.size(); i++) {
				destroyRigidBody(bodies[i]);
			}

			/*for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
			{
				btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
				{
					delete body->getMotionState();
				}
				dynamicsWorld->removeCollisionObject(obj);
				delete obj;
			}*/

			//delete collision shapes
			/*for (int j = 0; j < collisionShapes->size(); j++)
			{
				btCollisionShape* shape = collisionShapes->at(j);
				collisionShapes->at(j) = 0;
				delete shape;
			}*/


			destroyWorld();
		}

		btVector3 PhysicsManager::btConvert(const Utilities::Vector3<float>& v3) {

			return btVector3(v3.x, v3.y, v3.z);
		}

		Utilities::Vector3<float> PhysicsManager::v3Convert(const btVector3& v3) {

			return Utilities::Vector3<float>(v3.x(), v3.y(), v3.z());
		}


		//Metodo temporal para probar el funcionamiento de Bullet
		void PhysicsManager::bulletTest() {

			///-----includes_end-----
			int i;
			///-----initialization_start-----

			///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
			btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

			///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
			btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

			///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
			btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

			///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
			btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

			btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

			dynamicsWorld->setGravity(btVector3(0, -10, 0));

			///-----initialization_end-----

			//keep track of the shapes, we release memory at exit.
			//make sure to re-use collision shapes among rigid bodies whenever possible!
			btAlignedObjectArray<btCollisionShape*> collisionShapes;

			///create a few basic rigid bodies

			//the ground is a cube of side 100 at position y = -56.
			//the sphere will hit it at y = -6, with center at -5
			{
				btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

				collisionShapes.push_back(groundShape);

				btTransform groundTransform;
				groundTransform.setIdentity();
				groundTransform.setOrigin(btVector3(0, -56, 0));

				btScalar mass(0.);

				//rigidbody is dynamic if and only if mass is non zero, otherwise static
				bool isDynamic = (mass != 0.f);

				btVector3 localInertia(0, 0, 0);
				if (isDynamic)
					groundShape->calculateLocalInertia(mass, localInertia);

				//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
				btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
				btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
				btRigidBody* body = new btRigidBody(rbInfo);

				//add the body to the dynamics world
				dynamicsWorld->addRigidBody(body);
			}

			{
				//create a dynamic rigidbody

				//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
				btCollisionShape* colShape = new btSphereShape(btScalar(1.));
				collisionShapes.push_back(colShape);

				/// Create Dynamic Objects
				btTransform startTransform;
				startTransform.setIdentity();

				btScalar mass(1.f);

				//rigidbody is dynamic if and only if mass is non zero, otherwise static
				bool isDynamic = (mass != 0.f);

				btVector3 localInertia(0, 0, 0);
				if (isDynamic)
					colShape->calculateLocalInertia(mass, localInertia);

				startTransform.setOrigin(btVector3(2, 10, 0));

				//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
				btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
				btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
				btRigidBody* body = new btRigidBody(rbInfo);

				dynamicsWorld->addRigidBody(body);
			}

			/// Do some simulation

			///-----stepsimulation_start-----
			for (i = 0; i < 150; i++)
			{
				dynamicsWorld->stepSimulation(1.f / 60.f, 10);

				//print positions of all objects
				for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
				{
					btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
					btRigidBody* body = btRigidBody::upcast(obj);
					btTransform trans;
					if (body && body->getMotionState())
					{
						body->getMotionState()->getWorldTransform(trans);
					}
					else
					{
						trans = obj->getWorldTransform();
					}
					printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
				}
			}

			///-----stepsimulation_end-----

			//cleanup in the reverse order of creation/initialization

			///-----cleanup_start-----

			//remove the rigidbodies from the dynamics world and delete them
			for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
			{
				btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
				{
					delete body->getMotionState();
				}
				dynamicsWorld->removeCollisionObject(obj);
				delete obj;
			}

			//delete collision shapes
			for (int j = 0; j < collisionShapes.size(); j++)
			{
				btCollisionShape* shape = collisionShapes[j];
				collisionShapes[j] = 0;
				delete shape;
			}

			//delete dynamics world
			delete dynamicsWorld;

			//delete solver
			delete solver;

			//delete broadphase
			delete overlappingPairCache;

			//delete dispatcher
			delete dispatcher;

			delete collisionConfiguration;

			//next line is optional: it will be cleared by the destructor when the array goes out of scope
			collisionShapes.clear();
		}
	}
}

