#pragma once

class GameTime;
class SceneManager;
class OgreRenderer;
class PhysicsManager;

struct Game {

	OgreRenderer* renderer;
	SceneManager* sceneManager;
	GameTime* time;
	PhysicsManager* physics;

	void run();


	void setup();

	void quit();

	void loop();
};
