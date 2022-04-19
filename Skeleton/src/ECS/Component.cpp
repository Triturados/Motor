#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include "StringFormatter.h"

namespace LoveEngine {
	namespace ECS {

		//Inicialización de atributos estáticos
		unsigned int Component::numOfComponentClasses = 0;


		Component::Component()
		{
			this->scene = nullptr;
			this->gameObject = nullptr;
		}

		void Component::remove(Component* comp)
		{
			comp->gameObject->removeComponent(comp);
		}

		void Component::remove(GameObject* go)
		{
			go->removeGameObject();
		}

		void Component::remove()
		{
			gameObject->removeComponent(this);
		}

		void Component::setActive(bool val)
		{
			enabled = val;
		}

		bool Component::isActive()
		{
			return enabled;
		}

		void Component::swapActive()
		{
			enabled = !enabled;
		}

		void Component::formatString(std::string msg)
		{
			Utilities::StringFormatter sf(msg);
			receiveMessage(sf);
		}

		GameObject* Component::createObject(std::string name)
		{
			return gameObject->createGameObject(name);
		}
	}
}