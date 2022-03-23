#include "Game.h"

#include <Scene.h>
#include <SceneManager.h>
#include <Component.h>
#include <GameObject.h>
#include <iostream>
#include <GameTime.h>
#include <chrono>
#include <thread>
#include <OgreRenderer.h>
#include <Transform.h>
#include <PhysicsManager.h>





struct SceneDefinitions {
	std::vector<SceneCreator*> escenas;
	void scenesDefinitions();
};


using namespace std::chrono;
typedef SceneDefinitions* (*Funct)();

int Game::setup()
{
	game = LoadLibrary(TEXT("./Game.dll"));
	singleton = LoadLibrary(TEXT("Singleton.dll"));

	if (singleton == NULL) {
		std::cout << "No se encontró la biblioteca de singletons";
		return 1;
	}

	if (game == NULL) {
		std::cout << "No se encontró el juego\n";
		return 1;
	}

	Funct escena = (Funct)GetProcAddress(game, "quierounaescena");

	if (escena == NULL) {
		std::cout << "No se encontró inicio del juego\n";
		return 1;
	}


	SceneDefinitions* creator = escena();


	time = new LoveEngine::Time();
	sceneManager = new SceneManager();
	sceneManager->defineScenesFactories(creator->escenas);
	sceneManager->initiliseScenes();

	renderer = new OgreRenderer();
	renderer->exampleScene();

	PhysicsManager::setUpInstance();
	physics = PhysicsManager::getInstance();

	return 0;
}


void Game::quit()
{
	FreeLibrary(game);
	FreeLibrary(singleton);

	delete sceneManager;
	delete time;
	delete renderer;
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

		//input();

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



void Game::run()
{
	if (setup() == 0) {
		loop();
		quit();
	}
}
