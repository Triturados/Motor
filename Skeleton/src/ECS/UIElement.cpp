#include "UIElement.h"
#include <StringFormatter.h>

LoveEngine::ECS::UIElement::UIElement()
{
	position = Utilities::Vector3<int>();
	dimensions = Utilities::Vector2<int>();
}


LoveEngine::ECS::UIElement::~UIElement()
{

}


LoveEngine::Utilities::Vector2<int> LoveEngine::ECS::UIElement::getSize()
{
	return dimensions;
}

void LoveEngine::ECS::UIElement::setSize(LoveEngine::Utilities::Vector2<int> s)
{
	dimensions = s;
	onResize();
}

LoveEngine::Utilities::Vector3<int> LoveEngine::ECS::UIElement::getPosition()
{
	return position;
}

void LoveEngine::ECS::UIElement::setPosition(LoveEngine::Utilities::Vector3<int> p)
{
	position = p;
	onMove();
}

void LoveEngine::ECS::UIElement::receiveMessage(LoveEngine::Utilities::StringFormatter& sf)
{
	sf.tryGetInt("width", dimensions.x);
	sf.tryGetInt("height", dimensions.y);

	sf.tryGetInt("posX", position.x);
	sf.tryGetInt("posY", position.y);
	sf.tryGetInt("posZ", position.z);
}

