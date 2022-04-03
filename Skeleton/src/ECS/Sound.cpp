#include "Sound.h"
#include <fstream>
#include <fmod.hpp>
#include <SoundManager.h>
#include <iostream>
#include <StringFormater.h>

namespace LoveEngine {
	namespace ECS {

		void Sound::receiveValues(int gChannel, float f, Component* playerPos, GameObject* g)
		{
			groupChannel = static_cast<soundType>(gChannel);
		}

		void Sound::receiveMessage(std::string s)
		{
			StringFormatter sTf(s);
			soundRoute = "./FMOD/Sonidos/" + sTf.getString("soundName");
			bLoop = sTf.getBool("bLoop");
		}

		void Sound::init()
		{
			soundMngr = LoveEngine::Audio::SoundManager::instance;
			soundMngr->createSound(&sound, soundRoute.c_str(), channel);
		}

		void Sound::playSound()
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
