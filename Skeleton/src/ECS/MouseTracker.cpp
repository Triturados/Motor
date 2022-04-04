#include "MouseTracker.h"
#include <Input.h>
#include <iostream>
#include <Vector2.h>
#include <GameObject.h>
#include <CameraComponent.h>
#include <GameTime.h>

LoveEngine::ECS::MouseTracker::MouseTracker()
{
	maincam = nullptr;
	mousepos = new Utilities::Vector2();
	rotationSpeed = 5;
}

LoveEngine::ECS::MouseTracker::~MouseTracker()
{
	delete mousepos;
}

void LoveEngine::ECS::MouseTracker::init()
{
	maincam = gameObject->getComponent<Camera>();
}

void LoveEngine::ECS::MouseTracker::update()
{
	auto input = Input::InputManager::getInstance();
	Utilities::Vector2 newpos = input->mousePosition();

	if (input->mousePressed(Input::MouseState::CLICK_L)) {

		float difx = mousepos->x - newpos.x;
		float dify = mousepos->y - newpos.y;

		float dt = Time::getInstance()->deltaTime;
		if (difx != 0)
			maincam->yaw(difx * rotationSpeed * dt);
		else
			maincam->pitch(dify * rotationSpeed * dt);
	}

	*mousepos = newpos;
}

void LoveEngine::ECS::MouseTracker::receiveValues(int, float f, Component* c, GameObject*)
{
	rotationSpeed = f;
	maincam = static_cast<Camera*>(c);
}
