#include <Component.h>
#include <ComponentFactory.h>
#include <SingletonInfo.h>
#include <cassert>
#include <Timer.h>
#include <MouseTracker.h>
#include <Transform.h>
#include <Mesh.h>
#include <RigidBody.h>
#include <CameraComponent.h>
#include <LightComponent.h>
#include <Image.h>
#include <Animation.h>

namespace LoveEngine {
	using namespace ECS;

	namespace ComponentDefinitions {

		ComponentFactory* ComponentFactory::instance = nullptr;

		ComponentFactory* ComponentFactory::getInstance()
		{
			if (instance == nullptr) {
				instance =
					static_cast<ComponentFactory*>(
						LoveEngine::Singleton::getElement(
							LoveEngine::Singleton::positions::ComponentFactory));
			}
			return instance;
		}

		ComponentFactory::ComponentFactory()
		{
			if (instance != nullptr) {
				assert(false);
			}
			initialiseEngineComponents();
			LoveEngine::Singleton::addElement(this, LoveEngine::Singleton::positions::ComponentFactory);
		}


		void ComponentFactory::initialiseEngineComponents()
		{
			/*
			*	Aqu� se definen los componentes creados desde el propio motor para el desarrollo del juego
			*/

			registerComponent(new ComponentCreatorTemplate<Timer>("Timer"));
			registerComponent(new ComponentCreatorTemplate<MouseTracker>("MouseTracker"));
			registerComponent(new ComponentCreatorTemplate<Mesh>("Mesh"));
			registerComponent(new ComponentCreatorTemplate<RigidBody>("Rigidbody"));
			registerComponent(new ComponentCreatorTemplate<Transform>("Transform"));
			registerComponent(new ComponentCreatorTemplate<Camera>("Camera"));
			registerComponent(new ComponentCreatorTemplate<Light>("Light"));
			registerComponent(new ComponentCreatorTemplate<Image>("Image"));
			registerComponent(new ComponentCreatorTemplate<Animation>("Animation"));
		}


		ComponentFactory::~ComponentFactory()
		{
			for (auto it = components.begin(); it != components.end(); it++) {
				delete it->second;
			}

			components.clear();
		}

		void ComponentFactory::registerComponent(ComponentCreator* fact)
		{
			components.emplace(fact->componentName, fact);
		}

		Component* ComponentFactory::createComponent(std::string name)
		{
			auto elem = components.find(name);

			assert(("El componente no esta definidio", elem != components.end()));
			return elem->second->createComponent();
		}
	}
}