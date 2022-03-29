#include "Game.h"

#include <iostream>
#include <Scene.h>
#include <Component.h>
#include <GameObject.h>
#include <GameTime.h>
#include <ComponentFactory.h>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <time.h>
#include <SceneFactory.h>

#include <PhysicsManager.h>
#include <OgreRenderer.h>
#include <SceneManager.h>

#include <Sound.h>
#include <Transform.h>
#include <Vector3.h>
#include <lua.hpp>
#include <Input.h>
#include <LuaBridge/LuaBridge.h>

#include <memory>


using namespace std::chrono;

struct SceneDefinitions {

	std::vector<SceneCreator*> escenas;
	void scenesDefinitions();
};

void Game::run()
{
	if (setup() == 0) {
		loop();
		quit();
	}
}

int Game::setup()
{
	Funct escena;
	GameComponentDefinition gameComponentDefinitions;

	if(initialiseDLLs(escena, gameComponentDefinitions)){
		return 1;
	}


	time = new LoveEngine::Time();
	sceneManager = new SceneManager();
	compFactory = new ComponentFactory();

	gameComponentDefinitions();
	//SceneDefinitions* creator = escena();

	//sceneManager->defineScenesFactories(creator->escenas);

	initialiseSceneCreator();

	sceneManager->initiliseScenes();

	renderer = new OgreRenderer();
	Input::init();
	renderer->exampleScene();

	PhysicsManager::setUpInstance();
	physics = PhysicsManager::getInstance();

	//delete creator;
	return 0;
}


void Game::loop()
{
	const float numIterations = 360;

	const float updateFrameRate = 60;
	const float physicsFrameRate = 50;

	duration uInterval = duration<double>(1.0 / updateFrameRate);
	duration pInterval = duration<double>(1.0 / physicsFrameRate);
	duration rInterval = duration<double>(1.0 / updateFrameRate);

	auto applicationStart = high_resolution_clock::now();

	auto initialTime = applicationStart;

	for (int i = 0; i < numIterations; i++) {

		Scene* currentScene = sceneManager->getCurrentScene();

		if (currentScene == nullptr) {
			break;
		}

		Input::getInstance()->handleInput();

		physics->update();

		currentScene->update();

		physics->fixedUpdate(physicsFrameRate);

		currentScene->stepPhysics();

		//currentScene->render();
		renderer->update();


		sceneManager->checkChange();

		//Calculo del tiempo
		auto currentTime = high_resolution_clock::now();

		duration<float, std::milli> timeSinceStart = currentTime - applicationStart;
		duration<double, std::milli> timeSinceLastFrame = currentTime - initialTime;
		duration<double, std::milli> sleepFor = uInterval - timeSinceLastFrame;


		time->timeSinceStart = timeSinceStart.count();
		time->deltaTime = timeSinceLastFrame.count() * 0.001;
		time->frameCount++;

		initialTime = currentTime;
		//std::this_thread::sleep_for(sleepFor);
	}

	std::cout << "Frame rate medio: " << time->calculateFrameRate() << " Esperado: " << updateFrameRate << "\n";
}

void Game::quit()
{
	FreeLibrary(game);
	FreeLibrary(singleton);

	delete sceneManager;
	delete time;
	delete renderer;
	delete compFactory;
}


void Game::testing()
{
	int a;
	std::cout << "Pulsa los siguientes botones para probar cada proyecto:\n";
	std::cout << "0 - LUA\n";
	std::cout << "1 - Input\n";
	std::cout << "2 - OGRE\n";
	std::cout << "3 - FMOD\n";
	std::cout << "4 - Bullet\n";
	std::cout << "5 - LuaBridge\n";
	std::cin >> a;

	switch (a)
	{
	case 0: lua(); break;
	case 1: sdlinput(); break;
	case 2:
		Game game;
		game.run(); break;
	case 3: fmod(); break;
	case 4: PhysicsManager::getInstance()->testeandoBullet(); break;
	case 5: luabridge(); break;
	default:
		break;
	}

	std::cout << "Escribe algo para salir.\n";
	std::cin >> a;
}


void Game::sdlinput()
{
	Input::init();
	Input::initSDLWindowTest();
	Input* input = Input::getInstance();

	while (true) input->handleInput();
}

void Game::fmod()
{
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

void Game::lua()
{
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

void Game::luabridge()
{
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



int Game::initialiseDLLs(Funct& escena, GameComponentDefinition& gcd)
{

#ifdef _DEBUG
	game = LoadLibrary(TEXT("./Game_d.dll"));
	singleton = LoadLibrary(TEXT("Singleton_d.dll"));
#else
	game = LoadLibrary(TEXT("./Game.dll"));
	singleton = LoadLibrary(TEXT("Singleton.dll"));
#endif


	if (singleton == NULL) {
		std::cout << "No se encontró la biblioteca de singletons";
		return 1;
	}

	if (game == NULL) {
		std::cout << "No se encontró el juego\n";
		return 1;
	}

	escena = (Funct)GetProcAddress(game, "quierounaescena");
	if (escena == NULL) {
		std::cout << "No se encontró inicio del juego\n";
		return 1;
	}

	gcd = (GameComponentDefinition)GetProcAddress(game, "componentDefinition");
	if (gcd == NULL) {
		std::cout << "El juego no define correctamente los componentes\n";
		return 1;
	}


	return 0;
}


int Game::initialiseSceneCreator()
{
	luastate = luaL_newstate();
	luaL_openlibs(luastate);

	luabridge::getGlobalNamespace(luastate)
		.beginClass<GameObject>("GameObject")
		//.addConstructor<void(*)(std::string)>()
		.addFunction("addComponent", &(GameObject::createComponent))
		.endClass();

	luabridge::getGlobalNamespace(luastate)
		.beginClass<Scene>("Scene")
		.addFunction("createObject", &(Scene::createGameObject))
		.addFunction("name", &(Scene::setName))
		.endClass();


	int scriptloadstatus = luaL_dofile(luastate, "LUA/escena.lua");

	sceneManager->sceneFactory->creator = [&](Scene* scene, int idx) {

		luabridge::push(luastate, scene);
		lua_setglobal(luastate, "scene");


		luabridge::LuaRef populatescene = luabridge::getGlobal(luastate, "escena0");
		populatescene();
	};

	return 0;
}

