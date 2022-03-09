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

//#ifdef _DEBUG
//	mDebugDrawer_ = new OgreDebugDrawer(OgreContext::getInstance()->getSceneManager());
//	mDebugDrawer_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
//	dynamicsWorld->setDebugDrawer(mDebugDrawer_);
//#endif // DEBUG
}

btDiscreteDynamicsWorld* PhysicsManager::getWorld() const
{
	return dynamicsWorld;
}

void PhysicsManager::update()
{
	dynamicsWorld->stepSimulation(1.f / 60.f, 10);

	checkCollision();

#ifdef _DEBUG
	dynamicsWorld->debugDrawWorld();
#endif // _DEBUG
}

void PhysicsManager::fixedUpdate(float deltaTime)
{
	dynamicsWorld->stepSimulation(deltaTime, 10);

	checkCollision();
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

void PhysicsManager::checkCollision()
{
	
}