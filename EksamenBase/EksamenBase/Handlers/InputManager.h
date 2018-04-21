#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include <unordered_map>
#include "SDL.h"

class InputManager
{

public:
	static InputManager& getInstance()
	{
		static InputManager instance;
		return instance;
	}

private:
	InputManager() {}
	InputManager(InputManager const&);
	void operator=(InputManager const&);

	std::unordered_map<SDL_Keycode, bool> keyHeldMap;
	std::unordered_map<SDL_Keycode, bool> keyPressedMap;

public:
	bool KeyHeld(SDL_Keycode key);
	bool KeyDown(SDL_Keycode key);
	bool KeyUp(SDL_Keycode key);
	bool ExitGameRequested();
	void UpdateStates();
	SDL_Event event;
	const Uint8 *keyState;

};

#endif