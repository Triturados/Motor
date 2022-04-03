#include "MouseTracker.h"
#include <Input.h>
#include <iostream>
#include <Vector2.h>

void LoveEngine::ECS::MouseTracker::update()
{
	std::cout << "mouse position: " << Input::InputManager::getInstance()->mousePosition() << "\n";
}
