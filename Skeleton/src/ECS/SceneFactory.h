#pragma once
#include <functional>

namespace LoveEngine
{
	namespace ECS {
		class Scene;

	}
	namespace SceneManagement {

		class SceneFactory {

		public:

			ECS::Scene* createScene(int idx);

			std::function<void(ECS::Scene* scene, int idx)> creator;
		};
	}

}