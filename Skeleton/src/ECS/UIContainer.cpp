#include "UIContainer.h"

void LoveEngine::ECS::UIContainer::onMove()
{
	for (auto it = uiElements.begin(); it != uiElements.end();) {

		UIElement* element = it->element;

		//Comprobar que el elemento sigue teniendo el mismo padre contenedor
		if (element->getContainer() != this) {
			it = uiElements.erase(it);
			continue;
		}

		element->setPosition(it->localPosition + position);

		it++;
	}
}

void LoveEngine::ECS::UIContainer::onResize()
{
	for (auto it = uiElements.begin(); it != uiElements.end();) {

		UIElement* element = it->element;

		//Comprobar que el elemento sigue teniendo el mismo padre contenedor
		if (element->getContainer() != this) {
			it = uiElements.erase(it);
			continue;
		}

		Utilities::Vector2<int> newdimensions(dimensions.x + it->localDimensions.x, dimensions.y + it->localDimensions.y);
		element->setSize(newdimensions);

		it++;
	}
}

void LoveEngine::ECS::UIContainer::addElement(UIElement* element)
{
	UIChild child = { element, element->getPosition(), element->getSize() };
	uiElements.push_back(child);
}

void LoveEngine::ECS::UIContainer::receiveComponent(int, Component* c)
{
	addElement(static_cast<UIElement*>(c));
}
