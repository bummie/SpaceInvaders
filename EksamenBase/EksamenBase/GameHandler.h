#ifndef GAMEHANDLER_H_INCLUDED
#define GAMEHANDLER_H_INCLUDED

#include "SDL.h"
#include <iostream>

class GameHandler
{
public:
	const enum GAME_STATE { RUNNING, GAMEOVER, PAUSED };

	GameHandler();
	~GameHandler();
	void Init();
	
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	SDL_Window* _window;
	SDL_Surface* _screenSurface;
	GAME_STATE _gameState;

	void Update();
	void Draw();
};

#endif
