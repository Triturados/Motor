#include "Sound.h"


SoundSystemClass::SoundSystemClass()
{
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		// Report Error
		return;
	}
	//Manejo de drivers del ordenador para evitar que se intente reproducir cunaod no hay 
	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);
	if (driverCount == 0)
	{
		// Report Error
		return;
	}
	// Initialize our Instance with 36 Channels
	m_pSystem->init(36, FMOD_INIT_NORMAL, NULL);

	//Creacion de los grupos de canales
	m_pSystem->createChannelGroup("Master", &master);
	m_pSystem->createChannelGroup("Effects", &effects);
	m_pSystem->createChannelGroup("Environment", &environment);
	m_pSystem->createChannelGroup("Music", &music);
	m_pSystem->createChannelGroup("Voices", &voices);

	//A�adimos los canales al master que es el que controla todo 
	master->addGroup(effects);	master->addGroup(music);
	master->addGroup(environment); 	master->addGroup(voices);
}

void SoundSystemClass::createSound(SoundClass* pSound, const char* pFile, int channel)
{
	m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);


	//A�adimos al mapa de sonidos generales un tupla somido canal
	std::pair<int, SoundClass> sound(channel, *pSound);
	soundsMap.insert(sound);
}

void SoundSystemClass::playSound(SoundClass pSound, int groupChannel, bool bLoop)
{
	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	int numOfChans = sizeof(channels);
	for (int i = 0; i < numOfChans; i++) {
		bool isPlaying;
		channels[i]->isPlaying(&isPlaying);

		if (isPlaying) continue;

		switch (groupChannel)
		{
		case 1: m_pSystem->playSound(pSound, effects, false, &channels[i]); break;
		case 3:	m_pSystem->playSound(pSound, environment, false, &channels[i]); break;
		case 4: m_pSystem->playSound(pSound, voices, false, &channels[i]); break;
		case 5: m_pSystem->playSound(pSound, music, false, &channels[i]); break;
		default:
			break;
		}
	}
}

void SoundSystemClass::releaseSound(int channel)
{
	soundsMap.find(channel)->second->release();
};

void SoundSystemClass::setSpeed(int channel, float s)
{
	soundsMap.find(channel)->second->setMusicSpeed(s);
}

void SoundSystemClass::setVolumeChannel(int channelGroup, float volume)
{
	switch (channelGroup)
	{
	case 0: master->setVolume(volume); break;
	case 1: effects->setVolume(volume); break;
	case 3: environment->setVolume(volume); break;
	case 4: voices->setVolume(volume); break;
	case 5: music->setVolume(volume); break;
	default:
		break;
	}
}

void SoundSystemClass::pauseSound()
{
	bool paused; master->getPaused(&paused);
	paused ? master->setPaused(true) : master->setPaused(false);
}

