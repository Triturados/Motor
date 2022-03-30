#pragma once

#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <chrono>

namespace LoveEngine {
	class Time;
	namespace ComponentDefinitions {
		class ComponentFactory;
	}
	namespace SceneManagement {
		class SceneManager;
	}
}


class OgreRenderer;
class PhysicsManager;


class Input;
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

	Input* input;
	OgreRenderer* renderer;
	LoveEngine::SceneManagement::SceneManager* sceneManager;
	LoveEngine::ComponentDefinitions::ComponentFactory* compFactory;
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

	void updateTimeValues(
		const std::chrono::steady_clock::time_point& beginFrame,
		const std::chrono::steady_clock::time_point& endFrame,
		const std::chrono::steady_clock::time_point& appStart);
};
#endif