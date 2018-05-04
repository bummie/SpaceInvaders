#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include "SDL.h"
#include "SDL_mixer.h"
#include <unordered_map>

class SoundManager
{

public:
	static SoundManager& getInstance()
	{
		static SoundManager instance;
		return instance;
	}

	~SoundManager();
private:
	SoundManager() {}
	SoundManager(SoundManager const&);
	void operator=(SoundManager const&);

	std::unordered_map<std::string, Mix_Chunk*> m_soundMap;
	Mix_Music* m_music;
	bool m_isPlaying;
	void LoadSounds();

public:
	bool Init();
	void PlaySound(std::string soundName);
	void PlayMusic();
	void StopMusic();
	bool MusicPlaying();

};

#endif