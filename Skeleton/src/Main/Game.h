#pragma once

class GameTime;
class SceneManager;
class OgreRenderer;

struct Game {

	OgreRenderer* renderer;
	SceneManager* sceneManager;
	GameTime* time;

	void run();


	void setup();

	void quit();

	void loop();
};
