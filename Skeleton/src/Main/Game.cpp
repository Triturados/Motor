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
#include <LightComponent.h>

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
		//go->addComponent<Transform>();
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

	renderer = new OgreRenderer();
	renderer->exampleScene();

	//GameObject* luz = new GameObject("Luz");
	//luz->addComponent<Transform>();

	////luz->getComponent<Transform>()->setPos(Vector3<float>(0, 200, 0));

	//luz->addComponent<LightComponent>();
	//
	//luz->getComponent<LightComponent>()->sendParameters(lightType::point, "luz", renderer->getSceneManager());

	PhysicsManager::setUpInstance();
	physics = PhysicsManager::getInstance();
}


void Game::quit()
{
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
		time->deltaTime = timeSinceLastFrame.count();
		time->frameCount++;

		initialTime = currentTime;

		//std::this_thread::sleep_for(sleepFor);
	}

	std::cout << "Frame rate medio: " << time->calculateFrameRate() << " Esperado: " << updateFrameRate << "\n";
}



void Game::run()
{
	setup();
	loop();
	quit();
}
