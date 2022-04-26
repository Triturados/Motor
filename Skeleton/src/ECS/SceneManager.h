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

			//Número de escenas totales
			int sceneCount() const;

			//Índice o nombre de la escena actual
			int         currentSceneIdx() const;
			std::string currentSceneName() const;

			//Cuántas escenas hay ahora mismo en la pila
			int stackedScenes() const;

			//Cambiar a una escena dado su índice, indicando el tipo de cambio de escena
			void changeScene(int SceneIdx, SceneLoad type);

			//Comprueba si la escena debe cambiar, y la actualiza
			void tryChangeScene();

			//Finaliza la creación de escenas, para no añadir escenas en medio de la ejecución
			void initiliseScenes();
			//Añade las distintas escenas a la fábrica de escenas

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
