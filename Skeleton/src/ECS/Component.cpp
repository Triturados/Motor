#include "Component.h"
#include "GameObject.h"
#include "Scene.h"

namespace LoveEngine {
	namespace ECS {

		//Inicialización de atributos estáticos
		template<class T>
		unsigned int ComponentTemplate<T>::componentNum = 0;

		template<class T>
		size_t ComponentTemplate<T>::id = 0;

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

		GameObject* Component::createObject(std::string name)
		{
			return gameObject->createGameObject(name);
		}
	}
}
template <class T>
std::size_t std::hash<LoveEngine::ECS::ComponentTemplate<T>>::operator()(unsigned int num) const noexcept
{
	std::size_t h = std::hash<int>{}(num);
	return h ^ (h << 1);
}