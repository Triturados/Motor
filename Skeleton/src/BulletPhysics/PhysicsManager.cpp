#include <iostream>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <GameObject.h>
#include "PhysicsManager.h"
#include "Vector3.h"
#include "DebugDrawer.h"
#include <OgreRenderer.h>

PhysicsManager* PhysicsManager::instance_ = nullptr;

PhysicsManager::PhysicsManager()
{
	std::cout << "Inicializando Bullet Physics!\n";
}

PhysicsManager::~PhysicsManager()
{
	std::cout << "Destruyendo Bullet Physics!\n";
}

void PhysicsManager::checkCollision()
{
	if (dynamicsWorld == nullptr) return;
	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();

	for (int i = 0; i < numManifolds; i++) {
		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();
	}
}

PhysicsManager* PhysicsManager::getInstance()
{
	return instance_;
}

bool PhysicsManager::setUpInstance()
{
	if (instance_ == nullptr) {
		instance_ = new PhysicsManager();
		instance_->init(Utilities::Vector3<float>(0, -9.8f, 0));
		
		return true;
	}

	return false;
}

void PhysicsManager::init(const Utilities::Vector3<float> gravity)
{
	collConfig = new btDefaultCollisionConfiguration();

	collDispatcher = new btCollisionDispatcher(collConfig);

	broadPhaseInterface = new btDbvtBroadphase();
	constraintSolver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(collDispatcher, broadPhaseInterface,
		constraintSolver, collConfig);

	dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

//#ifdef _DEBUG
//	mDebugDrawer = new OgreDebugDrawer(OgreRenderer::instance->getSceneManager());
//	mDebugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
//	dynamicsWorld->setDebugDrawer(mDebugDrawer);
//#endif // DEBUG
}

btDiscreteDynamicsWorld* PhysicsManager::getWorld() const
{
	return dynamicsWorld;
}

void PhysicsManager::update(float physicsFrameRate)
{
	dynamicsWorld->stepSimulation(physicsFrameRate);


#ifdef _DEBUG
	//dynamicsWorld->getDebugDrawer()->drawBox(btVector3(5, 5, 5), btVector3(10, 10, 10), btVector3(1, 0, 0));

	dynamicsWorld->debugDrawWorld();
#endif // _DEBUG
}

void PhysicsManager::fixedUpdate(float deltaTime)
{
	dynamicsWorld->stepSimulation(deltaTime);
}

btRigidBody* PhysicsManager::createRB(Utilities::Vector3<float> pos, float mass, int shape, int group, int mask)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	btCollisionShape* groundShape;
	if (shape == 0) {
		groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

	}
	else {
		groundShape = new btSphereShape(btScalar(1.));
	}

	//collisionShapes->push_back(groundShape);

	//btRigidBody::btRigidBodyConstructionInfo info(mass, new btDefaultMotionState(transform), groundShape);
	btRigidBody* rb = new btRigidBody(mass, new btDefaultMotionState(transform), new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.))));

	rb->forceActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(rb, group, mask);

	return rb;
}
void PhysicsManager::destroyRigidBody(btRigidBody* body)
{
	dynamicsWorld->removeCollisionObject(body);
	delete body->getCollisionShape();
	delete body->getMotionState();
	delete body;
	body = nullptr;
}


void PhysicsManager::destroyWorld()
{
	delete collConfig; collConfig = nullptr;

	delete collDispatcher; collDispatcher = nullptr;

	delete broadPhaseInterface; broadPhaseInterface = nullptr;

	delete constraintSolver; constraintSolver = nullptr;

	delete mDebugDrawer; mDebugDrawer = nullptr;

	delete dynamicsWorld; dynamicsWorld = nullptr;
}

void PhysicsManager::destroy()
{
	instance_->destroyWorld();
	delete instance_;
}

btVector3 PhysicsManager::btConvert(const Utilities::Vector3<float>& v3)
{
	return btVector3(v3.x, v3.y, v3.z);
}

Utilities::Vector3<float> PhysicsManager::v3Convert(const btVector3& v3)
{
	return Utilities::Vector3<float>(v3.x(), v3.y(), v3.z());
}

void PhysicsManager::testeandoBullet() {
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