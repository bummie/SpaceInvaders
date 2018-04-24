#include "SoundManager.h"
#include <iostream>
#include <string>

SoundManager::~SoundManager()
{
	// Free the sound effects
	for (auto sound : soundMap)
	{
		Mix_FreeChunk(sound.second);
	}

	//Free the music
	Mix_FreeMusic(music);

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

	LoadSounds();

	return true;
}

/// <summary>
/// Loads sound used in the game into memory
/// </summary>
void SoundManager::LoadSounds()
{
	// Game music
	music = Mix_LoadMUS("Resources/Sound/music.wav");
	if (music == NULL)
	{
		std::cout << "Music could not be loaded: " << Mix_GetError() << std::endl;
	}

	// Laser being shot
	soundMap["Laser"] = Mix_LoadWAV("Resources/Sound/laser.wav");
	if(soundMap["Laser"] == NULL)
	{
		std::cout << "Sound could not be loaded: " << Mix_GetError() << std::endl;
	}

	// Explosion
	soundMap["Explosion"] = Mix_LoadWAV("Resources/Sound/explosion.wav");
	if (soundMap["Explosion"] == NULL)
	{
		std::cout << "Sound could not be loaded: " << Mix_GetError() << std::endl;
	}

}

/// <summary>
/// Plays a sound with the given name
/// </summary>
/// <param name="soundName"></param>
void SoundManager::PlaySound(std::string soundName)
{
	auto iterator = soundMap.find(soundName);

	if (iterator == soundMap.end())
	{
		std::cout << "Could not find sound with name " << soundName << std::endl;
		return;
	}

	if (Mix_PlayChannel(-1, soundMap[soundName], 0) == -1)
	{
		std::cout << "Failed to play sound" << soundName << std::endl;
		return;
	}
}

/// <summary>
/// Starts the game music
/// </summary>
void SoundManager::PlayMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		if (Mix_PlayMusic(music, -1) == -1)
		{
			return;
		}
	}
	else if (Mix_PausedMusic() == 1)
	{
		//Resume the music
		Mix_ResumeMusic();
	}
}

/// <summary>
/// Stops the game music
/// </summary>
void SoundManager::StopMusic()
{
	Mix_PauseMusic();
}