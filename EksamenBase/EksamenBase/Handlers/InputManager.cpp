#include "InputManager.h"

/// <summary>
/// Returns true if given key is being held down
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
bool InputManager::KeyHeld(SDL_Keycode key)
{
	return m_keyHeldMap[key];
}

/// <summary>
/// When a given key is pressed down
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
bool InputManager::KeyDown(SDL_Keycode key)
{
	if(m_keyPressedMap[key])
	{
		return false;
	}

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == key)
	{
		m_keyPressedMap[key] = true;
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
		m_keyPressedMap[key] = false;
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

/// <summary>
/// Updates whether or not a key is being held down
/// </summary>
void InputManager::UpdateStates()
{
	if (event.type == SDL_KEYUP)
	{
		m_keyHeldMap[event.key.keysym.sym] = false;
		m_keyPressedMap[event.key.keysym.sym] = false;
	}else if (event.type == SDL_KEYDOWN)
	{
		m_keyHeldMap[event.key.keysym.sym] = true;
	}

}
