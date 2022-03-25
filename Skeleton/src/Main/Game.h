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
class ComponentFactory;

struct SceneDefinitions;

typedef SceneDefinitions* (*Funct)();
typedef void (*GameComponentDefinition)();

struct Game {

	HMODULE game;
	HMODULE singleton;

	OgreRenderer* renderer;
	SceneManager* sceneManager;
	ComponentFactory* compFactory;
	LoveEngine::Time* time;
	PhysicsManager* physics;

	void run();

	int setup();

	void quit();

	void loop();

private:

	int initialiseDLLs(Funct& func, GameComponentDefinition& gcd);

};
#endif
