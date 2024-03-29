#pragma once

#include "EngineErrors.h"
#include <SDL\SDL_mixer.h> //tutorial used this
#include <string>
#include <map>


namespace Engine {





	/* tutorial code*/
	class SoundEffect {
	public:
		friend class AudioEngine;
		//loops -1 is loop forever
		//otherwise x+1 times
		void play(int loops = 0);
	private:
		Mix_Chunk* m_chunk = nullptr;
	};

	class Music {
	public:
		friend class AudioEngine;

		//loops -1 is loop forever
		//otherwise x times
		void play(int loops = 1);
		static void pause();
		static void stop();
		static void resume();
	private:
		Mix_Music* m_music = nullptr;
	};

	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);

	private:
		bool m_isInitialized = false;
		std::map<std::string, Mix_Chunk*> m_effectMap;
		std::map<std::string, Mix_Music*> m_musicMap;
	};
	/**/
}