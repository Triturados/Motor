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
			void receiveComponent(int i, Component* c) override;

			MouseTracker();
			~MouseTracker();
			void init() override;
			void update() override;
		};

	}
}

