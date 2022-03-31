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
class SoundManager;
class InputManager;

class ComponentFactory;
class lua_State;

typedef void (*GameComponentDefinition)();

struct Game {

	void setup();
	void loop();
	void quit();

	void testing();

private:
	HMODULE game;
	HMODULE singleton;

	InputManager* inputManager;
	OgreRenderer* ogreManager;
	SoundManager* soundManager;
	PhysicsManager* physicsManager;

	LoveEngine::SceneManagement::SceneManager* sceneManager;
	LoveEngine::ComponentDefinitions::ComponentFactory* compFactory;
	LoveEngine::Time* time;
	lua_State* luastate;

	int initialiseDLLs(GameComponentDefinition& gcd);
	int initialiseSceneCreator();

	void updateTimeValues(
		const std::chrono::steady_clock::time_point& beginFrame,
		const std::chrono::steady_clock::time_point& endFrame,
		const std::chrono::steady_clock::time_point& appStart);

	//Metodos de testing de funcionamiento de librerias
	void sdlinput();
	void fmod();
	void lua();
	void luabridge();
	void ogre();
	void bullet();
};
#endif
