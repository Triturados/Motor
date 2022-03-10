#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include <string>


//Inicializaci�n de atributos est�ticos
template<class T>
uint ComponentTemplate<T>::componentNum = 0;

uint Component::numOfComponentClasses = 0;
Component::Component()
{

	this->scene = nullptr;
	this->gameObject = nullptr;
}

void Component::print(std::string mssg, int line, const char* file)
{
	gameObject->print(mssg, file, line);
}

