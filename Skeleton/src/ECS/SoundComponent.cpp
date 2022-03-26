#include "SoundComponent.h"
#include <fstream>
#include <fmod.hpp>
#include <Sound.h>
#include <iostream>

SoundComponent::SoundComponent()
{

}

SoundComponent::~SoundComponent()
{

}

void SoundComponent::createSound(SoundSystemClass* manager, const char* pFile, int channel_)
{
	soundMngr = manager;
	channel = channel_;
	soundMngr->createSound(&sound, pFile, channel);
}

void SoundComponent::playSound(soundType groupChannel, bool bLoop)
{
	soundMngr->playSound(sound, groupChannel, bLoop);
}

void SoundComponent::releaseSound()
{
	soundMngr->releaseSound(channel);
}

void SoundComponent::setSpeed(float s)
{
	soundMngr->setSpeed(channel, s);
}
