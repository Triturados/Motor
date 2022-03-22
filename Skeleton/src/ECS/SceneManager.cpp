#include "SceneManager.h"
#include "Scene.h"
#include <cassert>
#include <Windows.h>
#include "../Singleton/SingletonInfo.h"

SceneManager* SceneManager::getInstance()
{
	HMODULE hModule = LoadLibrary(TEXT("Singleton.dll"));

	assert(hModule != NULL);

	int idx = (int)LoveSingleton::positions::SceneManager;

	LoveSingleton::singletonOUT value = (LoveSingleton::singletonOUT)GetProcAddress(hModule, "getElement");

	assert(value != NULL);

	FreeLibrary(hModule);
	return static_cast<SceneManager*>(value(idx));
}

SceneManager::SceneManager()
{
	HMODULE hModule = LoadLibrary(TEXT("Singleton.dll"));

	assert(hModule != NULL);

	int idx = (int)LoveSingleton::positions::SceneManager;

	LoveSingleton::singletonIN value = (LoveSingleton::singletonIN)GetProcAddress(hModule, "createElement");

	assert(value != NULL);

	value(this, idx);

	sceneChangeType = SceneLoad::PUSH;

	FreeLibrary(hModule);
}

SceneManager::~SceneManager()
{
	while (!currentScene.empty()) {
		delete currentScene.top();
		currentScene.pop();
	}

	for (auto sceneTemplate : scenesTemplates) {
		delete sceneTemplate;
	}
	scenesTemplates.clear();
}


Scene* SceneManager::getCurrentScene() {
	if (!currentScene.empty())
		return currentScene.top();
	return nullptr;
}

int SceneManager::sceneCount() const
{
	return scenesTemplates.size();
}

int SceneManager::currentSceneIdx() const
{
	return currentIdx;
}

std::string SceneManager::currentSceneName() const
{
	return currentScene.top()->name;
}

int SceneManager::currentSceneCount() const
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

void SceneManager::defineScenesFactories(SceneFactory scenes)
{
	assert(("__Ya se han inicializado las escenas", initialised == false));
	for (auto scene : scenes) {
		scenesTemplates.push_back(scene);
	}
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

	Scene* newscene = scenesTemplates[sceneToLoad]->createScene();
	currentScene.push(newscene);
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

