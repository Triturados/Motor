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


class lua_State;

typedef void (*GameComponentDefinition)();

struct Game {
	void run();

	int setup();

	void quit();

	void loop();

	void testing();

private:
	HMODULE game;
	HMODULE singleton;

	OgreRenderer* renderer;
	SceneManager* sceneManager;
	ComponentFactory* compFactory;
	LoveEngine::Time* time;
	PhysicsManager* physics;
	lua_State* luastate;
	//Métodos de testing de funcionamiento de librerías
	void sdlinput();
	void fmod();
	void lua();
	void luabridge();

	int initialiseDLLs(GameComponentDefinition& gcd);
	int initialiseSceneCreator();
};
#endif