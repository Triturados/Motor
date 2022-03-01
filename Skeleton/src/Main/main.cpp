//#include "../OgreProject/Saludador.h"
#include <Sound.h>
#include <iostream>

void useSystemSound()
{
	SoundSystemClass sound = SoundSystemClass(); //Inicializacion 

	// Create a sample sound
	SoundClass soundSample;
	sound.createSound(&soundSample, "../../../Recursos/Sonidos/sonido.wav",0);

	// Play the sound, with loop mode
	sound.playSound(soundSample, true);

	// Do something meanwhile...

	int a;
	std::cin >> a;

	// Release the sound
	sound.releaseSound(0);
}

void main()
{
	//sound("aaaa");
	useSystemSound();
}
