#include "Component.h"
#include "GameObject.h"
#include <ComponentFactory.h>

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


Component* GameObject::addComponent(std::string compname)
{
	Component* comp = ComponentFactory::getInstance()->createComponent(compname);

	comp->gameObject = this;
	comp->scene = scene;
	componentsList.push_back(comp);

	return comp;
}

void GameObject::activate(bool value)
{
	enabled = value;
}

void GameObject::removeGameObject()
{
	dead = true;
}

void GameObject::removeGameObject(GameObject* gO)
{
	gO->removeGameObject();
}

void GameObject::canvelRemove()
{
	dead = false;
}


bool GameObject::isEnabled()
{
	return enabled;
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
