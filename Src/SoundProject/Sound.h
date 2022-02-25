#pragma once
#include "..\inc\fmod.hpp"
#include "..\inc\fmod_errors.h"
#include <iostream>

typedef FMOD::Sound* SoundClass;
class SoundSystemClass //Clase que maneja el sonido a partir del uso de FMOD
{
public:
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
	SoundSystemClass();
	void createSound(SoundClass* pSound, const char* pFile);
	void playSound(SoundClass pSound, bool bLoop = false);
	void releaseSound(SoundClass pSound);

};
