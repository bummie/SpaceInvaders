#include "TextureManager.h"

TextureManager::TextureManager()
{
	tempSurface = nullptr;
}


TextureManager::~TextureManager()
{
	// Free textures?
}

/// <summary>
/// Takes the renderer and a path to an image
/// Will find given texture in the GPU memory
/// If it does not exist it will be created. 
/// </summary>
/// <param name="renderer"></param>
/// <param name="location"></param>
/// <returns>SDL_Texture*</returns>
SDL_Texture* TextureManager::GetTexture(SDL_Renderer* renderer, std::string location)
{

	tempSurface = SDL_LoadBMP(location.c_str);
	if (tempSurface == NULL) { return nullptr; }

	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (tempTexture == NULL) { return nullptr; }

	loadedTexturesMap.insert({ location, tempTexture });

	return loadedTexturesMap[location];
}
