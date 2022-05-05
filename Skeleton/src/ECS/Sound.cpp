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
			soundRoute = "./resources/Sounds/" + sf.getString("soundName");

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
			hasToPlay = sf.getBool("playNow");
			sf.tryGetFloat("volume", volume);
		}

		void Sound::init()
		{
			soundMngr = LoveEngine::Audio::SoundManager::getInstance();
			soundMngr->createSound(&sound, soundRoute.c_str(), channel);
			if (hasToPlay) playSound();
		}

		void Sound::playSound()
		{
			soundMngr->playSound(sound, (int)groupChannel, bLoop);

			setVolume(volume);
			
			hasChannel = true;
		}

		void Sound::releaseSound()
		{
			soundMngr->releaseSound(sound);
			hasChannel = false;
		}

		void Sound::setSpeed(float s)
		{
			soundMngr->setSpeed(sound, s);
		}
		
		Sound::~Sound()
		{
			releaseSound();
		}
		void Sound::pause(bool pause)
		{
			soundMngr->pauseSound(sound, pause);
		}

		void Sound::setVolume(float v)
		{
			volume = v;
			soundMngr->setVolume(sound, volume);
		}

		void Sound::onSceneUp()
		{
			if (hasChannel)
				pause(false);
			if (needRelease)
			{
				releaseSound();
				remove();
			}
		}

		void Sound::onSceneDown()
		{
			if (hasChannel)
				pause(true);
			if (needRelease)
			{
				releaseSound();
				remove();
			}
		}
	}



}

