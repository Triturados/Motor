#include "SoundComponent.h"
#include <fstream>
#include <fmod.hpp>
#include <Sound.h>
#include <iostream>
namespace LoveEngine {
	namespace ECS {

		void Sound::createSound(SoundManager* manager, const char* pFile, int channel_)
		{
			soundMngr = manager;
			channel = channel_;
			soundMngr->createSound(&sound, pFile, channel);
		}

		void Sound::playSound(soundType groupChannel, bool bLoop)
		{
			soundMngr->playSound(sound, groupChannel, bLoop);
		}

		void Sound::releaseSound()
		{
			soundMngr->releaseSound(channel);
		}

		void Sound::setSpeed(float s)
		{
			soundMngr->setSpeed(channel, s);
		}
	}
}
