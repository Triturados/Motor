#pragma once

#include <map>
#include <string>


namespace LoveEngine {
	namespace ECS {
		class Component;
	}
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

			ECS::Component* createComponent(std::string name);
		};


		class ComponentCreator {
			template<class CompType>
			friend class ComponentCreatorTemplate;
		public:
			std::string componentName;
			virtual ECS::Component* createComponent() {
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

			inline virtual ECS::Component* createComponent() override {
				return new CompType();
			};
		};
	}
}