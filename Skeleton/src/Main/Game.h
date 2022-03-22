#pragma once

#ifndef GAME_H
#define GAME_H

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
#endif
