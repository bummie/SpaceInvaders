#include "SoundManager.h"
#include <iostream>

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

/// <summary>
/// Inits the soundmanager
/// </summary>
bool SoundManager::Init()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Could not load SDL_Mixer" << std::endl;
		return false;
	}
	test = Mix_LoadWAV(".\Resources\Sound\laser.wav");
	
	if(test == NULL)
	{
		std::cout << "SOUND NOT LOOADEEED" << std::endl;
	}

	return true;
}

/// <summary>
/// Plays loaded sound
/// </summary>
void SoundManager::PlaySound()
{
	if (Mix_PlayChannel(-1, test, 0) == -1)
	{
		std::cout << "Failed to play sound" << std::endl;
	}
}



