#include "Scene.h"
#include "GameObject.h"

namespace LoveEngine {
	namespace ECS {

		Scene::Scene(std::string name) {
			this->name = name;
		}

		Scene::~Scene()
		{
			for (auto gO : gObjects) {
				delete gO;
			}
			gObjects.clear();
			renderers.clear();
		}

		void Scene::init()
		{
			for (auto gO : gObjects) {
				gO->init();
			}
		}

		void Scene::postInit()
		{
			for (auto gO : gObjects) {
				gO->postInit();
			}
		}

		void Scene::update()
		{
			std::list<std::list<GameObject*>::iterator> objectsToRemove;

			for (auto it = gObjects.begin(); it != gObjects.end(); it++) {
				GameObject* gO = *it;

				if (gO->enabled && !gO->dead)
					gO->update();
				else if (gO->dead)
					objectsToRemove.push_back(it);
			}


			for (auto it : objectsToRemove) {
				auto gO = *it;
				gObjects.erase(it);
				delete gO;
			}
		}


		void Scene::stepPhysics()
		{
			for (auto gO : gObjects) {
				if (gO->enabled && !gO->dead)
					gO->stepPhysics();
			}
		}


		void Scene::render()
		{
			//for (auto rend : renderers)
			//	rend->update();
		}

		void Scene::setName(std::string newname) {
			name = newname;
		}

		GameObject* Scene::createGameObject(std::string name)
		{
			GameObject* gameObject = new GameObject(name);
			gObjects.push_back(gameObject);
			gameObject->scene = this;
			return gameObject;
		}

	}
}