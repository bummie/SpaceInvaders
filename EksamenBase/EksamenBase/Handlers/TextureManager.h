#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <unordered_map>
#include "SDL.h"

class TextureManager
{

public:
	static TextureManager& getInstance()
	{
		static TextureManager instance;
		return instance;
	}

	SDL_Texture * GetTexture(SDL_Renderer* renderer, std::string location);

private:
	TextureManager() {}
	TextureManager(TextureManager const&);
	void operator=(TextureManager const&);

public:
	//TextureManager(TextureManager const&) = delete;
	//void operator=(TextureManager const&) = delete;


	SDL_Surface* tempSurface = nullptr;
	std::unordered_map<std::string, SDL_Texture*> loadedTexturesMap;

};

#endif