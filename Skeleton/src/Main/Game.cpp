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
#include <ComponentFactory.h>


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
	GameComponentDefinition gcd;

	int dlls = initialiseDLLs(escena, gcd);
	if (dlls) {
		std::cout << "Error DLLs";
		return 1;
	}


	time = new LoveEngine::Time();
	sceneManager = new SceneManager();
	compFactory = new ComponentFactory();

	gcd();
	SceneDefinitions* creator = escena();

	sceneManager->defineScenesFactories(creator->escenas);
	sceneManager->initiliseScenes();

	renderer = new OgreRenderer();
	renderer->exampleScene();

	PhysicsManager::setUpInstance();
	physics = PhysicsManager::getInstance();

	delete creator;
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



int Game::initialiseDLLs(Funct& escena, GameComponentDefinition& gcd)
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



void Game::quit()
{
	FreeLibrary(game);
	FreeLibrary(singleton);

	delete sceneManager;
	delete time;
	delete renderer;
	delete compFactory;
}
