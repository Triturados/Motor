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

	m_pSystem->createChannelGroup("Master", &master);
	m_pSystem->createChannelGroup("Effects", &effects);
	m_pSystem->createChannelGroup("Environment", &environment);
	m_pSystem->createChannelGroup("Music", &music);
	m_pSystem->createChannelGroup("Voices", &voices);

	master->addGroup(effects);	master->addGroup(music);
	master->addGroup(environment); 	master->addGroup(voices);
}

void SoundSystemClass::createSound(SoundClass* pSound, const char* pFile, int channel)
{
	m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound); //El segundo parametro antes era :_HARDWARE pero en la documentacion no etsbaa
	//Lo unico que me cuadraba de la documentacion es el 3D aunque bastante xd la verdad

	//Habria que hacer un switch para segun añadamos sonidos a los distintos mapas ,distinguir entre mapas para hacer el insert solo una vez
	std::pair<int, SoundClass> sound(channel, *pSound);
	soundsMap.insert(sound);
}

void SoundSystemClass::playSound(SoundClass pSound, bool bLoop)
{
	if (!bLoop)
		pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	//Los parametros que acepta el metodo son :
	//Sonido a Reproducir / Grupos de Canales (bastante wtf la verdad) / Si esta o no pausado / Canal por el que se reproduce (por defecto 0)
	m_pSystem->playSound(pSound, 0, false, 0); //He cambiado la sintaxis de como venia por que si no daba error

}

void SoundSystemClass::releaseSound(int channel)
{
	soundsMap.find(channel)->second->release();
};

void SoundSystemClass::setSpeed(int channel,float s)
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


//Para el de pausar no encuentro como se hace con el enum del FMOD_CHANNEL
//pero seria llamar con ese enum tanto al setPaused como al get Paused y et devuelven en el estado en el que estan
