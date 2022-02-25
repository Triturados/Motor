//#include "../OgreProject/Saludador.h"
#include <Sound.h>
#include <iostream>

void main()
{
	//sound("aaaa");

	int a;
	std::cin >> a;
}
void useSystemSound()
{
	SoundSystemClass sound = SoundSystemClass(); //Inicializacion 

	// Create a sample sound
	SoundClass soundSample;
	sound.createSound(&soundSample, "C:\\mysound.wav");

	// Play the sound, with loop mode
	sound.playSound(soundSample, true);

	// Do something meanwhile...

	// Release the sound
	sound.releaseSound(soundSample);
}