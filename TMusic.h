#pragma once

// formats: MOD, OGG, MP3
			
  
#ifndef TMUSIC_H_
#define TMUSIC_H_


#include "SDL_mixer.h"
#include <string>


class TMusic
{
	public:
		//loads a new music with volume 50
		TMusic(std::string filename);

		// frees mem
		virtual ~TMusic();

		
		// play the music loop times | -1 => inf
		// returns channel
		int play(int loop);

		// returns music
		Mix_Music* getSound();

		// sets volume - (0-MIX_MAX_VOLUME = 128)
		int setVolume(int volume);

		void pause();

		void resume();

		int stop();

		void rewind();

		// sets the beginning of the music
		// pos depends on music:
		//			MOD - pos is the pattern number and fractions are dropped
		//			OGG - pos is the number of seconds from the beginning of the music
		//			MP3 - pos is the number of seconds to jump forward.
		int setMusicPostion(double pos);

		// starts music in time ms with fade up
		int fadeIn(int loops, int time);

		// fade music out in time ms
		int fadeOut(int time);

		bool isPlaying();
	
		bool isPaused();

		/* returns:
				MIX_NO_FADING
				MIX_FADING_OUT
				MIX_FADING_IN
		*/
		Mix_Fading isFadding();
		
	private:
		Mix_Music* music;		
};


#endif
