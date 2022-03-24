#include <Component.h>
#include <ComponentFactory.h>
#include <SingletonInfo.h>
#include <cassert>

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

	LoveEngine::Singleton::addElement(this, LoveEngine::Singleton::positions::ComponentFactory);
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
	return elem->second->CreateComponent();
}

