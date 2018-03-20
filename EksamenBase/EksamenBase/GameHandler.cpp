#include "GameHandler.h"

GameHandler::GameHandler()
{
	_window = NULL;
	_screenSurface = NULL;
	_gameState = GAME_STATE::RUNNING;
}

void GameHandler::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError();
		return;
	}

	_window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (_window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	_screenSurface = SDL_GetWindowSurface(_window);

	//Fill the surface white
	SDL_FillRect(_screenSurface, NULL, SDL_MapRGB(_screenSurface->format, 0x00, 0x00, 0x00));

	//Update the surface
	SDL_UpdateWindowSurface(_window);

	//Wait two seconds
	SDL_Delay(2000);

	Update();
}

void GameHandler::Update()
{
	// Game loop
	while (_gameState != GAME_STATE::GAMEOVER)
	{
		Input();
		Draw();
	}
}

void GameHandler::Draw()
{
}

void GameHandler::Input()
{
}

GameHandler::~GameHandler()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}