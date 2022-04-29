#include "MouseTracker.h"
#include <Input.h>
#include <iostream>
#include <Vector2.h>
#include <GameObject.h>
#include <CameraComponent.h>
#include <GameTime.h>
#include <StringFormatter.h>
#include <Utils.h>
#include "Random.h"

void LoveEngine::ECS::MouseTracker::receiveComponent(int i, Component* c)
{
	rotationSpeed = i;
	maincam = static_cast<Camera*>(c);
}

LoveEngine::ECS::MouseTracker::MouseTracker()
{
	maincam = nullptr;
	mousepos = new Utilities::Vector2<int>();
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
	input->mouseWheel();
	int randomBetween = Utilities::Random::randomBetween(0, 19292392);
	float random = Utilities::Random::random();

	if (input->mousePressed(Input::MouseState::CLICK_L)) {

		float difx = mousepos->x - newpos.x;
		float dify = mousepos->y - newpos.y;

		float dt = Time::getInstance()->deltaTime;
		float tontetiraparaquecompileelprograma = Utilities::lerp(difx, dify, Utilities::cubicEaseOut(.5f));

		if (difx != 0)
			maincam->yaw(difx * rotationSpeed * dt);
		else
			maincam->pitch(dify * rotationSpeed * dt);
	}

	*mousepos = newpos;
}
