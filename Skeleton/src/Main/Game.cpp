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

		//Manager del proyecto de Input
		inputManager = new LoveEngine::Input::InputManager();

		//Manager del proyecto de sonido
		soundManager = new LoveEngine::Audio::SoundManager();

		//Manager del proyecto de fisica
		physicsManager = new LoveEngine::Physics::PhysicsManager();

		//Manager del proyecto de render
		ogreManager = new LoveEngine::Renderer::OgreRenderer();

		gameComponentDefinitions();

		initialiseSceneCreator();

		sceneManager->initiliseScenes();

		ogreManager->exampleScene();
		ogreManager->getSceneManager()->destroyAllCameras();

		//LoveEngine::ECS::GameObject* camera = sceneManager->getCurrentScene()->createGameObject("objCamera");
		//LoveEngine::ECS::Transform* transformCamera = camera->addComponent<LoveEngine::ECS::Transform>();
		//transformCamera->setPos(Utilities::Vector3<float>(0.0, 10.0, 100.0));
		//LoveEngine::ECS::Camera* cam = camera->addComponent<LoveEngine::ECS::Camera>();
		//cam->send3values(0, 0, camera->getComponent<LoveEngine::ECS::Transform>());
		//cam->init();
		//cam->lookAt(Utilities::Vector3<float>(0.0, 0.0, -50.0));
		//cam->setActive(true);

		//LoveEngine::ECS::GameObject* luz = sceneManager->getCurrentScene()->createGameObject("objLuz");
		//LoveEngine::ECS::Transform* transformLight = luz->addComponent<LoveEngine::ECS::Transform>();
		//transformLight->setPos(Utilities::Vector3<float>(0.0, 10.0, 50.0));
		//LoveEngine::ECS::Light* lightC = luz->addComponent<LoveEngine::ECS::Light>();
		//lightC->receiveValues(LoveEngine::ECS::lightType::point, 1, transformLight);
		//lightC->init();

		///*LoveEngine::ECS::GameObject* go = sceneManager->getCurrentScene()->createGameObject("obj1");
		//LoveEngine::ECS::Transform* t = go->addComponent<LoveEngine::ECS::Transform>();
		//LoveEngine::ECS::Mesh* m = go->addComponent<LoveEngine::ECS::Mesh>();
		//m->sendvalues("ogrehead.mesh", t);
		//m->init();*/

		//LoveEngine::ECS::GameObject* go = sceneManager->getCurrentScene()->createGameObject("obj1");
		//LoveEngine::ECS::Sound* s = go->addComponent<LoveEngine::ECS::Sound>();
		//s->receiveValues(LoveEngine::ECS::soundType::effects, 0);
		//s->receiveMessage("soundName: wii.mp3; bLoop: false");
		//s->init();
		//soundManager->setVolumeChannel(LoveEngine::ECS::soundType::effects, 0.1);
		//s->playSound();

		///*LoveEngine::ECS::GameObject* go2 = sceneManager->getCurrentScene()->createGameObject("obj2");
		//LoveEngine::ECS::Transform* t2 = go2->addComponent<LoveEngine::ECS::Transform>();
		//Utilities::Vector3<float>* v = new Utilities::Vector3<float>(20, 0, 0);
		//t2->setParent(t); t2->setPos(v);
		//LoveEngine::ECS::Mesh* m2 = go2->addComponent<LoveEngine::ECS::Mesh>();
		//m2->sendvalues("ogrehead.mesh", t2);
		//m2->init();

		//Utilities::Vector3<float>* v2 = new Utilities::Vector3<float>(-20, 0, 0);
		//t->setPos(v2);
		//Utilities::Vector4<float>* v3 = new Utilities::Vector4<float>(0, 0, 90, 0);
		//t->rotate(v3);*/

		//LoveEngine::ECS::GameObject* suelo = sceneManager->getCurrentScene()->createGameObject("suelo");
		//suelo->addComponent<LoveEngine::ECS::Transform>();
		//suelo->getComponent<LoveEngine::ECS::Transform>()->setScale(Utilities::Vector3<float>(70., 1., 70.));

		//LoveEngine::ECS::Mesh* sueloMesh = suelo->addComponent<LoveEngine::ECS::Mesh>();
		//sueloMesh->receiveValues(0, 0,
		//	suelo->getComponent<LoveEngine::ECS::Transform>());
		//sueloMesh->receiveMessage("meshName: cube.mesh");
		//sueloMesh->init();

		//suelo->addComponent<LoveEngine::ECS::RigidBody>();
		//suelo->getComponent<LoveEngine::ECS::RigidBody>()->receiveValues(1, 0., suelo->getComponent<LoveEngine::ECS::Transform>());
		//suelo->getComponent<LoveEngine::ECS::RigidBody>()->receiveMessage("forma: cube;");
		//suelo->getComponent<LoveEngine::ECS::RigidBody>()->init();

		//LoveEngine::ECS::GameObject* pelota = sceneManager->getCurrentScene()->createGameObject("obj1");
		//LoveEngine::ECS::Transform* pelotaTransform = pelota->addComponent<LoveEngine::ECS::Transform>();
		//pelotaTransform->setPos(Utilities::Vector3<float>(0, 15, 0));

		//LoveEngine::ECS::Mesh* pelotaMesh = pelota->addComponent<LoveEngine::ECS::Mesh>();
		//pelotaMesh->receiveValues(0, 0, pelota->getComponent<LoveEngine::ECS::Transform>());
		//pelotaMesh->receiveMessage("meshName: sphere.mesh");
		//pelotaMesh->init();


		//pelota->addComponent<LoveEngine::ECS::RigidBody>();
		//pelota->getComponent<LoveEngine::ECS::RigidBody>()->receiveValues(1, 1.0, pelota->getComponent<LoveEngine::ECS::Transform>());
		//pelota->getComponent<LoveEngine::ECS::RigidBody>()->receiveMessage("forma: sphere;");
		//pelota->getComponent<LoveEngine::ECS::RigidBody>()->init();

	}


	void Game::loop()
	{
		const float numIterations = 360;

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

			inputManager->handleInput();

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


	//M�todos temporales para testing
	void Game::testing()
	{
		int a;
		std::cout << "Pulsa los siguientes botones para probar cada proyecto:\n";
		std::cout << "0 - LUA\n1 - Input\n2 - OGRE\n3 - FMOD\n4 - Bullet\n5 - LuaBridge\n";
		std::cin >> a;

		switch (a) {
		case 0: lua(); break;
		case 1: sdlinput(); break;
		case 2: ogre(); break;
		case 3: fmod(); break;
		case 4: bullet(); break;
		case 5: luabridge(); break;
		default: break;
		}

		std::cout << "Escribe algo para salir: "; std::cin >> a;
	}


	void Game::sdlinput() {
		/*inputManager = new InputManager();
		InputManager::initSDLWindowTest();*/

		//while (true) inputManager->handleInput();
	}

	void Game::fmod()
	{
		//FMOD
		Audio::SoundManager sound = Audio::SoundManager(); //Inicializacion

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

	void Game::ogre() {
		Game game;
		game.setup();
		game.loop();
		game.quit();
	}

	void Game::bullet() {
		physicsManager->bulletTest();
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
			.addFunction("addComponent", &(LoveEngine::ECS::GameObject::createComponent))
			.addFunction("sendMssg", &(LoveEngine::ECS::GameObject::sendMessage))
			.addFunction("sendMsg", &(LoveEngine::ECS::GameObject::sendMessage))
			.endClass();

		luabridge::getGlobalNamespace(luastate)
			.beginClass<LoveEngine::ECS::Scene>("Scene")
			.addFunction("createObject", &(LoveEngine::ECS::Scene::createGameObject))
			.addFunction("name", &(LoveEngine::ECS::Scene::setName))
			.endClass();

		luabridge::getGlobalNamespace(luastate)
			.beginClass<LoveEngine::ECS::Component>("Component")
			.addFunction("send4", &(LoveEngine::ECS::Component::receiveValues)) //int float comp gameObject
			.addFunction("send3", &(LoveEngine::ECS::Component::send3values))
			.addFunction("send2", &(LoveEngine::ECS::Component::send2values))
			.addFunction("send1", &(LoveEngine::ECS::Component::send1value))
			.addFunction("send", &(LoveEngine::ECS::Component::send1value))
			.addFunction("sendMsg", &(LoveEngine::ECS::Component::receiveMessage))
			.addFunction("sendMssg", &(LoveEngine::ECS::Component::receiveMessage))
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
		sceneManager->numberOfScenes = count;

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
}