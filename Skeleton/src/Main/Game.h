#pragma once

#ifndef GAME_H
#define GAME_H
#include <Windows.h>

namespace LoveEngine {
	class Time;
}
class SceneManager;
class OgreRenderer;
class PhysicsManager;
struct Game {

	HMODULE game;
	HMODULE singleton;

	OgreRenderer* renderer;
	SceneManager* sceneManager;
	LoveEngine::Time* time;
	PhysicsManager* physics;

	void run();

	int setup();

	void quit();

	void loop();
};
#endif
