#include "GameHandler.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "TextRenderer.h"
#include "SoundManager.h"
#include "GameObjectsManager.h"
#include "SDL_ttf.h"
#include "../GameObjects/Enemy.h"
#include <string>
#include <iomanip>

double GameHandler::deltaTime = 0;
int GameHandler::score = 0;

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

	//Fill the surface black
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	//Update the surface
	SDL_UpdateWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, 0);

	// Create player
	GameObjectsManager::getInstance().Add(new Player(renderer, SCREEN_HEIGHT/2, SCREEN_HEIGHT-64));
	GameObjectsManager::getInstance().Add(new Enemy(renderer));

	// Init text to screen
	TextRenderer::getInstance().addText("score", new Text(renderer, "Score <1>", {255, 255, 255}, 24, 0, 0, 164, 32));
	TextRenderer::getInstance().addText("highscore", new Text(renderer, "HI-SCORE SCORE <2>", { 255, 255, 255 }, 24, 172, 0, 164, 32));
	TextRenderer::getInstance().addText("score_value", new Text(renderer, "0000", { 255, 255, 255 }, 16, 0, 40, 82, 24));
	TextRenderer::getInstance().addText("highscore_value", new Text(renderer, "0000", { 255, 255, 255 }, 16, 172, 40, 82, 24));

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
	GameObjectsManager::getInstance().Logic();

	//TODO: Own method make pretty
	m_scorestream.clear();
	m_scorestream.str(std::string());
	m_scorestream << std::setw(4) << std::setfill('0') << GameHandler::score;
	TextRenderer::getInstance().getText("score_value")->setText(m_scorestream.str());
}

/// <summary>
/// Draws to the window
/// </summary>
void GameHandler::Draw()
{
	SDL_RenderClear(renderer);
	// Draw stuff start
	
	GameObjectsManager::getInstance().Draw();
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
		//Updates keys held down
		InputManager::getInstance().UpdateStates();

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
		}

		// Pause game
		if (InputManager::getInstance().KeyDown(SDLK_c))
		{
			GameHandler::score++;
		}

		// Handle input on gameobjects
		GameObjectsManager::getInstance().Input();
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