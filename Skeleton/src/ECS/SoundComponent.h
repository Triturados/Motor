#pragma once

#include <Component.h>
namespace FMOD {
	class System;
	class Sound;
	typedef Sound* SoundClass;
}
class SoundSystemClass;

enum soundType { effects, environment, voices, music };

namespace LoveEngine {
	namespace ECS {

		class SoundComponent : public Component
		{
		private:
			FMOD::SoundClass sound;
			SoundSystemClass* soundMngr;

			int channel;
		public:

			SoundComponent();
			~SoundComponent();
			void createSound(SoundSystemClass* manager, const char* pFile, int channel_);
			void playSound(soundType groupChannel, bool bLoop = false);
			void releaseSound();
			void setSpeed(float s);
		};
	}
}