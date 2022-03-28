#pragma once
#include <unordered_map>
#include <fmod.hpp>

namespace FMOD {
	class System;
	class Sound;
	class ChannelControl;
	class Channel;
	class ChannelGroup;
	class Sound;
	class FMOD_RESULT;
	typedef Sound* SoundClass;
}

class SoundManager //Clase que maneja el sonido a partir del uso de FMOD
{
private:
	const int MaxCh = 36;
	std::unordered_map<int, FMOD::SoundClass> soundsMap;
	std::vector<FMOD::Channel*> channels;
	std::vector<FMOD::ChannelGroup*> channelGroups;
	FMOD::ChannelGroup *effects, *voices, *environment, *music, *master;

	FMOD_RESULT fmod_error;

public:
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
	SoundManager();
	void createSound(FMOD::SoundClass* pSound, const char* pFile,int channel);
	void playSound(FMOD::SoundClass pSound, int groupChannel, bool bLoop = false);
	void releaseSound(int channel);
	void setSpeed(int channel,float s);
	void setVolumeChannel(int channelGroup, float volume);
	void pauseSound();
	void throwFMODError(FMOD_RESULT result);
};
