#include "SceneManager.h"
#include "Scene.h"
#include <cassert>
#include <Windows.h>
#include <SingletonInfo.h>
#include <iostream>
#include <SceneFactory.h>

namespace LoveEngine {
	namespace SceneManagement {
		SceneManager* SceneManager::instance = nullptr;

		SceneManager* SceneManager::getInstance()
		{
			if (instance == nullptr) {
				instance =
					static_cast<SceneManager*>(
						LoveEngine::Singleton::getElement(
							LoveEngine::Singleton::positions::SceneManager));
			}
			return instance;
		}

		SceneManager::SceneManager()
		{
			if (instance != nullptr) {
				assert(false);
			}
			sceneChangeType = SceneLoad::PUSH;

			sceneFactory = new SceneManagement::SceneFactory();

			LoveEngine::Singleton::addElement(this, LoveEngine::Singleton::positions::SceneManager);
		}

		SceneManager::~SceneManager()
		{
			while (!currentScene.empty()) {
				delete currentScene.top();
				currentScene.pop();
			}

			delete sceneFactory;
		}


		ECS::Scene* SceneManager::getCurrentScene() {
			if (!currentScene.empty())
				return currentScene.top();
			return nullptr;
		}

		int SceneManager::sceneCount() const
		{
			return numberOfScenes;
		}

		int SceneManager::currentSceneIdx() const
		{
			return currentIdx;
		}

		std::string SceneManager::currentSceneName() const
		{
			return currentScene.top()->name;
		}

		int SceneManager::stackedScenes() const
		{
			return currentScene.size();
		}

		void SceneManager::changeScene(int sceneIdx, SceneLoad type)
		{
			shouldChange = true;
			sceneToLoad = sceneIdx;
			sceneChangeType = type;
		}

		void SceneManager::tryChangeScene()
		{
			if (shouldChange) {
				shouldChange = false;
				manageScene();
			}
		}

		void SceneManager::initiliseScenes()
		{
			initialised = true;
			assert(("__No hay escenas para crear__", sceneCount() > 0));

			sceneToLoad = 0;
			createScene();
		}


		void SceneManager::eraseTopScene()
		{
			assert(("__Niguna escena que eliminar__", !currentScene.empty()));
			ECS::Scene* sceneToErase = currentScene.top();
			currentScene.pop();

			delete sceneToErase;
		}

		void SceneManager::createScene()
		{
			assert(("__La escena a crear no es valida__", sceneToLoad >= 0 && sceneToLoad < sceneCount()));

			//Scene* newscene = scenesTemplates[sceneToLoad]->createScene();
			ECS::Scene* newscene = new ECS::Scene("new scene");
			sceneFactory->creator(newscene, sceneToLoad);
			currentScene.push(newscene);

			newscene->init();
			newscene->postInit();
		}

		void SceneManager::manageScene()
		{
			currentScene.top()->onSceneDown();

			switch (sceneChangeType)
			{
			case SceneLoad::CLEAR: {
				while (!currentScene.empty()) {
					eraseTopScene();
				}
				createScene();
				break;
			}

			case SceneLoad::PUSH: {
				createScene();
				break;
			}

			case SceneLoad::POP: {
				eraseTopScene();
				break;
			}

			case SceneLoad::SWAP: {
				eraseTopScene();
				createScene();
				break;
			}
			case SceneLoad::EXIT: {
				while (!currentScene.empty()) {
					eraseTopScene();
				}
				return;
			}
			default:
				break;
			}

			currentScene.top()->onSceneUp();
		}

		void changeScene(int idx, SceneLoad scenechangetype) {
			SceneManagement::SceneManager::getInstance()->changeScene(idx, scenechangetype);
		}
		void changeSceneByIdx(int idx, int type) {
			assert(type >= 0 && type < 5);
			SceneManagement::SceneManager::getInstance()->changeScene(idx, (SceneLoad)type);
		}
	}
}