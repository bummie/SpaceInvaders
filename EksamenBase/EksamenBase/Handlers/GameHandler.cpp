#include "GameHandler.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "TextRenderer.h"
#include "SoundManager.h"
#include "SDL_ttf.h"
#include <string>

double GameHandler::deltaTime = 0;

GameHandler::GameHandler()
{
	window = nullptr;
	screenSurface = nullptr;
	gameState = GAME_STATE::RUNNING;
	dtNow = dtLast = 0;
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

	if (TTF_Init() == -1) 
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		return;
	}

	if (!SoundManager::getInstance().Init()) { return; }

	screenSurface = SDL_GetWindowSurface(window);

	//Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	//Update the surface
	SDL_UpdateWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, 0);

	player = new Player(renderer); //TODO: Remove after testing
	TextRenderer::getInstance().addText("Seb", new Text(renderer, "Seb e kul", {255, 0, 255}, 24, 250, 100, 200, 200));
	TextRenderer::getInstance().addText("Title", new Text(renderer, "HALLO", { 19, 40, 255 }, 12, 10, 10, 100, 100));

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
		UpdateDeltaTime();
		Input();
		
		if(gameState != GAME_STATE::PAUSED)
		{
			Logic();
			Draw();
		}
		
		SDL_Delay(GAME_DELAY);
	}
}

/// <summary>
/// Game logic
/// </summary>
void GameHandler::Logic()
{
	player->Logic();
	TextRenderer::getInstance().getText("Seb")->setText("Seb: " + std::to_string(getDeltaTime()));
}

/// <summary>
/// Draws to the window
/// </summary>
void GameHandler::Draw()
{
	SDL_RenderClear(renderer);
	// Draw stuff start
	
	player->Draw();
	TextRenderer::getInstance().Draw();

	// Draw stuff end
	SDL_RenderPresent(renderer);
}

/// <summary>
/// Takes input
/// </summary>
void GameHandler::Input()
{
	while (SDL_PollEvent(&InputManager::getInstance().event) != 0)
	{
		// Exit game
		if (InputManager::getInstance().ExitGameRequested())
		{
			std::cout << "Pressed Exit" << std::endl;
			gameState = GAME_STATE::GAMEOVER;
		}

		// Pause game
		if (InputManager::getInstance().KeyDown(SDLK_p))
		{
			std::cout << "PAUSING GAME" << std::endl;
			//gameState = GAME_STATE::PAUSED;
			TextRenderer::getInstance().getText("Title")->setText("TRYKKET P");

		}

		if (InputManager::getInstance().KeyDown(SDLK_q))
		{
			TextRenderer::getInstance().getText("Title")->setText("TRYKKET Q");
			TextRenderer::getInstance().removeText("Title");
		}

		//Updates keys held down
		InputManager::getInstance().UpdateStates();

		// Handle input on player
		player->Input();
	}	
}

/// <summary>
/// Updates the deltatime value
/// </summary>
void GameHandler::UpdateDeltaTime()
{
	dtLast = dtNow;
	dtNow = SDL_GetPerformanceCounter();

	GameHandler::deltaTime = (double)((dtNow - dtLast) * 1000 / SDL_GetPerformanceFrequency());
}

/// <summary>
/// Returns the deltatime
/// </summary>
/// <returns></returns>
double GameHandler::getDeltaTime()
{
	return deltaTime;
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