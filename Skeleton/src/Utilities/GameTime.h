#pragma once


namespace LoveEngine {

	class Time {
		static Time* instance;
	public:
		Time();

		static Time* getInstance();

		float deltaTime;
		float physicsTime;
		float timeSinceStart;
		float timeScale;

		unsigned long frameCount;
		float calculateFrameRate();
	};

}