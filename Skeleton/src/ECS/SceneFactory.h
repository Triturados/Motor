#pragma once
#include <functional>

class Scene;

class SceneFactory {

public:

	Scene* createScene(int idx);

	std::function<void(Scene* scene, int idx)> creator;
};