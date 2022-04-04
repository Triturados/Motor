#pragma once
#include <../Export.h>
#include <Component.h>

namespace LoveEngine {

	namespace Utilities {
		template <class t>
		class Vector2;
	}

	namespace ECS {
		class Camera;
		class lovexport MouseTracker: public Component {
		private:
			Camera* maincam;
			float rotationSpeed;
			Utilities::Vector2<float>* mousepos;
		public:
			MouseTracker();
			~MouseTracker();
			void init() override;
			void update() override;
			void receiveValues(int, float, Component*, GameObject*) override;
		};

	}
}

