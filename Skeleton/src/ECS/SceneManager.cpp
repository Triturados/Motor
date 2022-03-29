#include "SceneManager.h"
#include "Scene.h"
#include <cassert>
#include <Windows.h>
#include <SingletonInfo.h>
#include <iostream>
#include <SceneFactory.h>

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

	sceneFactory = new SceneFactory();

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


Scene* SceneManager::getCurrentScene() {
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

void SceneManager::checkChange()
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
	Scene* sceneToErase = currentScene.top();
	currentScene.pop();

	delete sceneToErase;
}

void SceneManager::createScene()
{
	assert(("__La escena a crear no es valida__", sceneToLoad >= 0 && sceneToLoad < sceneCount()));

	//Scene* newscene = scenesTemplates[sceneToLoad]->createScene();
	Scene* newscene = new Scene("new scene");
	sceneFactory->creator(newscene, sceneToLoad);
	currentScene.push(newscene);

	newscene->init();
	newscene->postInit();
}

void SceneManager::manageScene()
{
	switch (sceneChangeType)
	{
	case SceneLoad::CLEAR: {
		while (!currentScene.empty()) {
			eraseTopScene();
		}
		createScene();
	}

	case SceneLoad::PUSH: {
		createScene();
	}

	case SceneLoad::POP: {
		eraseTopScene();
	}

	case SceneLoad::SWAP: {
		eraseTopScene();
		createScene();
	}
	default:
		break;
	}
}
	

