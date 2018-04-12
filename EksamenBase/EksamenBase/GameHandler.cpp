#include "GameHandler.h"

GameHandler::GameHandler()
{
	_window = NULL;
	_screenSurface = NULL;
	_gameState = GAME_STATE::RUNNING;
}

/// <summary>
/// Inits SDL
/// </summary>
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

	Update();
}

/// <summary>
/// Game loop
/// </summary>
void GameHandler::Update()
{
	// Game loop
	while (_gameState != GAME_STATE::GAMEOVER)
	{
		Input();
		Draw();
		SDL_Delay(33);
	}
}

/// <summary>
/// Draws to the window
/// </summary>
void GameHandler::Draw()
{

}

/// <summary>
/// Takes input
/// </summary>
void GameHandler::Input()
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			_gameState = GAME_STATE::GAMEOVER;
		} 
		else if (e.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				std::cout << "Up";
				break;

			case SDLK_DOWN:
				std::cout << "Down";
				break;

			case SDLK_LEFT:
				std::cout << "Left";
				break;

			case SDLK_RIGHT:
				std::cout << "Right";
				break;

			default:
				break;
			}
		}
	}
}

/// <summary>
/// GameHandler destructor
/// </summary>
GameHandler::~GameHandler()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}