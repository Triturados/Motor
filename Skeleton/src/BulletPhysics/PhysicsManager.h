#pragma once

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class OgreDebugDrawer;
class btCollisionObject;

//Clase placeholder hasta integrar utilities
template <typename T>
class Vector3;

class PhysicsManager {

private:
	static PhysicsManager* instance_;

	//Configuracion sobre la gestion de colisiones con bullet, nosotros usaremos la configuracion por defecto
	btDefaultCollisionConfiguration* collConfig = nullptr;

	//Variable de bullet que hace de "pasador" de colisiones
	btCollisionDispatcher* collDispatcher = nullptr;

	//Variable de bullet que se usa para hacer calculos de manera eficiente para generar posibles colisiones
	btBroadphaseInterface* broadPhaseInterface = nullptr;

	//Variable de bullet que hace de solucionador de restricciones 
	btSequentialImpulseConstraintSolver* constraintSolver = nullptr;

	//Variable de bullet a la que se le pasa todas las variables anteriores como configuracion de la fisica
	btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

	OgreDebugDrawer* mDebugDrawer_ = nullptr;

	PhysicsManager();
	virtual ~PhysicsManager();

	void checkCollision();

public:
	static PhysicsManager* getInstance();
	static bool setUpInstance();

	//Método para inicializar el mundo de bullet con gravedad como parámetro
	void init(const Vector3<float> gravity);

	btDiscreteDynamicsWorld* getWorld() const;

	void update();
	void fixedUpdate(float deltaTime);

	void destroyWorld();
	static void destroy();
};
