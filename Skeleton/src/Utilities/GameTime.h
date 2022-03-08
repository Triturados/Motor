#pragma once



class GameTime {
public:

	float deltaTime;
	float physicsTime;
	float timeSinceStart;
	float timeScale;

	unsigned long frameCount;
	float calculateFrameRate();
};