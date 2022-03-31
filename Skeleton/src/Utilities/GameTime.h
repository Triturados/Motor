#pragma once
#include <functional>
#include <../Export.h>
class Component;
class GameObject;

namespace LoveEngine {

	class lovexport Time {
		static Time* instance;
	public:
		Time();

		static Time* getInstance();

		float deltaTime;
		float unscaledTime;
		float physicsTime;
		float timeSinceStart;
		float timeScale;
		unsigned long frameCount;
		float calculateFrameRate();
	};

}