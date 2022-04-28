#include "Blueprint.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

#include <Component.h>
#include <GameObject.h>
#include <Scene.h>

namespace LoveEngine {
	namespace ECS {

		Blueprint* Blueprint::instance = nullptr;

		Blueprint::Blueprint() {
			luastate = luaL_newstate();
			luaL_openlibs(luastate);

			if (luaL_dofile(luastate, "LUA/blueprints.lua")) {
				lua_close(luastate);
				luastate = nullptr;
			}

			instance = this;
		}

		Blueprint::~Blueprint() {
			if (luastate != nullptr) {
				lua_close(luastate);
				luastate = nullptr;
			}
		}

		Blueprint* Blueprint::getInstance() {
			return instance;
		}

		GameObject* Blueprint::spawnObject(Scene* scene, std::string const& name) {
			GameObject* go = scene->createGameObject(name);
			loadObject(go, name, true);
			go->init();
			go->postInit();
			return go;
		}

		GameObject* Blueprint::fillObject(GameObject* gameObject, std::string const& name)
		{
			loadObject(gameObject, name, false);
			return gameObject;
		}

		void Blueprint::loadObject(GameObject* gameObject, std::string const& object, bool changename) {

			auto luaObj = luabridge::getGlobal(luastate, object.c_str());

			if (luaObj.isNil()) { //Not defined in lua

				auto obj = objects.find(object);
				if (obj != objects.end()) {
					ObjectBlueprint* objbp = obj->second;

					if (changename)
						gameObject->name = objbp->name;

					for (auto cmp : objbp->components) {
						addComponent(gameObject, cmp);
					}
				}
				return;
			}

			auto name = luaObj["name"];
			if (changename && !name.isNil())
				gameObject->name = name.tostring();

			auto components = luaObj["components"];
			if (!components.isNil()) {
				for (int i = 1; i <= components.length(); i++) {
					auto cmp = components[i];
					auto type = cmp["type"];
					if (type.isNil())
						addComponent(gameObject, components[i].tostring());
					else {

						Component* component = gameObject->createComponent(type);

						auto info = cmp["values"];
						if (!info.isNil())
							component->sendFormattedString(info.tostring());
					}
				}
			}
		}

		Component* Blueprint::addComponent(GameObject* gameObject, std::string const& component) {

			auto luacmp = luabridge::getGlobal(luastate, component.c_str());

			if (!luacmp.isNil()) { //Component is defined in lua
				auto type = luacmp["type"];

				if (!type.isNil()) {
					Component* cmp = gameObject->createComponent(type);

					auto mssg = luacmp["info"];
					if (!mssg.isNil())
					{
						cmp->sendFormattedString(mssg.tostring());
					}
					return cmp;
				}
			}

			auto cppcmp = components.find(component);
			if (cppcmp != components.end()) { //Component defined in cpp
				ComponentBlueprint* cmpbp = cppcmp->second;
				Component* cmp = gameObject->createComponent(cmpbp->type);

				if (cmpbp->message != "") {
					cmp->sendFormattedString(cmpbp->message);
				}
				return cmp;
			}

			return nullptr;
		}

	}
}
