#pragma once
#include <string>

class lua_State;

namespace LoveEngine {
	namespace ECS {
		class Scene;
		class Component;
		class GameObject;
	}

	void setWindowSize(int x, int y);

	int getWidth();

	int getHeight();

	std::string getWindowTitle();

	void setWindowTitle(std::string);

	void setFullScreen(bool);

	void setIcon(std::string);

	float random(); // 0 - 1

	int randomBetween(int min, int max); //exclusive

	void print(std::string str);

	int round(float);
	int floor(float);
	int ceil(float);


	ECS::GameObject* BlueprintSpawnObject(ECS::Scene* scene, std::string name);
	ECS::GameObject* BlueprintFillObject(ECS::GameObject* gameObject, std::string name);
	ECS::Component*	 BlueprintAddComponent(ECS::GameObject* gameObject, std::string cmpname);

	void parseScene(ECS::Scene* scene, lua_State* luastate, std::string scenename);
}