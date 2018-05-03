#ifndef GAMEHANDLER_H_INCLUDED
#define GAMEHANDLER_H_INCLUDED

#include "SDL.h"
#undef main
#include <iostream>
#include <string>
#include <sstream>
#include "../GameObjects/Player.h"
#include "Text.h"

class GameHandler
{
public:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	static int score;
private:
	const enum GAME_STATE { RUNNING, STARTSCREEN, GAMEOVER, PAUSED };

	const char* GAME_NAME = "Space Invaders 2018";

	const int GAME_DELAY = 1000 / 60;

	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	GAME_STATE gameState;

	Player* player;

	Uint64 dtNow, dtLast;
	static double deltaTime;

	std::stringstream m_scorestream;

	void Update();
	void Draw();
	void Logic();
	void Input();
	void UpdateDeltaTime();
	void ChangeGameState(GameHandler::GAME_STATE state);

public:
	GameHandler();
	~GameHandler();
	void Init();

	static double getDeltaTime();
	
};

#endif
