#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
#include <unordered_map>

typedef FMOD::Sound* SoundClass;

class SoundSystemClass //Clase que maneja el sonido a partir del uso de FMOD
{
private:
	const int MaxCh = 36;
	std::unordered_map<int, SoundClass> soundsMap;
	std::vector<FMOD::Channel*> channels;
	std::vector<FMOD::ChannelGroup*> channelGroups;
	FMOD::ChannelGroup *effects, *voices, *environment, *music, *master;

public:
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
	SoundSystemClass();
	void createSound(SoundClass* pSound, const char* pFile,int channel);
	void playSound(SoundClass pSound, int groupChannel, bool bLoop = false);
	void releaseSound(int channel);
	void setSpeed(int channel,float s);
	void setVolumeChannel(int channelGroup, float volume);
	void pauseSound();
};
