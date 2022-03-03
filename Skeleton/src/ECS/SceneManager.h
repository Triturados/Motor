#pragma once
#include <vector>
#include <stack>
#include <functional>
#include <string>

/// <summary>
/// =PUSH  : ADD THE NEW SCENE AT THE TOP OF THE STACK
/// =POP   : REMOVE THE SCENE AT THE TOP OF THE STACK
/// =CLEAR : REMOVES ALL PREVIOUS SCENE AND CREATES THE NEW ONE
/// =SWAP  : REMOVE THE SCENE AT THE TOP OF THE STACK AND CREATES THE NEW ONE
/// </summary>
enum class SceneLoad {
	PUSH, POP, CLEAR, SWAP
};


class Scene;
class SceneCreator;
using SceneFactory = std::vector<SceneCreator*>;


class SceneManager final {

public:
	static SceneManager* instance;
	SceneManager();
	~SceneManager();

	Scene* getCurrentScene();

	//Número de escenas totales
	int sceneCount() const;

	//Índice o nombre de la escena actual
	int         currentSceneIdx () const;
	std::string currentSceneName() const;

	//Cuántas escenas hay ahora mismo en la pila
	int currentSceneCount() const;

	//Cambiar a una escena dado su índice, indicando el tipo de cambio de escena
	void changeScene(int SceneIdx, SceneLoad type);
	
	//Comprueba si la escena debe cambiar, y la actualiza
	void checkChange();

	//Finaliza la creación de escenas, para no añadir escenas en medio de la ejecución
	void initiliseScenes();
	//Añade las distintas escenas a la fábrica de escenas
	void defineScenesFactories(SceneFactory scenes);
protected:

	int currentIdx = 0;
	bool initialised = false;

	bool shouldChange = false;
	int sceneToLoad = -1;
	SceneLoad sceneChangeType;

	void eraseTopScene();
	void createScene();
	void manageScene();

	//Vector con todas las escenas
	SceneFactory scenesTemplates;
	//Pila con las escenas actuales
	std::stack<Scene*> currentScene;
};
