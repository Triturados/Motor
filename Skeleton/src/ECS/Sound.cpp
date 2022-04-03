#include "Sound.h"
#include <fstream>
#include <fmod.hpp>
#include <SoundManager.h>
#include <iostream>
namespace LoveEngine {
	namespace ECS {

		void Sound::createSound(const char* pFile, int channel_)
		{
			channel = channel_;
			soundMngr = LoveEngine::Audio::SoundManager::instance;
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
