#pragma once
#include <../Export.h>
#include <vector>
#include <string>

namespace LoveEngine {

	namespace Utilities {
		class StringFormatter;
	}

	namespace ECS {

		class Scene;
		class GameObject;

		// Componente interfaz, utilizada para listas polimórficas
		class lovexport Component {
			friend GameObject;

		public:
			// Indica el número de subclases de componente que existen. Necesario para calcular IDs.
			static unsigned int numOfComponentClasses;

			Component();
			virtual ~Component() {};
			GameObject* gameObject;

			virtual void receiveComponent(int, Component*) {};
			virtual void receiveGameObject(int, GameObject*) {};

			Component* sendFormattedString(std::string mssg);

			virtual void receiveString(std::string mssg) {};

			void remove(Component* comp);
			void remove(GameObject* go);
			void remove();

			void setActive(bool val);
			bool isActive();
			void swapActive();

		public:

			// Puntero a escena
			Scene* scene;

			/// Componentes desactivados no son actualizados automáticamente por el motor, 
			/// pero otras componentes pueden llamar a sus métodos.
			bool enabled = true;

			/// Lista de componentes de las que depende esta componente. Si se intenta añadir esta componente
			/// a un objeto que no tiene todas sus dependencias, se escribe un mensaje de error y no se añande.
			std::vector<Component*> dependencies;

			virtual void init() {};
			virtual void postInit() {};

			virtual void update() {};
			virtual void stepPhysics() {};

			virtual void activated() {};
			virtual void deActivated() {};

			virtual void onSceneUp() {};
			virtual void onSceneDown() {};

			virtual void receiveMessage(Utilities::StringFormatter& sf) {};

			virtual void colliding(GameObject* other) {};
			virtual void enterCollision(GameObject* other) {};
			virtual void exitCollision(GameObject* other) {};


			GameObject* createObject(std::string name);

		private:

			bool dead = false;
			std::vector<GameObject*> collisions;
		};

	}

	namespace Utilities {
		template<class T>
		class Vector4;
		template<class T>
		class Vector3;
		template<class T>
		class Vector2;
	}
}


