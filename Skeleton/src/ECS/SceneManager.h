#pragma once
#include <vector>
#include <stack>
#include <functional>
#include <string>
#include <../Export.h>



namespace LoveEngine {
	namespace ECS {
		class Scene;
	}

	namespace SceneManagement {
		class SceneFactory;

		/// <summary>
		/// =PUSH  : ADD THE NEW SCENE AT THE TOP OF THE STACK
		/// =POP   : REMOVE THE SCENE AT THE TOP OF THE STACK
		/// =CLEAR : REMOVES ALL PREVIOUS SCENE AND CREATES THE NEW ONE
		/// =SWAP  : REMOVE THE SCENE AT THE TOP OF THE STACK AND CREATES THE NEW ONE
		/// =EXIT  : STOPS THE GAME
		/// </summary>
		enum class SceneLoad {
			PUSH, SWAP, POP, CLEAR, EXIT
		};

		
		class lovexport SceneManager final {
			friend class Engine;
			friend ECS::Scene;

			static SceneManager* instance;
		public:
			static  SceneManager* getInstance();
			SceneManager();
			~SceneManager();

			ECS::Scene* getCurrentScene();

			//N�mero de escenas totales
			int sceneCount() const;

			//�ndice o nombre de la escena actual
			int         currentSceneIdx() const;
			std::string currentSceneName() const;

			//Cu�ntas escenas hay ahora mismo en la pila
			int stackedScenes() const;

			//Cambiar a una escena dado su �ndice, indicando el tipo de cambio de escena
			void changeScene(int SceneIdx, SceneLoad type);

			//Comprueba si la escena debe cambiar, y la actualiza
			void tryChangeScene();

			//Finaliza la creaci�n de escenas, para no a�adir escenas en medio de la ejecuci�n
			void initiliseScenes();
			//A�ade las distintas escenas a la f�brica de escenas

		private:
			ECS::Scene* persistentScene;
			void updatePersistentScene();
			void initialisePersistentScene();

			SceneManagement::SceneFactory* sceneFactory;

			int numberOfScenes = 0;

			int currentIdx = 0;
			bool initialised = false;

			bool shouldChange = false;
			int sceneToLoad = -1;
			SceneLoad sceneChangeType;

			void eraseTopScene();
			void createScene();
			void manageScene();

			void createSplashScreen();

			//Pila con las escenas actuales
			std::stack<ECS::Scene*> currentScene;
		};


		
		//void changeSceneByIndex(int idx, int scenechangetype) {
		//	changeScene(idx, (SceneLoad)scenechangetype);
		//}
		lovexport void changeScene(int idx, SceneManagement::SceneLoad scenechangetype);
	}

	
}
//
//lovexport int damenumero() {
//	return 13;
//}
