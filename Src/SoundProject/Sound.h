#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>
#include <unordered_map>

typedef FMOD::Sound* SoundClass;
class SoundSystemClass //Clase que maneja el sonido a partir del uso de FMOD
{
private:
	std::unordered_map<int, SoundClass> soundsMap;
	std::unordered_map<int, SoundClass> effectsMap;
	std::unordered_map<int, SoundClass> voicesMap;
	std::unordered_map<int, SoundClass> enviormentMap;
public:
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
	SoundSystemClass();
	void createSound(SoundClass* pSound, const char* pFile,int channel, int mapType);
	void playSound(SoundClass pSound, bool bLoop = false);
	void releaseSound(int map, int channel);
	void setSpeed(int map, int channel,float s);
	void setVolumeChannel(int map, int channel, float volume);
};
