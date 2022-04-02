#pragma once
#include <../Export.h>

#include <Component.h>
namespace FMOD {
	class System;
	class Sound;
	typedef Sound* SoundClass;
}
class SoundManager;

enum soundType { effects, environment, voices, music };

namespace LoveEngine {
	namespace ECS {

		class lovexport Sound : public Component
		{
		private:
			FMOD::SoundClass sound;
			SoundManager* soundMngr;

			int channel;
		public:

			Sound();
			~Sound();
			void createSound(SoundManager* manager, const char* pFile, int channel_);
			void playSound(soundType groupChannel, bool bLoop = false);
			void releaseSound();
			void setSpeed(float s);
		};
	}
}
