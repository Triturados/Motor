#pragma once

#include <map>
#include <string>
#include <typeinfo>
class Component;
class ComponentCreator;

class ComponentFactory {

private:
	static ComponentFactory* instance;

	std::map<std::string, ComponentCreator*> components;

public:

	static ComponentFactory* getInstance();
	ComponentFactory();
	~ComponentFactory();

	void registerComponent(ComponentCreator* fact);

	Component* createComponent(std::string name);
};


class ComponentCreator {

public:
	std::string componentName;
	ComponentCreator(std::string name) {
		componentName = name;
	}

	virtual Component* CreateComponent() {
		return nullptr;
	};
};
