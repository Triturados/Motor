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

		class Camera;
		class Component;
		class GameObject;
		class lovexport Scene final {

			friend GameObject;
			friend SceneManagement::SceneManager;
			friend SceneManagement::SceneFactory;

			Scene(std::string name);
		public:
			~Scene();

			std::string name;

			void init();
			void postInit();
			void update();
			void removeObjects();
			void stepPhysics();

			void onSceneUp();
			void onSceneDown();

			GameObject* persistentGameObject();
			GameObject* find(std::string name);

			void setName(std::string newname);

			std::list<GameObject*> const& getGameObjects();
			GameObject* createGameObject(std::string name = "new game object");

			void    setMainCamera(Camera*);
			Camera* getMainCamera();
		private:
			
			Camera* mainCamera;
			std::list<std::list<GameObject*>::iterator> objectsToRemove;
			std::list<GameObject*> gObjects;
		};
	}
}