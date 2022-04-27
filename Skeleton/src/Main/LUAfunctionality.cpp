#include "LUAfunctionality.h"
#include <Window.h>
#include <random>
#include <iostream>
#include <Scene.h>
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <GameObject.h>
#include <Component.h>
#include <Blueprint.h>

namespace LoveEngine {

	void setWindowSize(int x, int y) {
		Window::getInstance()->setWindowSize(x, y);
	}

	int getWidth() {
		return Window::getInstance()->getWindowSize().x;
	}
	int getHeight() {
		return Window::getInstance()->getWindowSize().y;
	}

	std::string getWindowTitle() {
		return Window::getInstance()->getWindowTitle();
	}

	void setWindowTitle(std::string s) {
		Window::getInstance()->setWindowTitle(s);
	}

	void setFullScreen(bool val) {
		Window::getInstance()->setFullScreen(val);
	}

	void setIcon(std::string val) {
		Window::getInstance()->setWindowIcon(val);
	}

	float random()
	{
		return rand() % 1000 / 1000.0;
	}

	int randomBetween(int min, int max)
	{
		int dif = max - min;
		int r = rand() % dif;
		return min + r;
	}

	void print(std::string mssg) {
		std::cout << mssg << "\n";
	}

	int round(float t) {
		return std::round(t);
	}

	int floor(float t) {
		return std::floor(t);
	}

	int ceil(float t) {
		return std::ceil(t);
	}

	ECS::GameObject* BlueprintSpawnObject(ECS::Scene* scene, std::string name)
	{
		return ECS::Blueprint::getInstance()->spawnObject(scene, name);
	}

	ECS::GameObject* BlueprintFillObject(ECS::GameObject* gameObject, std::string name)
	{
		return ECS::Blueprint::getInstance()->fillObject(gameObject, name);
	}

	ECS::Component* BlueprintAddComponent(ECS::GameObject* gameObject, std::string cmpname)
	{
		return ECS::Blueprint::getInstance()->addComponent(gameObject, cmpname);
	}


	void parseScene(ECS::Scene* scene, lua_State* luastate, std::string scenename)
	{
		luabridge::LuaRef luascene = luabridge::getGlobal(luastate, &scenename[0]);

		if (luascene.isNil())
			return;

		if (luascene.isFunction()) {
			luascene();
			return;
		}

		auto name = luascene["name"];
		if (!name.isNil())
			scene->name = name.tostring();

		auto objects = luascene["objects"];
		for (int go = 1; go <= objects.length(); go++) {

			if (objects[go].isNil()) {
				print("Error en los objetos");
				return;
			}
			auto gameObjectName = objects[go]["name"];
			std::string nameStr = gameObjectName.isNil() ? "New GameObject" : gameObjectName.tostring();
			ECS::GameObject* gameObject = scene->createGameObject(nameStr);

			auto components = objects[go]["components"];
			if (components.isNil())
				continue;

			for (int cmp = 1; cmp <= components.length(); cmp++) {

				auto cmpType = components[cmp]["type"];
				if (cmpType.isNil())
					continue;

				ECS::Component* component = gameObject->createComponent(cmpType.tostring());

				auto cmpInfo = components[cmp]["info"];
				if (cmpInfo.isNil())
					continue;

				component->formatString(cmpInfo.tostring());
			}
		}

		auto code = luascene["code"];
		if (!code.isNil())
			code();
	}
}