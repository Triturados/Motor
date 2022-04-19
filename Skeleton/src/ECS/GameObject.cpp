#include "Component.h"
#include "GameObject.h"
#include <Scene.h>
#include <ComponentFactory.h>
#include <iostream>


namespace LoveEngine {
	namespace ECS {

		GameObject::GameObject(std::string name)
		{
			this->name = name;
		}

		GameObject::GameObject(std::string name, Scene* scn)
		{
			this->name = name;
			scene = scn;
			scene->gObjects.push_back(this);
		}


		GameObject::~GameObject()
		{
			for (auto& comp : componentsList) {
				delete comp;
				comp = nullptr;
			}
			componentsList.clear();
		}


		Component* GameObject::createComponent(std::string compname)
		{
			Component* comp = LoveEngine::ComponentDefinitions::ComponentFactory::getInstance()->createComponent(compname);

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

		void GameObject::onSceneUp() {
			for (Component* comp : componentsList) {
				comp->onSceneUp();
			}
		}

		void GameObject::onSceneDown() {
			for (Component* comp : componentsList) {
				comp->onSceneDown();
			}
		}

		void GameObject::colliding(GameObject* other)
		{
			for (Component* comp : componentsList) {
				comp->colliding(other);
			}
		}

		void GameObject::enterCollision(GameObject* other)
		{
			for (Component* comp : componentsList) {
				comp->enterCollision(other);
			}
		}

		void GameObject::exitCollision(GameObject* other)
		{
			for (Component* comp : componentsList) {
				comp->exitCollision(other);
			}
		}

		Scene* GameObject::getCurrentScene()
		{
			return scene;
		}

		GameObject* GameObject::createGameObject(std::string name)
		{
			auto go = scene->createGameObject(name);
			go->init();
			go->postInit();
			return go;
		}

		void GameObject::sendMessage(std::string message) {
			for (auto comp : componentsList) {
				comp->formatString(message);
			}
		}
	}
}