#include <iostream>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <GameObject.h>
#include "PhysicsManager.h"
#include "Vector3.h"
//#include "DebugDrawer.h"

PhysicsManager* PhysicsManager::instance_ = nullptr;

PhysicsManager::PhysicsManager()
{
	std::cout << "Inicializando Bullet Physics!\n";
}

PhysicsManager::~PhysicsManager()
{
	std::cout << "Destruyendo Bullet Physics!\n";
}

PhysicsManager* PhysicsManager::getInstance()
{
	return instance_;
}

bool PhysicsManager::setUpInstance()
{
	if (instance_ == nullptr) {
		instance_ = new PhysicsManager();
		instance_->init(Vector3<float>(0, -9.8f, 0));
		
		return true;
	}

	return false;
}

void PhysicsManager::init(const Vector3<float> gravity)
{
	collConfig = new btDefaultCollisionConfiguration();

	collDispatcher = new btCollisionDispatcher(collConfig);

	broadPhaseInterface = new btDbvtBroadphase();
	constraintSolver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(collDispatcher, broadPhaseInterface,
		constraintSolver, collConfig);

	dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

#ifdef _DEBUG
	mDebugDrawer_ = new OgreDebugDrawer(OgreContext::getInstance()->getSceneManager());
	mDebugDrawer_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	dynamicsWorld->setDebugDrawer(mDebugDrawer_);
#endif // DEBUG
}

btDiscreteDynamicsWorld* PhysicsManager::getWorld() const
{
	return dynamicsWorld;
}

void PhysicsManager::update()
{
	dynamicsWorld->stepSimulation(1.f / 60.f);


#ifdef _DEBUG
	//dynamicsWorld->getDebugDrawer()->drawBox(btVector3(5, 5, 5), btVector3(10, 10, 10), btVector3(1, 0, 0));

	dynamicsWorld->debugDrawWorld();
#endif // _DEBUG
}

void PhysicsManager::fixedUpdate(float deltaTime)
{
	dynamicsWorld->stepSimulation(deltaTime);
}

btRigidBody* PhysicsManager::createRB(Vector3<float> pos, float mass, int group, int mask)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

	btRigidBody::btRigidBodyConstructionInfo info(mass, new btDefaultMotionState(transform), new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)));
	btRigidBody* rb = new btRigidBody(info);

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

	delete mDebugDrawer_; mDebugDrawer_ = nullptr;

	delete dynamicsWorld; dynamicsWorld = nullptr;
}

void PhysicsManager::destroy()
{
	instance_->destroyWorld();
	delete instance_;
}

btVector3 PhysicsManager::btConvert(const Vector3<float>& v3)
{
	return btVector3();
}

Vector3<float> PhysicsManager::v3Convert(const btVector3& v3)
{
	return Vector3<float>();
}

