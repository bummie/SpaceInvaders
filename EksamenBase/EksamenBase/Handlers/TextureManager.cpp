#include "TextureManager.h"
#include <iostream>

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
	auto iterator = loadedTexturesMap.find(location);

	if(iterator == loadedTexturesMap.end())
	{
		std::cout << "Texture not loaded, loading now.." << std::endl;
		tempSurface = SDL_LoadBMP(location.c_str());
		if (tempSurface == NULL) { return nullptr; }
		
		// Makes white pixels transparent
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0, 0));
	
		SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (tempTexture == NULL) { return nullptr; }

		SDL_FreeSurface(tempSurface);
		tempSurface = nullptr;

		loadedTexturesMap.insert({ location, tempTexture });
	}

	return loadedTexturesMap[location];
}
