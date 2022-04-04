#pragma once
#include <../Export.h>
#include <Component.h>

namespace LoveEngine {
	namespace ECS {

		class lovexport MouseTracker: public Component {
		public:

			void update() override;

		};

	}
}

