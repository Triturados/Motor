#pragma once
#include <string>

class lua_State;
namespace LoveEngine {
	namespace ECS {
		class Scene;
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


	void parseScene(ECS::Scene* scene, lua_State* luastate, std::string scenename);
}