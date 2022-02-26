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
}
void SoundSystemClass::createSound(SoundClass* pSound, const char* pFile, int channel)
{
    m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound); //El segundo parametro antes era :_HARDWARE pero en la documentacion no etsbaa
    //Lo unico que me cuadraba de la documentacion es el 3D aunque bastante xd la verdad

    soundsMap.insert(channel, pSound>);
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
    m_pSystem->playSound(pSound, 0, false,0); //He cambiado la sintaxis de como venia por que si no daba error

}


void SoundSystemClass::releaseSound(SoundClass pSound)
{
    pSound->release();
}

void SoundSystemClass::pauseSound(SoundClass* pSound)
{
}
