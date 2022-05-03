#pragma once
#include <../Export.h>

#include <Component.h>
#include <string>
#include <functional>

namespace LoveEngine {
	namespace ECS {
		class Sound;
		class Button;

		class lovexport SoundButton : public Component
		{
		private:
			ECS::Sound* sound;
			ECS::Button* button;

		public:
			void init() override;
			void postInit() override;
			void removeSound();
		};
	}
}
