#include <Sound.h>
#include <iostream>
#include <OgreRenderer.h>
#include <SceneManager.h>
#include <Component.h>
#include <GameObject.h>
#include <Scene.h>


class ContadorFrames : public Component {

public:


	void update() override {

		if (cont == 14) {
			SceneManager::instance->changeScene(0, SceneLoad::PUSH);
		}
		std::cout << cont++ << "\n";
	}

private:
	int cont = 0;
};


class Escenadecontar : public SceneCreator {

	Scene* populateScene() override {

		Scene* scene = createScene("Escena");
		GameObject* go = createGameObject("Nombre");
		go->addComponent<ContadorFrames>();

		return scene;
	}
};



void useSystemSound()
{
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

	SceneManager* sceneManager = new SceneManager();
	sceneManager->defineScenesFactories({ new Escenadecontar() });
	sceneManager->initiliseScenes();

	const int numIterations = 60;
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
	}

	delete sceneManager;


	new ContadorFrames();







	OgreRenderer main = OgreRenderer();
	main.exampleScene();

	while (main.update()) {};

}

void main()
{
	//sound("aaaa");
	useSystemSound();
}

