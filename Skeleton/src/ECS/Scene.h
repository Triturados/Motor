#pragma once
#include <string>
#include <list>

class Renderer;

namespace LoveEngine {

	namespace SceneManagement {
		class SceneManager;
		class SceneFactory;
	}

	namespace ECS {

		class Component;
		class GameObject;

		class Scene final {

			friend SceneManagement::SceneManager;
			friend SceneManagement::SceneFactory;
			friend GameObject;

			Scene(std::string name);
		public:
			~Scene();

			std::string name;

			void init();
			void postInit();
			void update();
			void stepPhysics();
			void render();

			void setName(std::string newname);

			GameObject* createGameObject(std::string name = "new game object");
		private:




			std::list<GameObject*> gObjects;
			std::list<Renderer*> renderers;
		};
	}
}