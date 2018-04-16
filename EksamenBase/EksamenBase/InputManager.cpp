#include "InputManager.h"

/// <summary>
/// When a given key is pressed down
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
bool InputManager::KeyDown(SDL_Keycode key)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == key)
	{
		return true;
	}

	return false;
}

/// <summary>
/// When a given key is being released
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
bool InputManager::KeyUp(SDL_Keycode key)
{
	if (event.type == SDL_KEYUP && event.key.keysym.sym == key)
	{
		return true;
	}

	return false;
}

/// <summary>
/// When the player push the cross in the window
/// </summary>
/// <returns></returns>
bool InputManager::ExitGameRequested()
{
	if (event.type == SDL_QUIT)
	{
		return true;
	}
	return false;
}
