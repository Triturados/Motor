#include "Scene.h"
#include "GameObject.h"

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

GameObject* Scene::createGameObject(std::string name)
{
	GameObject* gameObject = new GameObject(name);
	gObjects.push_back(gameObject);
	gameObject->scene = this;
	return gameObject;
}

Scene* SceneCreator::createScene() {
	Scene* scene = populateScene();
	push(scene);
	return scene;
}


Scene* SceneCreator::createScene(std::string name) {
	Scene* scene = new Scene(name);
	return scene;
}


GameObject* SceneCreator::createGameObject(std::string name) {
	GameObject* go = new GameObject(name);
	gObjects.push_back(go);
	return go;
}


void SceneCreator::push(Scene* scene)
{
	for (auto gO : gObjects) {
		scene->gObjects.push_back(gO);
		gO->scene = scene;
	}

	gObjects.clear();
}
