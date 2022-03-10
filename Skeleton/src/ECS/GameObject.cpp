#include <iostream>
#include "Component.h"
#include "GameObject.h"


GameObject::GameObject(std::string name)
{
	this->name = name;
}

GameObject::~GameObject()
{
	for (auto& comp : componentsList) {
		delete comp;
		comp = nullptr;
	}
	componentsList.clear();
}

void GameObject::print(std::string mssg, std::string file, int line)
{
	if (file.length() > 0) {

		std::cout << "File: " << file << "\n";
	}
	if (line >= 0)
	{
		std::cout << "Line: " << line << " ";
	}

	std::cout << name << ": " << mssg << "\n";
}

void GameObject::init()
{
	for (Component* comp : componentsList) {
		comp->init();
	}
}

void GameObject::postInit()
{
	for (Component* comp : componentsList) {
		comp->postInit();
	}
}



void GameObject::update()
{
	for (Component* comp : componentsList) {
		if (comp->enabled)
			comp->update();
	}

	for (auto it : componentsToErase) {
		delete* it;
		componentsList.erase(it);
	}
	componentsToErase.clear();
}

void GameObject::stepPhysics()
{
	for (Component* comp : componentsList) {
		if (comp->enabled)
			comp->stepPhysics();
	}
}

void GameObject::preRender()
{
	for (Component* comp : componentsList) {
		if (comp->enabled)
			comp->preRender();
	}
}

void GameObject::activated()
{
	for (Component* comp : componentsList) {
		if (comp->enabled)
			comp->activated();
	}
}

void GameObject::deActivated()
{
	for (Component* comp : componentsList) {
		if (comp->enabled)
			comp->deActivated();
	}
}
