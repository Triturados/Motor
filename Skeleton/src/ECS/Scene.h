#pragma once
#include <string>
#include <list>

class Renderer;
class Component;
class GameObject;
class SceneManager;
class SceneCreator;

class Scene final {

	friend SceneCreator;
	friend SceneManager;
	friend class SceneFactory;
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



//Clase para añadir cada uno de los elementos a la escena
class SceneCreator {

public:
	Scene* createScene();
protected:
	virtual Scene* populateScene() { return nullptr; };
	std::list<GameObject*> gObjects;

	Scene* createScene(std::string name);
	GameObject* createGameObject(std::string name);
private:
	void push(Scene*);
};