#ifndef GAMEHANDLER_H_INCLUDED
#define GAMEHANDLER_H_INCLUDED

#include "SDL.h"
#undef main
#include <iostream>
#include <string>
#include "GameObject.h"

class GameHandler
{
private:
	const enum GAME_STATE { RUNNING, GAMEOVER, PAUSED };

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const char* GAME_NAME = "BaseGameEksamen";

	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	GAME_STATE gameState;
	SDL_Event e;

	GameObject* player;

	void Update();
	void Draw();
	void Logic();
	void Input();

public:
	GameHandler();
	~GameHandler();
	void Init();
	
};

#endif
