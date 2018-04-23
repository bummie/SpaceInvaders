#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include "SDL.h"
#include "SDL_mixer.h"
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

public:
	bool Init();

};

#endif