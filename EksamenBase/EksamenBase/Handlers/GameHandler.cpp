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
	gameState = GAME_STATE::GAMEOVER;
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
	GameObjectsManager::getInstance().Add(new Player(renderer, SCREEN_WIDTH * .5, SCREEN_HEIGHT - 64));

	// Init text to screen
	TextRenderer::getInstance().addText("score", new Text(renderer, "Score <1>", {255, 255, 255}, 24, 0, 0, 164, 32));
	TextRenderer::getInstance().addText("highscore", new Text(renderer, "HI-SCORE SCORE <2>", { 255, 255, 255 }, 24, 172, 0, 164, 32));
	TextRenderer::getInstance().addText("score_value", new Text(renderer, "0000", { 255, 255, 255 }, 16, 0, 40, 82, 24));
	TextRenderer::getInstance().addText("highscore_value", new Text(renderer, "0000", { 255, 255, 255 }, 16, 172, 40, 82, 24));

	TextRenderer::getInstance().addText("startscreen_title", new Text(renderer, "SPACE INVADERS", { 130, 200, 255 }, 36, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/5));
	TextRenderer::getInstance().addText("startscreen_enter", new Text(renderer, "Press <SPACE> to start!", { 255, 255, 255 }, 24, 172, SCREEN_HEIGHT/2, 164, 32));
	
	TextRenderer::getInstance().addText("paused", new Text(renderer, "Game has been paused", { 255, 255, 255 }, 24, 172, SCREEN_HEIGHT / 2, 164, 32));


	ChangeGameState(GAME_STATE::STARTSCREEN);
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
	switch(gameState)
	{
	case GAME_STATE::RUNNING:
		GameObjectsManager::getInstance().Logic();

		//TODO: Own method make pretty
		m_scorestream.clear();
		m_scorestream.str(std::string());
		m_scorestream << std::setw(4) << std::setfill('0') << GameHandler::score;
		TextRenderer::getInstance().getText("score_value")->setText(m_scorestream.str());

		break;
	case GAME_STATE::STARTSCREEN:

		break;
	case GAME_STATE::PAUSED:
		break;
	}
}

/// <summary>
/// Draws to the window
/// </summary>
void GameHandler::Draw()
{
	SDL_RenderClear(renderer);
	// Draw stuff start
	
	switch (gameState)
	{
	case GAME_STATE::RUNNING:
		GameObjectsManager::getInstance().Draw();
		break;
	case GAME_STATE::STARTSCREEN:
		break;
	case GAME_STATE::PAUSED:
		break;
	}

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
			ChangeGameState(GAME_STATE::GAMEOVER);
		}

		// Pause game
		if (InputManager::getInstance().KeyDown(SDLK_p) && gameState != GAME_STATE::STARTSCREEN)
		{
			if(gameState != GAME_STATE::PAUSED)
			{
				ChangeGameState(GAME_STATE::PAUSED);
			}else
			{
				ChangeGameState(GAME_STATE::RUNNING);
			}
		}

		// Add score to player
		if (InputManager::getInstance().KeyDown(SDLK_c))
		{
			GameHandler::score++;
		}

		// Handle input on gameobjects

		switch (gameState)
		{
		case GAME_STATE::RUNNING:
			GameObjectsManager::getInstance().Input();
			break;
		case GAME_STATE::STARTSCREEN:
			if (InputManager::getInstance().KeyDown(SDLK_SPACE))
			{
				ChangeGameState(GAME_STATE::RUNNING);
			}
			break;
		case GAME_STATE::PAUSED:
			break;
		}
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
/// Handles the change of game state
/// </summary>
/// <param name="state"></param>
void GameHandler::ChangeGameState(GameHandler::GAME_STATE state)
{
	if (gameState == state) { return; }
	
	gameState = state;

	switch (gameState)
	{
	case GAME_STATE::RUNNING:
		std::cout << "GameState: Running" << std::endl;
		TextRenderer::getInstance().getText("paused")->setVisible(false);

		TextRenderer::getInstance().getText("startscreen_title")->setVisible(false);
		TextRenderer::getInstance().getText("startscreen_enter")->setVisible(false);

		TextRenderer::getInstance().getText("score")->setVisible(true);
		TextRenderer::getInstance().getText("score_value")->setVisible(true);
		TextRenderer::getInstance().getText("highscore")->setVisible(true);
		TextRenderer::getInstance().getText("highscore_value")->setVisible(true);
		break;
	case GAME_STATE::STARTSCREEN:
		std::cout << "GameState: Startscreen" << std::endl;

		TextRenderer::getInstance().getText("paused")->setVisible(false);

		TextRenderer::getInstance().getText("startscreen_title")->setVisible(true);
		TextRenderer::getInstance().getText("startscreen_enter")->setVisible(true);

		TextRenderer::getInstance().getText("score")->setVisible(false);
		TextRenderer::getInstance().getText("score_value")->setVisible(false);
		TextRenderer::getInstance().getText("highscore")->setVisible(false);
		TextRenderer::getInstance().getText("highscore_value")->setVisible(false);
		break;
	case GAME_STATE::PAUSED:
		std::cout << "GameState: Paused" << std::endl;
		TextRenderer::getInstance().getText("paused")->setVisible(true);
		break;

	case GAME_STATE::GAMEOVER:
		std::cout << "GameState: GameOver" << std::endl;

		break;
	}


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