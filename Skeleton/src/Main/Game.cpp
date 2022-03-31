#include "Game.h"

#include <iostream>
#include <Scene.h>
#include <Component.h>
#include <GameObject.h>
#include <GameTime.h>
#include <ComponentFactory.h>
#include <thread>
#include <Windows.h>
#include <time.h>
#include <SceneFactory.h>

#include <PhysicsManager.h>
#include <OgreRenderer.h>
#include <SceneManager.h>

#include <Sound.h>
#include <Transform.h>
#include <Mesh.h>
#include <CameraComponent.h>
#include <LightComponent.h>
#include <RigidBody.h>
#include <Vector3.h>
#include <lua.hpp>
#include <Input.h>
#include <LuaBridge/LuaBridge.h>

#include <memory>


using namespace std::chrono;

void Game::run()
{
	if (setup() == 0) {
		loop();
		quit();
	}
}

int Game::setup()
{
	GameComponentDefinition gameComponentDefinitions;

	if (initialiseDLLs(gameComponentDefinitions)) {
		return 1;
	}

	input = new Input();
	time = new LoveEngine::Time();
	sceneManager = new LoveEngine::SceneManagement::SceneManager();
	compFactory = new LoveEngine::ComponentDefinitions::ComponentFactory();

	gameComponentDefinitions();

	initialiseSceneCreator();

	sceneManager->initiliseScenes();

	renderer = new OgreRenderer();
	//renderer->exampleScene();

	PhysicsManager::setUpInstance();
	physics = PhysicsManager::getInstance();

	LoveEngine::ECS::GameObject* camera = sceneManager->getCurrentScene()->createGameObject("objCamera");
	camera->addComponent<LoveEngine::ECS::Transform>();
	camera->getComponent<LoveEngine::ECS::Transform>()->setPos(new Utilities::Vector3<float>(0.0, 0.0, 50.0));
	camera->addComponent<LoveEngine::ECS::CameraComponent>();
	camera->getComponent<LoveEngine::ECS::CameraComponent>()->lookAt(new Utilities::Vector3<float>(0.0, 0.0, 50.0));
	camera->getComponent<LoveEngine::ECS::CameraComponent>()->setActive(true);

	LoveEngine::ECS::GameObject* luz = sceneManager->getCurrentScene()->createGameObject("objLuz");
	luz->addComponent<LoveEngine::ECS::Transform>();
	luz->getComponent<LoveEngine::ECS::Transform>()->setPos(new Utilities::Vector3<float>(0.0, 10.0, 0.0));
	luz->addComponent<LoveEngine::ECS::LightComponent>();

	LoveEngine::ECS::GameObject* go = sceneManager->getCurrentScene()->createGameObject("obj1");
	go->addComponent<LoveEngine::ECS::Transform>();
	go->addComponent<LoveEngine::ECS::Mesh>();
	go->getComponent <LoveEngine::ECS::Mesh>()->sendParameters("ogrehead.mesh", nullptr, nullptr, 
		nullptr, nullptr, go->getComponent<LoveEngine::ECS::Transform>());
	go->getComponent<LoveEngine::ECS::Mesh>()->init();
	go->addComponent<LoveEngine::ECS::RigidBody>();
	go->getComponent<LoveEngine::ECS::RigidBody>()->setTransform(go->getComponent<LoveEngine::ECS::Transform>());
	go->getComponent<LoveEngine::ECS::RigidBody>()->setMass(1.0);
	go->getComponent<LoveEngine::ECS::RigidBody>()->init();
	Utilities::Vector3<float>* vel = new Utilities::Vector3<float>(0, -50, 0);
	Utilities::Vector3<float>* pos = new Utilities::Vector3<float>(0, 0, 0);
	go->getComponent<LoveEngine::ECS::RigidBody>()->addForce(*vel, *pos, 0);
	
	//delete creator;
	return 0;
}


void Game::loop()
{
	const float numIterations = 360;

	const float physicsFrameRate = 50;
	//double pInterval = 1.0 / physicsFrameRate;
	duration pInterval = duration<double>(1.0 / physicsFrameRate);

	steady_clock::time_point applicationStart = high_resolution_clock::now();
	steady_clock::time_point lastPhysicFrame  = applicationStart;
	steady_clock::time_point beginFrame       = applicationStart;

	for (int i = 0; i < numIterations; i++) {

		LoveEngine::ECS::Scene* currentScene = sceneManager->getCurrentScene();

		if (currentScene == nullptr) {
			break;
		}

		input->handleInput();

		currentScene->update();

		if ((beginFrame - lastPhysicFrame).count() > physicsFrameRate) {

			currentScene->stepPhysics();
			physics->update(pInterval.count() * time->timeScale);

			lastPhysicFrame = beginFrame;
		}

		renderer->update();

		sceneManager->tryChangeScene();

		//Calculo del tiempo
		steady_clock::time_point endFrame = high_resolution_clock::now();
		updateTimeValues(beginFrame, endFrame, applicationStart);
		beginFrame = endFrame;
	}
}

void Game::quit()
{
	FreeLibrary(game);
	FreeLibrary(singleton);

	delete sceneManager;
	delete time;
	delete renderer;
	delete compFactory;
	delete input;
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
	input = new Input();
	Input::initSDLWindowTest();

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



int Game::initialiseDLLs(GameComponentDefinition& gcd)
{

#ifdef _DEBUG
	game = LoadLibrary(TEXT("./Game_d.dll"));
	singleton = LoadLibrary(TEXT("Singleton_d.dll"));
#else
	game = LoadLibrary(TEXT("./Game.dll"));
	singleton = LoadLibrary(TEXT("Singleton.dll"));
#endif


	if (singleton == NULL) {
		std::cout << "No se encontro la biblioteca de singletons";
		return 1;
	}

	if (game == NULL) {
		std::cout << "No se encontro el juego\n";
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
		.beginClass<LoveEngine::ECS::GameObject>("GameObject")
		.addConstructor<void(*)(std::string, LoveEngine::ECS::Scene*)>()
		.addFunction("addComponent", &(LoveEngine::ECS::GameObject::createComponent))
		.endClass();

	luabridge::getGlobalNamespace(luastate)
		.beginClass<LoveEngine::ECS::Scene>("Scene")
		.addFunction("createObject", &(LoveEngine::ECS::Scene::createGameObject))
		.addFunction("name", &(LoveEngine::ECS::Scene::setName))
		.endClass();

	luabridge::getGlobalNamespace(luastate)
		.beginClass<LoveEngine::ECS::Component>("Component")
		.addFunction("send4", &(LoveEngine::ECS::Component::sendValues))
		.addFunction("send3", &(LoveEngine::ECS::Component::send3values))
		.addFunction("send2", &(LoveEngine::ECS::Component::send2values))
		.addFunction("send1", &(LoveEngine::ECS::Component::send1value))
		.addFunction("send", &(LoveEngine::ECS::Component::send1value))
		.endClass();


	int scriptloadstatus = luaL_dofile(luastate, "LUA/escena.lua");

	sceneManager->sceneFactory->creator = [&](LoveEngine::ECS::Scene* scene, int idx) {

		luabridge::push(luastate, scene);
		lua_setglobal(luastate, "scene");

		std::string scenestring = "scene" + std::to_string(idx);
		luabridge::LuaRef populateScene = luabridge::getGlobal(luastate, &scenestring[0]);
		populateScene();
	};

	int count = 0;
	bool isNil = false;
	while (!isNil) {
		std::string scenestring = "scene" + std::to_string(count++);
		luabridge::LuaRef populateScene = luabridge::getGlobal(luastate, &scenestring[0]);
		isNil = populateScene.isNil();
	}
	sceneManager->numberOfScenes = count - 1;

	return 0;
}

void Game::updateTimeValues(const steady_clock::time_point& beginFrame, const steady_clock::time_point& endFrame, const steady_clock::time_point& appStart)
{
	duration<float, std::milli> timeSinceStart = endFrame - appStart;
	duration<double, std::milli> timeSinceLastFrame = endFrame - beginFrame;

	time->timeSinceStart = timeSinceStart.count();
	time->deltaTime = timeSinceLastFrame.count() * 0.001;
	time->frameCount++;

}

