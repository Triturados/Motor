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
	for (auto gO : gObjects) {
		if (gO->enabled)
			gO->update();
	}
}


void Scene::stepPhysics()
{
	for (auto gO : gObjects) {
		if (gO->enabled)
			gO->stepPhysics();
	}
}


void Scene::render()
{
	//for (auto rend : renderers)
	//	rend->update();
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
	}

	gObjects.clear();
}
