#include "GameTime.h"
#include <Windows.h>
#include <cassert>
#include "../Singleton/SingletonInfo.h"

namespace LoveEngine {

	Time* Time::instance = nullptr;

	Time::Time() {

		instance = this;
		deltaTime = physicsTime = timeSinceStart = timeScale = frameCount = 0;
	}

	Time* Time::getInstance() {
		if (instance == nullptr) {
			HMODULE hModule = LoadLibrary(TEXT("Singleton.dll"));

			assert(hModule != NULL);

			int idx = (int)LoveSingleton::positions::Time;

			LoveSingleton::singletonOUT value = (LoveSingleton::singletonOUT)GetProcAddress(hModule, "getElement");

			assert(value != NULL);

			FreeLibrary(hModule);
			return static_cast<Time*>(value(idx));
		}
		return instance;
	}


	float Time::calculateFrameRate() {
		return frameCount / timeSinceStart * 1000;
	}
}