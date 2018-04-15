#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <unordered_map>
#include "SDL.h"

class TextureManager
{
private:
	TextureManager() {};
	TextureManager(const TextureManager&) {};
	TextureManager& operator=(const TextureManager&) {};
	~TextureManager() {};

	SDL_Surface* tempSurface = nullptr;
	std::unordered_map<std::string, SDL_Texture*> loadedTexturesMap;

public:
	static TextureManager* getInstance()
	{
		static TextureManager* INSTANCE;
		return INSTANCE;
	}

	SDL_Texture * GetTexture(SDL_Renderer* renderer, std::string location);
	
	// Load surfaces into textures and keep the pointer to the textures in a hashmap, can look it up with imagepath w
};

#endif