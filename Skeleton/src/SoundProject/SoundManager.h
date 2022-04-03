#pragma once
#include <unordered_map>
#include <fmod.hpp>
#include <../Export.h>
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
namespace LoveEngine {
	namespace Audio {
		class lovexport SoundManager //Clase que maneja el sonido a partir del uso de FMOD
		{
		private:
			const int MaxCh = 36;
			std::unordered_map<int, FMOD::SoundClass> soundsMap;
			std::vector<FMOD::Channel*> channels;
			std::vector<FMOD::ChannelGroup*> channelGroups;
			FMOD::ChannelGroup* effects, * voices, * environment, * music, * master;

			void setVolume(FMOD::ChannelGroup* group, float volume);

			//Errores
			FMOD_RESULT fmod_error;
			void throwFMODError(FMOD_RESULT result, int errorLine);


		public:
			// Pointer to the FMOD instance
			FMOD::System* m_pSystem;

			static SoundManager* instance;

			SoundManager();
			~SoundManager();

			void createSound(FMOD::SoundClass* pSound, const char* pFile, int channel);
			void playSound(FMOD::SoundClass pSound, int groupChannel, bool bLoop = false);
			void releaseSound(int channel);
			void setSpeed(int channel, float s);
			void setVolumeChannel(int channelGroup, float volume);
			void pauseSound();
		};

	}
}
