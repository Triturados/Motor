#include <Sound.h>
#include <iostream>
#include <OgreRenderer.h>

void useSystemSound()
{
	SoundSystemClass sound = SoundSystemClass(); //Inicializacion 

	// Create a sample sound
	SoundClass soundSample;
	sound.createSound(&soundSample, "FMOD/Sonidos/sonido.wav",0);

	// Play the sound, with loop mode
	sound.playSound(soundSample, true);

	// Do something meanwhile...

	int a;
	std::cin >> a;

	// Release the sound
	sound.releaseSound(0);


	OgreRenderer main = OgreRenderer();
	main.exampleScene();

	while (main.update()) {};

}

void main()
{
	//sound("aaaa");
	useSystemSound();
}
