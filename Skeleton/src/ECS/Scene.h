#pragma once
#include <string>
#include <list>

class Renderer;
class Component;
class GameObject;

namespace LoveEngine {
	namespace SceneManagement {
		class SceneManager;
	}
}

class Scene final {

	friend LoveEngine::SceneManagement::SceneManager;
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

