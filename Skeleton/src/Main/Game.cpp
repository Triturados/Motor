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
#include <SoundManager.h>
#include <Sound.h>
#include <CameraComponent.h>
#include <LightComponent.h>
#include <RigidBody.h>
#include <Vector3.h>
#include <Vector4.h>
#include <lua.hpp>
#include <Input.h>
#include <LuaBridge/LuaBridge.h>

#include <memory>

typedef const char* (*GameName)();

using namespace std::chrono;
namespace LoveEngine {
	void Game::setup() {

		GameComponentDefinition gameComponentDefinitions;

		if (initialiseDLLs(gameComponentDefinitions)) {
			assert("Error al inicializar las DLL.", false);
		}

		time = new LoveEngine::Time();
		sceneManager = new LoveEngine::SceneManagement::SceneManager();
		compFactory = new LoveEngine::ComponentDefinitions::ComponentFactory();

		//Manager del proyecto de sonido
		soundManager = new LoveEngine::Audio::SoundManager();

		//Manager del proyecto de fisica
		physicsManager = new LoveEngine::Physics::PhysicsManager();

		//Manager del proyecto de render
		ogreManager = new LoveEngine::Renderer::OgreRenderer();

		//Manager del proyecto de Input
		inputManager = new LoveEngine::Input::InputManager();


		changeWindowTitle();

		ogreManager->getSceneManager()->destroyAllCameras();

		gameComponentDefinitions();

		initialiseSceneCreator();

		sceneManager->initiliseScenes();
		sceneManager->initialisePersistentScene();
	}


	void Game::loop()
	{
		const float numIterations = 3600;

		const float physicsFrameRate = 50;
		//double pInterval = 1.0 / physicsFrameRate;
		duration pInterval = duration<double>(1.0 / physicsFrameRate);

		steady_clock::time_point applicationStart = high_resolution_clock::now();
		steady_clock::time_point lastPhysicFrame = applicationStart;
		steady_clock::time_point beginFrame = applicationStart;

		for (int i = 0; i < numIterations; i++) {

			LoveEngine::ECS::Scene* currentScene = sceneManager->getCurrentScene();

			if (currentScene == nullptr) {
				break;
			}

			if (!inputManager->handleInput()) { //if SDl Quit, exit the game
				break;
			}

			currentScene->update();

			if ((beginFrame - lastPhysicFrame).count() > physicsFrameRate) {

				currentScene->stepPhysics();
				physicsManager->update(pInterval.count() * time->timeScale);

				lastPhysicFrame = beginFrame;
			}

			ogreManager->update();

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

		delete compFactory;
		delete sceneManager;
		delete time;

		delete ogreManager;
		delete inputManager;
		delete soundManager;
		//delete physicsManager;
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
			.addFunction("addComponent", &(LoveEngine::ECS::GameObject::createComponent))
			.addFunction("sendMssg", &(LoveEngine::ECS::GameObject::sendMessage))
			.addFunction("sendMsg", &(LoveEngine::ECS::GameObject::sendMessage))
			.endClass();

		luabridge::getGlobalNamespace(luastate)
			.beginClass<LoveEngine::ECS::Scene>("Scene")
			.addFunction("createObject", &(LoveEngine::ECS::Scene::createGameObject))
			.addFunction("createGameObject", &(LoveEngine::ECS::Scene::createGameObject))
			.addFunction("name", &(LoveEngine::ECS::Scene::setName))
			.endClass();

		luabridge::getGlobalNamespace(luastate)
			.beginClass<LoveEngine::ECS::Component>("Component")
			.addFunction("sendComponent", &(LoveEngine::ECS::Component::receiveComponent))
			.addFunction("sendGameObject", &(LoveEngine::ECS::Component::receiveGameObject))
			.addFunction("sendObject", &(LoveEngine::ECS::Component::receiveGameObject))
			.addFunction("sendMsg", &(LoveEngine::ECS::Component::receiveUnformattedMessage))
			.addFunction("sendMssg", &(LoveEngine::ECS::Component::receiveUnformattedMessage))
			.endClass();

	
		int scriptloadstatus = luaL_dofile(luastate, "LUA/escena.lua");
		sceneManager->sceneFactory->creator = [&](LoveEngine::ECS::Scene* scene, int idx) {

			luabridge::push(luastate, scene);
			lua_setglobal(luastate, "scene");

			luabridge::push(luastate, sceneManager->persistentScene->gObjects.front());
			lua_setglobal(luastate, "persistentObject");

			luabridge::push(luastate, sceneManager->persistentScene->gObjects.front());
			lua_setglobal(luastate, "persistentGameObject");

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
		sceneManager->numberOfScenes = count;

		return 0;
	}

	void Game::changeWindowTitle()
	{
		std::string title = "";
		GameName name = (GameName)GetProcAddress(game, "gameName");

		if (name == NULL)
			title = "LoveEngine";
		else
			title = name();

		ogreManager->changeWindowTitle(title);
	}

	void Game::updateTimeValues(const steady_clock::time_point& beginFrame, const steady_clock::time_point& endFrame, const steady_clock::time_point& appStart)
	{
		duration<float, std::milli> timeSinceStart = endFrame - appStart;
		duration<double, std::milli> timeSinceLastFrame = endFrame - beginFrame;

		time->timeSinceStart = timeSinceStart.count();
		time->deltaTime = timeSinceLastFrame.count() * 0.001;
		time->frameCount++;
	}
}