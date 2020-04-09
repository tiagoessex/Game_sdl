

#include "TSound.h"
//#include <windows.h>

TSound::TSound(string filename)
{
	//Beep(523,100);

	sound = Mix_LoadWAV(filename.c_str());
	setVolume(50);
}

TSound::~TSound()
{
	//Beep(250,100);
	Mix_FreeChunk(sound);
}

/*
int TSound::play(int times)
{
	return Mix_PlayChannel(1, sound, times);
}
*/

// play sound n times
int TSound::play(int times)
{
	return Mix_PlayChannel(channel, sound, times);
}

int TSound::playTimed( int times, int ticks)
{
	return Mix_PlayChannelTimed(channel, sound, times, ticks);
}


int TSound::playFaded(int times, int ms)
{
	return Mix_FadeInChannel(channel, sound, times, ms);
}


int TSound::playTimedFaded( int times, int ms, int ticks)
{
	return Mix_FadeInChannelTimed(channel, sound, times, ms, ticks);
}


int TSound::setVolume(int volume)
{
	return Mix_VolumeChunk(sound, volume);
}

Mix_Chunk* TSound::getSound()
{
	return sound;
}

void TSound::pause()
{
	Mix_Pause(channel);
}

void TSound::resume()
{
	Mix_Resume(channel);
}


int TSound::stop()
{
	return Mix_HaltChannel(channel);
}

int TSound::stopWithDelay( int ticks)
{
	return Mix_ExpireChannel(channel, ticks);
}

int TSound::stopWithFade(int ms)
{
	return Mix_FadeOutChannel(channel, ms);
}

void TSound::setChannel(int channel)
{
	this->channel = channel;
}

int TSound::getChannel()
{
	return channel;
}

bool TSound::isPlaying()
{
	if (Mix_Playing(channel))
		return true;
	else
		return false;
}

bool TSound::isPaused()
{
	if (Mix_Paused(channel))
		return true;
	else
		return false;
}

Mix_Fading TSound::isFading()
{
	return Mix_FadingChannel(channel);
}
