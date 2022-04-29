#include "Sound.h"
#include <fstream>
#include <fmod.hpp>
#include <SoundManager.h>
#include <iostream>
#include <StringFormatter.h>

namespace LoveEngine {
	namespace ECS {

		

		void Sound::receiveMessage(Utilities::StringFormatter& sf)
		{
			soundRoute = "./FMOD/Sonidos/" + sf.getString("soundName");

			int channel;
			if (sf.tryGetInt("channel", channel)) {
				groupChannel = static_cast<soundType>(channel);
			}
			else {
				std::string name;
				if (sf.tryGetString("channel", name))
				{
					if (name == "environment") {
						groupChannel = soundType::environment;
					}
					else if (name == "voices") {
						groupChannel = soundType::voices;
					}
					else if (name == "music") {
						groupChannel = soundType::music;
					}
					else {
						groupChannel = soundType::effects;
					}
				}
			}
			bLoop = sf.getBool("loop");
		}

		void Sound::init()
		{
			soundMngr = LoveEngine::Audio::SoundManager::getInstance();
			soundMngr->createSound(&sound, soundRoute.c_str(), channel);
			playSound();
		}

		void Sound::playSound()
		{
			soundMngr->playSound(sound, (int) groupChannel, bLoop);
		}

		void Sound::releaseSound()
		{
			soundMngr->releaseSound(sound);
		}

		void Sound::setSpeed(float s)
		{
			soundMngr->setSpeed(sound, s);
		}

		void Sound::pause(bool pause)
		{
			soundMngr->pauseSound(sound, pause);
		}

		void Sound::setVolume(float volume)
		{
			soundMngr->setVolume(sound, volume);
		}
	}
}
