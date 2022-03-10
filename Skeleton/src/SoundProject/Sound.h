#pragma once
#include <unordered_map>

namespace FMOD {
	class System;
	class Sound;
	class ChannelControl;
	class Channel;
	class ChannelGroup;
	class Sound;
	typedef Sound* SoundClass;
}

class SoundSystemClass //Clase que maneja el sonido a partir del uso de FMOD
{
private:
	const int MaxCh = 36;
	std::unordered_map<int, FMOD::SoundClass> soundsMap;
	std::vector<FMOD::Channel*> channels;
	std::vector<FMOD::ChannelGroup*> channelGroups;
	//Efectos 15 canales - Voces 5 canales - Entorno 5 canales - Musica 2 canales
	FMOD::ChannelGroup *effects, *voices, *environment, *music, *master;

public:
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
	SoundSystemClass();
	void createSound(FMOD::SoundClass* pSound, const char* pFile,int channel);
	void playSound(FMOD::SoundClass pSound, int groupChannel, bool bLoop = false);
	void releaseSound(int channel);
	void setSpeed(int channel,float s);
	void setVolumeChannel(int channelGroup, float volume);
	void pauseSound();
};
