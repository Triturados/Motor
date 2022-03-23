#include "GameTime.h"
#include <Windows.h>
#include <cassert>
#include "../Singleton/SingletonInfo.h"

namespace LoveEngine {

	Time* Time::instance = nullptr;

	Time::Time() {

		deltaTime = physicsTime = timeSinceStart = timeScale = frameCount = 0;

		if (instance != nullptr) {
			assert(false);
		}

		Time::instance = this;

		HMODULE hModule = LoadLibrary(TEXT("Singleton.dll"));

		assert(hModule != NULL);

		int idx = (int)LoveSingleton::positions::Time;

		LoveSingleton::singletonIN value = (LoveSingleton::singletonIN)GetProcAddress(hModule, "createElement");

		assert(value != NULL);

		value(this, idx);

		FreeLibrary(hModule);
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