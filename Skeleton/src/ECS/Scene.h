#pragma once
#include <../Export.h>
#include <string>
#include <list>

namespace LoveEngine {

	namespace SceneManagement {
		class SceneManager;
		class SceneFactory;
	}

	namespace ECS {

		class Component;
		class GameObject;
		class lovexport Scene final {

			friend SceneManagement::SceneManager;
			friend SceneManagement::SceneFactory;
			friend class Engine;
			friend class Timer;
			friend GameObject;

			Scene(std::string name);
		public:
			~Scene();

			std::string name;

			void init();
			void postInit();
			void update();
			void removeObjects();
			void stepPhysics();
			void render();

			void onSceneUp();
			void onSceneDown();

			GameObject* persistentGameObject();

			void setName(std::string newname);

			GameObject* createGameObject(std::string name = "new game object");
		private:

			std::list<std::list<GameObject*>::iterator> objectsToRemove;
			std::list<GameObject*> gObjects;
		};
	}
}