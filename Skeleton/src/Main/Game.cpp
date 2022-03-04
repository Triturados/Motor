#include "Game.h"

#include <Scene.h>
#include <SceneManager.h>
#include <Component.h>
#include <GameObject.h>
#include <iostream>
#include <GameTime.h>
#include <chrono>
#include <thread>


using namespace std::chrono;

class ContadorFrames : public Component {

	int cont = 0;
public:
	void update() override {
		//std::cout << cont++ << "\n";
		cont++;
	}

};

class Escenadecontar : public SceneCreator {
	Scene* populateScene() override {

		Scene* scene = createScene("Escena de contar");
		GameObject* go = createGameObject("Objeto");
		go->addComponent<ContadorFrames>();

		return scene;
	}
};


void Game::setup()
{
	time = new GameTime();
	sceneManager = new SceneManager();
	sceneManager->defineScenesFactories({ new Escenadecontar() });
	sceneManager->initiliseScenes();
}


void Game::quit()
{
	delete sceneManager;
	delete time;
}

void Game::loop()
{
	const float numIterations = 60;

	const float updateFrameRate = 60;
	const float physicsFrameRate = 50;

	duration uInterval = duration<double>(1.0 / updateFrameRate);
	duration pInterval = duration<double>(1.0 / physicsFrameRate);

	auto applicationStart = high_resolution_clock::now();

	auto initialTime = applicationStart;
	for (int i = 0; i < numIterations; i++) {

		Scene* currentScene = sceneManager->getCurrentScene();

		if (currentScene == nullptr) {
			break;
		}

		//input();
		currentScene->update();
		currentScene->stepPhysics();
		currentScene->render();

		sceneManager->checkChange();

		//Calculo del tiempo
		auto currentTime = high_resolution_clock::now();

		duration<float, std::milli> timeSinceStart = currentTime - applicationStart;
		duration<double, std::milli> timeSinceLastFrame = currentTime - initialTime;
		duration<double, std::milli> sleepFor = uInterval - timeSinceLastFrame;


		time->timeSinceStart = timeSinceStart.count();
		time->deltaTime = timeSinceLastFrame.count();
		time->frameCount++;

		initialTime = currentTime;
		std::this_thread::sleep_for(sleepFor);
	}

	std::cout << "Frame rate medio: " << time->calculateFrameRate() << " Esperado: " << updateFrameRate << "\n";
	
	system("pause");
}



void Game::run()
{
	setup();
	loop();
	quit();
}