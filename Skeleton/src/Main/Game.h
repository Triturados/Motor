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
class ComponentFactory;
class SoundManager;
class InputManager;


class Input;
class lua_State;

typedef void (*GameComponentDefinition)();

struct Game {
	void run();

	int setup();

	void quit();

	void setup();
	void loop();
	void quit();

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
	//M�todos de testing de funcionamiento de librer�as
	void sdlinput();
	void fmod();
	void lua();
	void luabridge();
	void ogre();
	void bullet();

	int initialiseDLLs(GameComponentDefinition& gcd);
	int initialiseSceneCreator();

	void updateTimeValues(
		const std::chrono::steady_clock::time_point& beginFrame,
		const std::chrono::steady_clock::time_point& endFrame,
		const std::chrono::steady_clock::time_point& appStart);
};
#endif
