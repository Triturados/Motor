#include "SceneFactory.h"
#include <Scene.h>


Scene* SceneFactory::createScene(int idx)
{
	Scene* scene = new Scene("Escena");
	creator(scene, idx);
	return scene;
}
