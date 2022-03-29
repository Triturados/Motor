#pragma once

#include <map>
#include <string>

class Component;

namespace LoveEngine {

	namespace ComponentDefinitions {
	class ComponentCreator;

		class ComponentFactory {

		private:
			static ComponentFactory* instance;

			std::map<std::string, ComponentCreator*> components;

			void initialiseEngineComponents();
		public:

			static ComponentFactory* getInstance();
			ComponentFactory();
			~ComponentFactory();

			void registerComponent(ComponentCreator* fact);

			Component* createComponent(std::string name);
		};


		class ComponentCreator {
			template<class CompType>
			friend class ComponentCreatorTemplate;
		public:
			std::string componentName;
			virtual Component* createComponent() {
				return nullptr;
			}
		private:
			ComponentCreator(std::string name) {
				componentName = name;
			}
		};


		template <class CompType>
		class ComponentCreatorTemplate : public ComponentCreator {

		public:
			ComponentCreatorTemplate(std::string name) : ComponentCreator(name) {
			}

			inline virtual Component* createComponent() override {
				return new CompType();
			};
		};
	}
}