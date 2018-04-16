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


public:
	bool KeyDown(SDL_Keycode key);
	bool KeyUp(SDL_Keycode key);
	bool ExitGameRequested();
	SDL_Event event;


};

#endif