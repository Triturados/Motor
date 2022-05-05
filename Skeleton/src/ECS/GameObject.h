#pragma once
#include <vector>
#include <string>
#include <list>
#include <../Export.h>


namespace LoveEngine {
	namespace ECS {

		class Scene;
		class Component;

		//Solo se puede pasar como plantilla una clase que herede de componente
		template <typename T>
		concept isComponent = std::is_base_of<Component, T>::value;

		class lovexport GameObject final {

			friend Scene;
			friend class RigidBody;
			friend class SceneCreator;
			friend class Blueprint;

			GameObject(const  std::string& name);
			GameObject(const  std::string& name, Scene* scene);
			~GameObject();
	
		private:

			Scene* scene;
			bool enabled = true;
			bool dead = false;
			std::list<Component*> componentsList;

			//Lista de componentes a elimiar al final del ciclo de update
			std::list<std::list<Component*>::iterator> componentsToErase;

			void init();
			void postInit();

			void update();
			void stepPhysics();

			void activated();
			void deActivated();

			void onSceneUp();
			void onSceneDown();

		public:
			std::string name;
			
			void colliding(GameObject* other);
			void enterCollision(GameObject* other);
			void exitCollision(GameObject* other);

			Scene* getCurrentScene();


			template <typename T>
			requires isComponent<T>
				T* addComponent(bool init = false) {

				T* c = new T();
				c->gameObject = this;
				c->scene = scene;

				if (init) {
					c->init();
					c->postInit();
				}
				componentsList.push_back(c);
				return c;
			}

			Component* createComponent(const  std::string& comp);

			template <typename T>
			requires isComponent<T>
				bool hasComponent() {
				return getComponent<T>() != nullptr;
			}

			template <typename T>
			requires isComponent<T>
				void removeComponent() {

				std::list<Component*>::iterator it = componentsList.begin();
				while (it != componentsList.end()) {

					if (dynamic_cast<T*>(*it) != nullptr)
					{
						componentsToErase.push_back(it);
						return;
					}
					it++;
				}
			}

			void removeComponent(Component* comp) {
				std::list<Component*>::iterator it = componentsList.begin();
				while (it != componentsList.end()) {

					if (*it == comp)
					{
						componentsToErase.push_back(it);
						return;
					}
					it++;
				}
			}


			template <typename T>
			requires isComponent<T>
				T* getComponent() {

				for (Component* comp : componentsList) {
					T* v = dynamic_cast<T*>(comp);
					if (v != nullptr) {
						return v;
					}
				}

				return nullptr;
			}

			template <typename T>
			requires isComponent<T>
				std::vector<T*> getComponents() {
				std::vector<T*> vec;
				for (Component* comp : componentsList) {
					T* v = dynamic_cast<T*>(comp);
					if (v != nullptr) {
						vec.push_back(v);
					}
				}

				return vec;
			}

			void activate(bool value);
			void removeGameObject();
			bool isEnabled();

			GameObject* createEmptyGameObject(const  std::string& name);

			void sendMessage(const  std::string& mssg);
		};
	}
}