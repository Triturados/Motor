#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include <string>

Component::Component()
{

	this->scene = nullptr;
	this->gameObject = nullptr;
}

void Component::print(std::string mssg, int line, const char* file)
{
	gameObject->print(mssg, file, line);
}

