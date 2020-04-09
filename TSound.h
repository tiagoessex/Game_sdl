#pragma once

			
  
#ifndef TSOUND_H_
#define TSOUND_H_

#include "SDL_mixer.h"
#include <string>

using namespace std;

class TSound
{
	public:
		//loads a new sound with volume 50
		TSound(string filename);

		// frees mem
		virtual ~TSound();

		
		// play sound n times | -1 => inf
		// use this one if the system assigns automaticcaly the channels
		// 0 -> MIX_MAX_VOLUME times
		// 0 -> 1 time
		int play(int times);

		// play sound n times | -1 => inf
		//int play(int canal, int times);

		// ticks -> number of ticks ms that the sound will be reproduzed
		int playTimed(int times, int ticks);

		// it takes from 0 to ms to fade
		int playFaded(int times, int ms);

		// it takes from ticks to ms to fade until then, plays normally
		int playTimedFaded(int times, int ms, int ticks);

		// return sound
		Mix_Chunk* getSound();

		// sets volume - (0-128)
		// 0 - MIX_MAX_VOLUME
		int setVolume(int volume);

		// if channel -1 => all channels pauses
		void pause();

		// if channel -1 => all channels resumes
		void resume();

		// stop sound
		int stop();

		// stops channel after a delay (ticks)
		int stopWithDelay( int ticks);

		// channel fades and then stops
		int stopWithFade( int ms);

		void setChannel(int channel);
		int getChannel();

		bool isPlaying();

		bool isPaused();

		/* returns:
				MIX_NO_FADING - isn’t being faded
				MIX_FADING_OUT - is fading out
				MIX_FADING_IN - is fading in
		*/
		Mix_Fading isFading();
		
	private:
		Mix_Chunk* sound;		
		int channel;
};





#endif
