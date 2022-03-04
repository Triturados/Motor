#pragma once

class GameTime;
class SceneManager;

struct Game {

	SceneManager* sceneManager;
	GameTime* time;

	void run();


	void setup();

	void quit();

	void loop();
};
