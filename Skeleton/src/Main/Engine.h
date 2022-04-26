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

	class Engine {
	public:
		int setup();
		void loop();
		void quit();

	private:
		HMODULE game;

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

		void changeWindowTitle();

		void updateTimeValues(
			const std::chrono::steady_clock::time_point& beginFrame,
			const std::chrono::steady_clock::time_point& endFrame,
			const std::chrono::steady_clock::time_point& appStart);
	};
}
#endif
