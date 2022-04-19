#pragma once
#include <../Export.h>
#include <vector>
#include <map>

class btDefaultCollisionConfiguration;
class btDispatcher;
class btBroadphaseInterface;
class btConstraintSolver;
class btDynamicsWorld;
class btRigidBody;
class OgreDebugDrawer;
class btCollisionObject;
class btManifoldPoint;
class btVector3;
class btCollisionShape;
class btDiscreteDynamicsWorld;
template <class T> class btAlignedObjectArray;

namespace LoveEngine {

	namespace Utilities {
		template <typename T>
		class Vector3;
		template <typename T>
		class Vector4;
	}

	namespace Physics {
		class Collider;

		class lovexport PhysicsManager {
			friend class RigidBody;
		private:
			static PhysicsManager* instance_;

			//Configuracion sobre la gestion de colisiones con bullet, nosotros usaremos la configuracion por defecto
			btDefaultCollisionConfiguration* collConfig = nullptr;

			//Variable de bullet que hace de "pasador" de colisiones
			btDispatcher* collDispatcher = nullptr;

			//Variable de bullet que se usa para hacer calculos de manera eficiente para generar posibles colisiones
			btBroadphaseInterface* broadPhaseInterface = nullptr;

			//Variable de bullet que hace de solucionador de restricciones
			btConstraintSolver* constraintSolver = nullptr;

			//Variable que representa el entorno din�mico de bullet con las anteriores variables como configuraci�n
			btDynamicsWorld* dynamicsWorld = nullptr;

			std::vector<btRigidBody*> bodies;

			void destroyWorld();
			void checkCollision();
			std::map<const btCollisionObject*, std::pair<Collider*, Collider*>> contacts;
			//Errores
			void checkExceptions();


		public:
			static PhysicsManager* getInstance();

			PhysicsManager();
			~PhysicsManager();

			//M�todo para inicializar el mundo de bullet con gravedad como par�metro
			void init(const Utilities::Vector3<float> gravity);


			btDynamicsWorld* getWorld() const;

			//Crea el un rigidbody de bullet a partir de los siguientes parametros:
			//Posicion, masa e identificador (el cual determina la forma del collider)
			btRigidBody* createRB(Utilities::Vector3<float> pos_, Utilities::Vector3<float> scale_, float mass, int shape/*, int group = -1, int mask = -1*/, 
				Utilities::Vector4<float> rot_);

			//destruye un rigidbody de bullet
			void destroyRigidBody(btRigidBody* body);


			void update(float);
			void fixedUpdate(float deltaTime);

			void destroy();

			btVector3 btConvert(const Utilities::Vector3<float>& v3);
			Utilities::Vector3<float> v3Convert(const btVector3& v3);

			void bulletTest();
		};
	}
}

