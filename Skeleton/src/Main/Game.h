#pragma once

#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <chrono>

class lua_State;

typedef void (*GameComponentDefinition)();
namespace LoveEngine {

	class Time;
	namespace ComponentDefinitions {
		class ComponentFactory;
	}
	namespace SceneManagement {
		class SceneManager;
	}
	namespace Input {
		class InputManager;
	}
	namespace Physics {
		class PhysicsManager;
	}
	namespace Audio { 
		class SoundManager;
	}
	namespace Renderer {
		class OgreRenderer;
	}

	struct Game {

		void setup();
		void loop();
		void quit();

		void testing();

	private:
		HMODULE game;
		HMODULE singleton;

		Input::InputManager* inputManager;
		Renderer::OgreRenderer* ogreManager;
		Audio::SoundManager* soundManager;
		Physics::PhysicsManager* physicsManager;

		SceneManagement::SceneManager* sceneManager;
		ComponentDefinitions::ComponentFactory* compFactory;
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
}
#endif
