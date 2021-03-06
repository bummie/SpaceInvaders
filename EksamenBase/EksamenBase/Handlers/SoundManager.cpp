#include "SoundManager.h"
#include <iostream>
#include <string>

SoundManager::~SoundManager()
{
	// Free the sound effects
	for (auto sound : m_soundMap)
	{
		Mix_FreeChunk(sound.second);
	}

	//Free the music
	Mix_FreeMusic(m_music);

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
		m_isPlaying = false;
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
	m_music = Mix_LoadMUS("Resources/Sound/music.wav");
	if (m_music == NULL)
	{
		std::cout << "Music could not be loaded: " << Mix_GetError() << std::endl;
	}

	// Laser being shot
	m_soundMap["Laser"] = Mix_LoadWAV("Resources/Sound/laser.wav");
	if(m_soundMap["Laser"] == NULL)
	{
		std::cout << "Sound could not be loaded: " << Mix_GetError() << std::endl;
	}

	// Explosion
	m_soundMap["Explosion"] = Mix_LoadWAV("Resources/Sound/explosion.wav");
	if (m_soundMap["Explosion"] == NULL)
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
	auto iterator = m_soundMap.find(soundName);

	if (iterator == m_soundMap.end())
	{
		std::cout << "Could not find sound with name " << soundName << std::endl;
		return;
	}

	if (Mix_PlayChannel(-1, m_soundMap[soundName], 0) == -1)
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
	m_isPlaying = true;

	if (Mix_PlayingMusic() == 0)
	{
		if (Mix_PlayMusic(m_music, -1) == -1)
		{
			return;
		}
	}
	else if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
}

/// <summary>
/// Stops the game music
/// </summary>
void SoundManager::StopMusic()
{
	Mix_PauseMusic();
	m_isPlaying = false;
}

/// <summary>
/// Returns true if music is playing
/// </summary>
/// <returns></returns>
bool SoundManager::MusicPlaying()
{
	return m_isPlaying;
}
