#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include "StringFormatter.h"

namespace LoveEngine {
	namespace ECS {

		//Inicializaci�n de atributos est�ticos
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


		Component* Component::sendFormattedString(const  std::string& msg)
		{
			Utilities::StringFormatter sf(msg);
			receiveMessage(sf);
			return this;
		}

		GameObject* Component::createObject(const  std::string& name)
		{
			return gameObject->createEmptyGameObject(name);
		}
	}
}