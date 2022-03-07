#include <Sound.h>
#include <iostream>
#include <OgreRenderer.h>
#include <SceneManager.h>
#include <Component.h>
#include <GameObject.h>
#include <Scene.h>
#include <PhysicsManager.h>

#include <lua.hpp>

//Ejemplo Componente
class ContadorFrames : public Component {

public:


	void update() override {

		if (cont == 14) {
			SceneManager::instance->changeScene(1, SceneLoad::PUSH);
		}
		std::cout << cont++ << "\n";
	}

private:
	int cont = 0;
};

//Ejemplo Componente
class ElComponenteDeDani : public Component {


public:
	void update() override {
		std::cout << "Ivan es muy tonto sinceramente\n";
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

	Scene* populateScene() override {

		Scene* scene = createScene("Escena");
		GameObject* go = createGameObject("Nombre");
		go->addComponent<ContadorFrames>();

		return scene;
	}
};


//Pruebas de proyectos
void probandoCosas()
{
	//LUA
	lua_State *L = luaL_newstate();

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
	
	
	//FMOD
	SoundSystemClass sound = SoundSystemClass(); //Inicializacion 

	// Create a sample sound
	SoundClass soundSample;
	sound.createSound(&soundSample, "../../resources/FMOD/Sonidos/sonido.wav",0);

	// Play the sound, with loop mode
	sound.playSound(soundSample, true);

	// Do something meanwhile...

	int a;
	std::cin >> a;

	// Release the sound
	sound.releaseSound(0);


	//GESTOR DE ESCENAS
	SceneManager* sceneManager = new SceneManager();
	sceneManager->defineScenesFactories({ new Escenadecontar(), new EscenaDeDani()});
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

	PhysicsManager* physicsManager = new PhysicsManager();

	while (main.update()) {};

}

void main()
{
	probandoCosas();
}

