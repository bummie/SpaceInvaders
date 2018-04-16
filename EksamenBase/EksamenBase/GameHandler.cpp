#include "GameHandler.h"
#include "TextureManager.h"
#include "InputManager.h"

GameHandler::GameHandler()
{
	window = nullptr;
	screenSurface = nullptr;
	gameState = GAME_STATE::RUNNING;

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

	window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	screenSurface = SDL_GetWindowSurface(window);

	//Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	//Update the surface
	SDL_UpdateWindowSurface(window);

	renderer = SDL_CreateRenderer(window, -1, 0);
	player = new GameObject(renderer); //TODO: Remove after testing

	Update();
}

/// <summary>
/// Game loop
/// </summary>
void GameHandler::Update()
{
	// Game loop
	while (gameState != GAME_STATE::GAMEOVER)
	{
		Input();
		Logic();
		Draw();
		SDL_Delay(33);
	}
}

/// <summary>
/// Game logic
/// </summary>
void GameHandler::Logic()
{
	player->Logic();
}

/// <summary>
/// Draws to the window
/// </summary>
void GameHandler::Draw()
{
	SDL_RenderClear(renderer);

	/*SDL_Rect dRect;
	dRect.h = 16;
	dRect.w = 16;
	dRect.x = 64;
	dRect.y = 64;

	SDL_RenderCopy(renderer, TextureManager::getInstance().GetTexture(renderer, "Resources/Images/bear.bmp"), NULL, &dRect);
	
	dRect.x = 120;
	dRect.y = 120;
	SDL_RenderCopy(renderer, TextureManager::getInstance().GetTexture(renderer, "Resources/Images/bear.bmp"), NULL, &dRect);
	*/

	player->Draw();

	SDL_RenderPresent(renderer);
}

/// <summary>
/// Takes input
/// </summary>
void GameHandler::Input()
{
	while (SDL_PollEvent(&InputManager::getInstance().event) != 0)
	{
		if (InputManager::getInstance().ExitGameRequested())
		{
			std::cout << "Pressed Exit" << std::endl;
			gameState = GAME_STATE::GAMEOVER;
		}

		player->Input();
	}
	
}

/// <summary>
/// GameHandler destructor
/// </summary>
GameHandler::~GameHandler()
{
	// MORE DESTROY
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}