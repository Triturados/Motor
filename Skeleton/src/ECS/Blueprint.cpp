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
			loadObject(go, name);
			go->init();
			go->postInit();
			return go;
		}

		void Blueprint::loadObject(GameObject* gameObject, std::string const& object) {


			auto luaObj = luabridge::getGlobal(luastate, object.c_str());

			if (luaObj.isNil()) { //Si no existe en lua buscar en el mapa en caso de que se haya creado por c++


				return;
			}

			auto name = luaObj["name"];
			if (!name.isNil())
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
							component->formatString(info.tostring());
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
						cmp->formatString(mssg.tostring());
					}
					return cmp;
				}
			}
			//cmp->formatString(info);

			return nullptr;
		}

	}
}
