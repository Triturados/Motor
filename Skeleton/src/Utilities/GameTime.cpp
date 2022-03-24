#include "GameTime.h"
#include <Windows.h>
#include <cassert>
#include <SingletonInfo.h>


namespace LoveEngine {

	Time* Time::instance = nullptr;

	Time::Time() {

		deltaTime = physicsTime = timeSinceStart = timeScale = unscaledTime = frameCount = 0;

		if (instance != nullptr) {
			assert(false);
		}

		Time::instance = this;

		Singleton::addElement(this, Singleton::positions::Time);
	}

	Time* Time::getInstance() {
		if (instance == nullptr) {
			instance = static_cast<Time*>(Singleton::getElement(Singleton::positions::Time));
		}
		return instance;
	}


	float Time::calculateFrameRate() {
		return frameCount / timeSinceStart * 1000;
	}

	
}