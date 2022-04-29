#pragma once
#include <../Export.h>

#include <Component.h>
#include <string>

namespace FMOD {
	class System;
	class Sound;
	typedef Sound* SoundClass;
}

namespace LoveEngine {
	namespace Audio {
		class SoundManager;
	}
	namespace ECS {

		enum class soundType { effects, environment, voices, music };

		class lovexport Sound : public Component
		{
		private:
			FMOD::SoundClass sound;
			LoveEngine::Audio::SoundManager* soundMngr;

			std::string soundRoute;
			soundType groupChannel;
			int channel = 0;
			bool bLoop = false;
		public:

			void init() override;
			void receiveMessage(Utilities::StringFormatter& s) override;
			void playSound();
			void releaseSound();
			void setSpeed(float s);
			void pause(bool pause);
			void setVolume(float volume);
		};
	}
}
