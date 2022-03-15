#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include <string>


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

void Component::print(std::string mssg, int line, const char* file)
{
	gameObject->print(mssg, file, line);
}

template <class T>
std::size_t std::hash<ComponentTemplate<T>>::operator()(unsigned int num) const noexcept
{
	std::size_t h = std::hash<int>{}(num);
	return h ^ (h << 1);
}