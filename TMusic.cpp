
#include "TMusic.h"

TMusic::TMusic(std::string filename)
{
	music=Mix_LoadMUS(filename.c_str());
	setVolume(50);
}

// frees mem
TMusic::~TMusic()
{
	Mix_FreeMusic(music);
}

		
// play the music loop times | -1 => inf
int TMusic::play(int loop)
{
	return Mix_PlayMusic(music, loop);
}



// return music
Mix_Music* TMusic::getSound()
{
	return music;
}

// sets volume - (0-128)
int TMusic::setVolume(int volume)
{
	return Mix_VolumeMusic(volume);
}

void TMusic::pause()
{
	Mix_PauseMusic();
}

void TMusic::resume()
{
	Mix_ResumeMusic();
}

int TMusic::stop()
{
	return Mix_HaltMusic();
}

void TMusic::rewind()
{
	Mix_RewindMusic();
}

int TMusic::setMusicPostion(double pos)
{
	return Mix_SetMusicPosition(pos);
}


int TMusic::fadeOut(int time)
{
	return Mix_FadeOutMusic(time);
}

int TMusic::fadeIn(int loops, int time)
{
	return Mix_FadeInMusic(music, loops, time);
}

bool TMusic::isPlaying()
{
	if (Mix_PlayingMusic())
		return true;
	else
		return false;
}

bool TMusic::isPaused()
{
	if (Mix_PausedMusic())
		return true;
	else
		return false;
}

Mix_Fading TMusic::isFadding()
{
	return Mix_FadingMusic();
}