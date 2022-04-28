#pragma once

#include <../Export.h>
#include <map>
#include <vector>
#include <string>

class lua_State;

namespace LoveEngine {
	namespace ECS {

		class Scene;
		class Component;
		class GameObject;

		struct lovexport ComponentBlueprint
		{
			std::string type;
			std::string message;
		};

		struct lovexport ObjectBlueprint {
			
			std::string name;
			std::vector<std::string> components;
		};

		class lovexport Blueprint
		{

		private:
			static Blueprint* instance;
			
			lua_State* luastate;

			std::map<std::string, ObjectBlueprint*>		objects;
			std::map<std::string, ComponentBlueprint*>	components;

			std::vector<Component*> loadObject(GameObject* gameObject, std::string const& object, bool changename);
		public:
			Blueprint();
			~Blueprint();

			static Blueprint* getInstance();


			Component* addComponent(GameObject* gameObject, std::string const& component, bool init = true);

			GameObject* spawnObject(Scene* scene, std::string const& name, bool init = true);
			GameObject* fillObject (GameObject* gameObject, std::string const& name, bool init = true);
		};
	}
}
