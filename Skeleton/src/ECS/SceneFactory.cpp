#include "SceneFactory.h"
#include <Scene.h>

namespace LoveEngine {
	namespace SceneManagement {
		ECS::Scene* SceneFactory::createScene(int idx)
		{
			ECS::Scene* scene = new ECS::Scene("Escena");
			creator(scene, idx);
			return scene;
		}
	}
}
