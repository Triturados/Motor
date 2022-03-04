#include <Sound.h>
#include <iostream>
#include <OgreRenderer.h>
#include <SceneManager.h>
#include <Component.h>
#include <GameObject.h>
#include <Scene.h>
#include <lua.hpp>
#include <GameTime.h>
#include <time.h>
#include "Game.h"


class ContadorFrames : public Component {

public:


	void update() override {

		if (cont == 14) {
			SceneManager::instance->changeScene(1, SceneLoad::PUSH);
		}
		std::cout << cont++ << "\n";
	}

private:
	int cont = 0;
};




class ElComponenteDeDani : public Component {


public:
	void update() override {
		std::cout << "Ivan es muy tonto sinceramente\n";
	}
};



class EscenaDeDani : public SceneCreator {


public:
	Scene* populateScene() override {
		Scene* scene = createScene("Escena Dani");
		GameObject* pepe = createGameObject("Pepe");
		pepe->addComponent<ElComponenteDeDani>();
		return scene;
	}
};



class Escenadecontar : public SceneCreator {


};



void useSystemSound()
{


	lua_State *L = luaL_newstate();

	const char* s = "a = 2 + 7";
	int r = luaL_dostring(L, s);

	if (r == LUA_OK) {
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1)) {
			float a_in_cpp = (float)lua_tonumber(L, -1);
			std::cout << "LUA LUA LUA: " << a_in_cpp << "\n";
		}
	}

	lua_close(L);
	
	
	
	SoundSystemClass sound = SoundSystemClass(); //Inicializacion 

	// Create a sample sound
	SoundClass soundSample;
	sound.createSound(&soundSample, "FMOD/Sonidos/sonido.wav",0);

	// Play the sound, with loop mode
	sound.playSound(soundSample, true);

	// Do something meanwhile...

	int a;
	std::cin >> a;

	// Release the sound
	sound.releaseSound(0);

	

	
	Game game;
	game.run();



	OgreRenderer main = OgreRenderer();
	main.exampleScene();

	while (main.update()) {};

}

void main()
{
	//sound("aaaa");
	useSystemSound();
}

