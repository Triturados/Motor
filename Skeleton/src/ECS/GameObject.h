#pragma once
#include <vector>
#include <string>
#include <list>

class Scene;
class Component;

//Solo se puede pasar como plantilla una clase que herede de componente
template <typename T>
concept isComponent = std::is_base_of<Component, T>::value;

class GameObject final {

	friend Scene;

public:

	GameObject(std::string name);
	~GameObject();
	std::string name;


private:

	Scene* scene;
	bool enabled = true;
	std::list<Component*> componentsList;
	
	//Lista de componentes a elimiar al final del ciclo de update
	std::list<std::list<Component*>::iterator> componentsToErase;

	void init();
	void postInit();

	void update();
	void stepPhysics();
	void preRender();

	void activated();
	void deActivated();

public:
	void print(std::string mssg, std::string file, int line);

	template <typename T>
		requires isComponent<T>
	T* addComponent() {

		T* c = new T();
		c->gameObject = this;
		c->scene = scene;

		componentsList.push_back(c);

		return c;
	}

	template <typename T>
		requires isComponent<T>
	bool hasComponent() {
		return getComponent<T>() != nullptr;
	}

	template <typename T>
		requires isComponent<T>
	void removeComponent() {

		std::list<Component*>::iterator it = componentsList.begin();
		while (it != componentsList.end()) {

			if (dynamic_cast<T*>(*it) != nullptr)
			{
				componentsToErase.push_back(it);
				return;
			}
			it++;
		}
	}

	template <typename T>
		requires isComponent<T>
	T* getComponent() {

		for (Component* comp : componentsList) {
			T* v = dynamic_cast<T*>(comp);
			if (v != nullptr) {
				return v;
			}
		}

		return nullptr;
	}

	template <typename T>
		requires isComponent<T>
	std::vector<T*> getComponents() {
		std::vector<T*> vec;
		for (Component* comp : componentsList) {
			T* v = dynamic_cast<T*>(comp);
			if (v != nullptr) {
				vec.push_back(v);
			}
		}

		return vec;
	}
};