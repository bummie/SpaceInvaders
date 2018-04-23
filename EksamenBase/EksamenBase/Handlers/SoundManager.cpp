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

	return true;
}

