#include "Timer.h"
#include <GameTime.h>
#include <GameObject.h>
#include <SceneManager.h>
#include <Scene.h>
#include <iostream>


void Timer::onTimeUp() 
{
	funct(this);
	gameObject->removeGameObject();
}

void Timer::setValue(action f, float t)
{
	funct = f;
	maxTime = t;
} 

void Timer::update()
{
	std::cout << timeLeft() << "\n";
	currentTime += LoveEngine::Time::getInstance()->deltaTime;

	if (currentTime > maxTime) {
		onTimeUp();
	}
}

void Timer::stop()
{
	onTimeUp();
}

void Timer::restart()
{
	currentTime = 0;
}

void Timer::pause()
{
	setActive(false);
}

void Timer::resume()
{
	setActive(true);
}

void Timer::loop()
{
	_loop = true;
}

void Timer::noloop()
{
	_loop = false;
}

float Timer::timeLeft()
{
	return maxTime - currentTime;
}


Timer* Timer::invoke(action funct, float time)
{
	Timer* timer = createObjectWithTimer();
	timer->setValue(funct, time);
	return timer;
}

//TODO repear
Timer* Timer::repeat(action funct, float initialcall, float interval)
{
	Timer* timer = createObjectWithTimer();
	auto f = [&](Timer* t) {
		invoke(funct, interval);
	};
	timer->setValue(f, initialcall);
	timer->loop();
	return timer;
}

#include <iostream>
Timer* Timer::deleteGameObject(GameObject* gObject, float time)
{
	Timer* timer = createObjectWithTimer();
	timer->objectToDelete = gObject;
	std::cout << gObject->name << " set to dead\n";

	auto funct = [&](Timer* t) {
		std::cout << t->objectToDelete->name << " set to dead\n";
		t->objectToDelete->removeGameObject();
	};

	timer->setValue(funct, time);
	return timer;
}

Timer* Timer::deleteComponent(Component* component, float time)
{
	Timer* timer = createObjectWithTimer();
	timer->componentToDelete = component;
	auto funct = [&](Timer* t) {
		t->componentToDelete->remove();
		t->remove();
	};
	timer->setValue(funct, time);
	return timer;
}

Timer* Timer::createObjectWithTimer()
{
	auto gO = SceneManager::getInstance()->getCurrentScene()->createGameObject("Timer object");
	auto timer = gO->addComponent<Timer>();
	return timer;
}