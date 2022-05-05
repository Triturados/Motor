#pragma once
#include <../Export.h>

#include <map>
#include <string>


namespace LoveEngine {
	namespace ECS {
		class Component;
	}
	namespace ComponentDefinitions {
		class ComponentCreator;

		class lovexport ComponentFactory {

		private:
			static ComponentFactory* instance;

			std::map<std::string, ComponentCreator*> components;

			void initialiseEngineComponents();
		public:

			static ComponentFactory* getInstance();
			ComponentFactory();
			~ComponentFactory();

			void registerComponent(ComponentCreator* fact);

			ECS::Component* createComponent(const  std::string& name);
		};


		class lovexport ComponentCreator {
			template<class CompType>
			friend class ComponentCreatorTemplate;
		public:
			std::string componentName;
			virtual ECS::Component* createComponent() {
				return nullptr;
			}
		private:
			ComponentCreator(const  std::string& name) {
				componentName = name;
			}
		};


		template <class CompType>
		class lovexport ComponentCreatorTemplate : public ComponentCreator {

		public:
			ComponentCreatorTemplate(const  std::string& name) : ComponentCreator(name) {
			}

			inline virtual ECS::Component* createComponent() override {
				return new CompType();
			};
		};
	}
}