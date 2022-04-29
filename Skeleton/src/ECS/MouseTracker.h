#pragma once
#include <../Export.h>
#include <Component.h>

namespace LoveEngine {

	namespace ECS {
		class Camera;
		class lovexport MouseTracker: public ComponentTemplate<MouseTracker>
		{
		private:
			Camera* maincam;
			float rotationSpeed;
			Utilities::Vector2<int>* mousepos;
		public:
			void receiveComponent(int i, Component* c) override;

			MouseTracker();
			~MouseTracker();
			void init() override;
			void update() override;
		};

	}
}

