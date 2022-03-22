#include <Sound.h>
#include <iostream>
#include <OgreRenderer.h>
#include <SceneManager.h>
#include <Component.h>
#include <GameObject.h>
#include <Scene.h>
#include <PhysicsManager.h>
#include <Vector3.h>
#include <lua.hpp>
#include <GameTime.h>
#include <time.h>
#include "Game.h"
#include <Input.h>
#include <Windows.h>

//LUABRIDGE
extern "C" {
#include <Lua.5.2.0/src/lua.h>
#include <Lua.5.2.0/src/lualib.h>
#include <Lua.5.2.0/src/lauxlib.h>
}


#include <memory>

#include <LuaBridge/LuaBridge.h>
#undef main

//Ejemplo Componente
class ContadorFrames : public ComponentTemplate<ContadorFrames> {
public:


	void update() override {

		if (cont == 14) {
			SceneManager::getInstance()->changeScene(1, SceneLoad::PUSH);
		}
		std::cout << cont++ << "\n";
	}

private:
	int cont = 0;
};

//Ejemplo Componente
class ElComponenteDeDani : public ComponentTemplate<ElComponenteDeDani> {
public:
	void update() override {
		std::cout << "Ivan es muy tonto sinceramente\n";
	}
};

//Ejemplo Componente con Input
class ComponenteTestInput : public Component {


public:
	void update() override {
		if (Input::getInstance()->isKeyPressed(InputKeys::A))
			std::cout << "Se ha pulsado la tecla A\n";
	}
};

//Ejemplo Escena
class EscenaDeDani : public SceneCreator {


public:
	Scene* populateScene() override {
		Scene* scene = createScene("Escena Dani");
		GameObject* pepe = createGameObject("Pepe");
		pepe->addComponent<ElComponenteDeDani>();
		return scene;
	}
};

//Ejemplo Escena
class Escenadecontar : public SceneCreator {


};


void probandoInput() {


	Input::init();
	Input::initSDLWindowTest();
	Input* input = Input::getInstance();

	while (true) {
		input->handleInput();

	}
}

void probandoFMOD() {
	//FMOD
	SoundSystemClass sound = SoundSystemClass(); //Inicializacion 

	// Create a sample sound
	FMOD::SoundClass soundSample;
	sound.createSound(&soundSample, "./FMOD/Sonidos/sonido.wav", 0);

	// Play the sound, with loop mode
	sound.playSound(soundSample, 0, true);

	// Do something meanwhile...
	int a;
	std::cin >> a;

	// Release the sound
	sound.releaseSound(0);
}

void probandoLUA() {
	lua_State* L = luaL_newstate();

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
}


struct SceneDefinitions {
	std::vector<SceneCreator*> escenas;
	void scenesDefinitions();
};


typedef SceneDefinitions*(*Funct)();

int probandoECScutreParaVerSiRealmenteFuncionaElEnlazadoDinamico() {
	HMODULE hModule = LoadLibrary(TEXT("./Game.dll"));
	HMODULE singletons = LoadLibrary(TEXT("Singleton.dll"));


	if (singletons == NULL) {
		std::cout << "No se encontró la biblioteca de singletons";
		return 1;
	}

	if (hModule == NULL) {
		std::cout << "No se encontró el juego\n";
		return 1;
	}

	Funct escena = (Funct)GetProcAddress(hModule, "quierounaescena");

	if (escena == NULL) {
		std::cout << "No se encontró inicio del juego\n";
		return 1;
	}

	const int numFrames = 60;

	SceneDefinitions* creator = escena();
	
	SceneManager* manager = new SceneManager();
	manager->defineScenesFactories(creator->escenas);
	manager->initiliseScenes();

	for (int i = 0; i < 60; i++) {
		Scene* scene = manager->getCurrentScene();

		if (scene == nullptr)
			break;

		scene->update();

		manager->checkChange();
	}

	FreeLibrary(hModule);
	FreeLibrary(singletons);
	delete manager;

	return 0;
}

void LuaBridge() {
	// create a lua state
	lua_State* luastate = luaL_newstate();

	// load standard libs
	luaL_openlibs(luastate);

	// load some code from lua file
	int scriptloadstatus = luaL_dofile(luastate, "LUABRIDGE/Example.lua");

	// call function defined in lua script
	luabridge::LuaRef addanddouble = luabridge::getGlobal(luastate, "addAndDouble");

	int x = addanddouble(15, 12);

	std::cout << "[evaluate lua] (15 + 12) * 2 = " << x << std::endl;

}

//Pruebas de proyectos
void probandoCosas()
{
	int a;
	std::cout << "Pulsa los siguientes botones para probar cada proyecto:\n";
	std::cout << "0 - LUA\n";
	std::cout << "1 - Input\n";
	std::cout << "2 - OGRE\n";
	std::cout << "3 - FMOD\n";
	std::cout << "4 - Bullet\n";
	std::cout << "5 - LuaBridge\n";
	std::cout << "6 - ECS cutre\n";
	std::cin >> a;

	switch (a)
	{
	case 0: probandoLUA(); break;
	case 1: probandoInput(); break;
	case 2:
		Game game;
		game.run(); break;
	case 3: probandoFMOD(); break;
	case 4: PhysicsManager::getInstance()->testeandoBullet(); break;
	case 5: LuaBridge(); break;
	case 6:probandoECScutreParaVerSiRealmenteFuncionaElEnlazadoDinamico(); break;
	default:
		break;
	}

	std::cout << "Escribe algo para salir.\n";
	std::cin >> a;
}

void main()
{
	probandoCosas();
}

