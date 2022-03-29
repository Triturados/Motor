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
class SoundManager;

struct SceneDefinitions;

typedef SceneDefinitions* (*Funct)();
typedef void (*GameComponentDefinition)();

struct Game {

	HMODULE game;
	HMODULE singleton;

	OgreRenderer* ogreManager;;
	SceneManager* sceneManager;
	PhysicsManager* physicsManager;
	SoundManager* soundManager;

	ComponentFactory* compFactory;
	LoveEngine::Time* time;
	

	void setup();
	void loop();
	void quit();

	void testing();

private:

	//Métodos de testing de funcionamiento de librerías
	void sdlinput();
	void fmod();
	void lua();
	void luabridge();

	int initialiseDLLs(Funct& func, GameComponentDefinition& gcd);
};
#endif