#include "MouseTracker.h"
#include <Input.h>
#include <iostream>

void LoveEngine::ECS::MouseTracker::update()
{
	if (LoveEngine::Input::InputManager::getInstance()->isKeyPressed(
	LoveEngine::Input::InputKeys::A)) {
		std::cout << "Se ha pulsado la tecla A\n";
	}
}
