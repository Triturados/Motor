#include "GameTime.h"
#include <Windows.h>
#include <cassert>
#include <SingletonInfo.h>


namespace LoveEngine {

	Time* Time::instance = nullptr;

	Time::Time() {
		deltaTime = physicsTime = timeSinceStart = timeScale = unscaledTime = frameCount = 1;
		deltaTime = 1 / 60.0f;
		if (instance != nullptr) {
			assert(false);
		}

		Time::instance = this;

		//Singleton::addElement(this, Singleton::positions::Time);
	}

	Time* Time::getInstance() {
		return instance;
	}


	float Time::calculateFrameRate() {
		return frameCount / timeSinceStart * 1000;
	}

	
}