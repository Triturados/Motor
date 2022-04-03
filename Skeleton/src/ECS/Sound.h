#pragma once
#include <../Export.h>

#include <Component.h>
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

		enum soundType { effects, environment, voices, music };

		class lovexport Sound : public Component
		{
		private:
			FMOD::SoundClass sound;
			LoveEngine::Audio::SoundManager* soundMngr;

			int channel;
		public:

			void createSound(const char* pFile, int channel_);
			void playSound(soundType groupChannel, bool bLoop = false);
			void releaseSound();
			void setSpeed(float s);
		};
	}
}
