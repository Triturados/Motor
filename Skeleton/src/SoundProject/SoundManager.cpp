#include "SoundManager.h"
#include <fmod_errors.h>
#include <string.h>
#include <fstream>
#include <Error_handling.h>
#include <SingletonInfo.h>

namespace LoveEngine {
	namespace Audio {
		SoundManager* SoundManager::instance = nullptr;

		SoundManager* SoundManager::getInstance()
		{
			return instance;
		}

		SoundManager::SoundManager()
		{
			if (instance != nullptr)
				LoveEngine::ErrorHandling::throwError(__PROJECT_NAME__, __LINE__,
					__FILENAME__, "Ya existe una instancia del SoundManager.");

			instance = this;

			fmod_error = FMOD::System_Create(&m_pSystem);
			throwFMODError(fmod_error, __LINE__);

			//Manejo de drivers del ordenador para evitar que se intente reproducir cuando no hay 
			int driverCount = 0;
			fmod_error = m_pSystem->getNumDrivers(&driverCount);
			throwFMODError(fmod_error, __LINE__);

			// Initialize our Instance with 36 Channels
			fmod_error = m_pSystem->init(36, FMOD_INIT_NORMAL, NULL);
			throwFMODError(fmod_error, __LINE__);

			//Creacion de los grupos de canales
			m_pSystem->createChannelGroup("Master", &master);
			m_pSystem->createChannelGroup("Effects", &effects);
			m_pSystem->createChannelGroup("Environment", &environment);
			m_pSystem->createChannelGroup("Music", &music);
			m_pSystem->createChannelGroup("Voices", &voices);

			//Añadimos los canales al master que es el que controla todo 
			master->addGroup(effects);	master->addGroup(music);
			master->addGroup(environment); 	master->addGroup(voices);

			channels.reserve(MaxCh);
			for (int i = 0; i < MaxCh; i++) channels.push_back(nullptr);
		}

		SoundManager::~SoundManager()
		{
			fmod_error = m_pSystem->release();
			throwFMODError(fmod_error, __LINE__);
		}

		void SoundManager::createSound(FMOD::SoundClass* pSound, const char* pFile, int channel)
		{
			fmod_error = m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
			throwFMODError(fmod_error, __LINE__);

			if (!std::ifstream(pFile)) throw std::exception("[Error en el proyecto SoundProject] : El archivo de sonido no existe o no se ha podido encontrar.");

			//Añadimos al mapa de sonidos generales un tupla somido canal
			std::pair<int, FMOD::SoundClass> sound(channel, *pSound);
			soundsMap.insert(sound);
		}

		void SoundManager::playSound(FMOD::SoundClass pSound, int groupChannel, bool bLoop)
		{
			if (!bLoop) {
				fmod_error = pSound->setMode(FMOD_LOOP_OFF);
				throwFMODError(fmod_error, __LINE__);
			}
			else
			{
				fmod_error = pSound->setMode(FMOD_LOOP_NORMAL);
				throwFMODError(fmod_error, __LINE__);

				pSound->setLoopCount(-1);
			}

			for (auto channel : channels) {
				bool isPlaying;
				channel->isPlaying(&isPlaying);

				if (isPlaying) continue;

				switch (groupChannel)
				{
				case 0: {
					fmod_error = m_pSystem->playSound(pSound, effects, false, &channel);
					throwFMODError(fmod_error, __LINE__);
					break;
				}
				case 1: {
					m_pSystem->playSound(pSound, environment, false, &channel);
					throwFMODError(fmod_error, __LINE__);
					break;
				}
				case 2: {
					m_pSystem->playSound(pSound, voices, false, &channel);
					throwFMODError(fmod_error, __LINE__);
					break;
				}
				case 3: {
					m_pSystem->playSound(pSound, music, false, &channel);
					throwFMODError(fmod_error, __LINE__);
					break;
				}
				default:
					break;
				}
				break;
			}
		}

		void SoundManager::releaseSound(int channel)
		{
			fmod_error = soundsMap.find(channel)->second->release();
			throwFMODError(fmod_error, __LINE__);
		};

		void SoundManager::setSpeed(int channel, float s)
		{
			fmod_error = soundsMap.find(channel)->second->setMusicSpeed(s);
			throwFMODError(fmod_error, __LINE__);
		}

		void SoundManager::setVolumeChannel(int channelGroup, float volume)
		{
			switch (channelGroup)
			{
			case 0: setVolume(master, volume); break;
			case 1: setVolume(effects, volume); break;
			case 2: setVolume(environment, volume); break;
			case 3: setVolume(voices, volume); break;
			case 4: setVolume(music, volume); break;
			default:
				break;
			}
		}

		void SoundManager::pauseSound()
		{
			bool paused; fmod_error = master->getPaused(&paused);
			throwFMODError(fmod_error, __LINE__);

			paused ? master->setPaused(true) : master->setPaused(false);
		}

		void SoundManager::setVolume(FMOD::ChannelGroup* group, float volume) {
			fmod_error = group->setVolume(volume);
			throwFMODError(fmod_error, __LINE__);
		}

		void SoundManager::throwFMODError(FMOD_RESULT result, int errorLine)
		{
			if (result != FMOD_OK) {
				LoveEngine::ErrorHandling::throwError(__PROJECT_NAME__, errorLine, __FILENAME__, FMOD_ErrorString(result));
			}
		}


	}
}
