#include "Scene.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "CameraComponent.h"

namespace LoveEngine {
	namespace ECS {

		Scene::Scene(std::string name) {
			mainCamera = nullptr;
			this->name = name;
		}

		Scene::~Scene()
		{
			for (auto gO : gObjects) {
				delete gO;
			}
			gObjects.clear();
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
			for (auto it = gObjects.begin(); it != gObjects.end(); it++) {
				GameObject* gO = *it;

				if (gO->enabled && !gO->dead)
					gO->update();
				else if (gO->dead)
					objectsToRemove.push_back(it);
			}
		}

		void Scene::removeObjects() {
			for (auto it : objectsToRemove) {
				auto gO = *it;
				gObjects.erase(it);
				delete gO;
			}
			objectsToRemove.clear();
		}

		void Scene::stepPhysics()
		{
			for (auto gO : gObjects) {
				if (gO->enabled && !gO->dead)
					gO->stepPhysics();
			}
		}


		void Scene::onSceneUp()
		{
			for (auto gO : gObjects) {
				if (gO->enabled && !gO->dead)
					gO->onSceneUp();
			}
		}

		void Scene::onSceneDown()
		{
			for (auto gO : gObjects) {
				if (gO->enabled && !gO->dead)
					gO->onSceneDown();
			}
		}

		GameObject* Scene::persistentGameObject()
		{
			return SceneManagement::SceneManager::getInstance()->persistentScene->gObjects.front();
		}


		void Scene::setName(std::string newname) {
			name = newname;
		}

		GameObject* Scene::find(std::string name)
		{
			for (auto go : gObjects) {
				if (go->name == name)
					return go;
			}
			return nullptr;
		}

		std::list<GameObject*> const& Scene::getGameObjects()
		{
			return gObjects;
		}

		GameObject* Scene::createGameObject(std::string name)
		{
			GameObject* gameObject = new GameObject(name);
			gObjects.push_back(gameObject);
			gameObject->scene = this;
			return gameObject;
		}


		void Scene::setMainCamera(Camera* cam)
		{
			mainCamera = cam;
		}

		Camera* Scene::getMainCamera()
		{
			return mainCamera;
		}
	}
}