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


		/// <summary>
		/// Calcula el número de componente que le corresponde a una clase concreta de ComponentTemplate.
		/// El número no tiene por qué ser el mismo en diferentes compilaciones, pero dentro de una misma ejecución
		/// siempre será el mismo para todas las instancias de esa clase.
		/// El número de componente solo tiene valor para generar la id, por lo que no tiene getter público.
		/// 
		/// Al ser un template, se compila una versión de esta función por cada tipo que lo llame.
		/// </summary>
		template<typename T>
		inline static unsigned int calculateComponentNum() 
		{
			static unsigned int componentNum = Component::numOfComponentClasses++;;
			return componentNum;
		};


		// Todas las clases Componentes deben heredar de esta clase, para que puedan tener IDs.
		// Esta clase usa herencia inversa (Curiously Recurring Template Pattern), por lo que las clases que heredan
		// de ella deben estar declaradas así:
		// class NombreClase: public ComponentTemplate<NombreClase>
		template <class T>
		class lovexport ComponentTemplate : public Component
		{
		private:
			friend T;

			static unsigned int componentNum;
			static size_t id;
			
			ComponentTemplate()
			{
				generateComponentID();
			}

			// Las ids se usan para comparar componentes y organizarlas en listas ordenadas
			void generateComponentID()
			{
				componentNum = calculateComponentNum<T>();
				std::hash<ComponentTemplate<T>> myComponentHash;
				ComponentTemplate<T>::id = myComponentHash(componentNum);
			}

		public:
			inline size_t getId() const { return id; };
		};

		//Inicialización de atributos estáticos
		template<class T>
		unsigned int ComponentTemplate<T>::componentNum = 0;

		template<class T>
		size_t ComponentTemplate<T>::id = 0;
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
// Un hash genera un número muy grande determinista a partir de un valor
template<class T>
struct std::hash<LoveEngine::ECS::ComponentTemplate<T>>
{
	std::size_t operator()(unsigned int num) const noexcept 
	{
		std::size_t h = std::hash<int>{}(num);
		return h ^ (h << 1);
	}
};

