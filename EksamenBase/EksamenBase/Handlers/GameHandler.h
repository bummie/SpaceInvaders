#ifndef GAMEHANDLER_H_INCLUDED
#define GAMEHANDLER_H_INCLUDED

#include "SDL.h"
#undef main
#include <iostream>
#include <string>
#include "../GameObjects/Player.h"
#include "Text.h"

class GameHandler
{
private:
	const enum GAME_STATE { RUNNING, GAMEOVER, PAUSED };

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const char* GAME_NAME = "BaseGameEksamen";

	const int GAME_DELAY = 1000 / 60;

	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	GAME_STATE gameState;

	Player* player;

	Uint64 dtNow, dtLast;
	static double deltaTime;

	void Update();
	void Draw();
	void Logic();
	void Input();
	void UpdateDeltaTime();

public:
	GameHandler();
	~GameHandler();
	void Init();

	static double getDeltaTime();
	
};

#endif
