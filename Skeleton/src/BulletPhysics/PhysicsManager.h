#pragma once
#include <../Export.h>

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class OgreDebugDrawer;
class btCollisionObject;
class btVector3;
class btCollisionShape;
template <class T> class btAlignedObjectArray;

namespace Utilities {
	template <typename T>
	class Vector3;
}

class lovexport PhysicsManager {

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

	//Variable que representa el entorno din�mico de bullet con las anteriores variables como configuraci�n
	btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

	OgreDebugDrawer* mDebugDrawer = nullptr;

	btAlignedObjectArray<btCollisionShape*>* collisionShapes;

	void destroyWorld();
	void checkCollision();

	//Errores
	void checkExceptions();

public:
	static PhysicsManager* getInstance();

	PhysicsManager();
	~PhysicsManager();

	//M�todo para inicializar el mundo de bullet con gravedad como par�metro
	void init(const Utilities::Vector3<float> gravity);


	btDiscreteDynamicsWorld* getWorld() const;

	//Crea el un rigidbody de bullet a partir de los siguientes parametros:
	//Posicion, masa e identificador (el cual determina la forma del collider)
	btRigidBody* createRB(Utilities::Vector3<float> pos, float mass, int shape, int group = -1, int mask = -1);

	//destruye un rigidbody de bullet
	void destroyRigidBody(btRigidBody* body);


	void update(float);
	void fixedUpdate(float deltaTime);

	void destroy();

	btVector3 btConvert(const Utilities::Vector3<float>& v3);
	Utilities::Vector3<float> v3Convert(const btVector3& v3);

	void bulletTest();
};
