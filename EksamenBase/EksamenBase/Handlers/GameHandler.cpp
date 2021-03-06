#include "GameHandler.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "TextRenderer.h"
#include "SoundManager.h"
#include "GameObjectsManager.h"
#include "SDL_ttf.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Laser.h"
#include "../GameObjects/Snake.h"
#include "../GameObjects/EnemyAttack.h"
#include "../GameObjects/MysteryShip.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <memory>

double GameHandler::deltaTime = 0;
int GameHandler::score = 0;
int GameHandler::highScore = 0;
int GameHandler::level = 1;

GameHandler::GameHandler()
{
	m_window = nullptr;
	m_screenSurface = nullptr;
	m_gameState = GAME_STATE::EXIT;
	dtNow = dtLast = 0;
	m_enemyMoveDelay = 400;
	m_enemyMoveTimer = 0;
	m_enemyMoveDistance = 5;
	m_enemyMoveDirection = -1;
	m_enemyTurnAround = false;
	m_enemyMoveDown = false;
	m_enemyColumnCount = 11;
	m_enemyRowCount = 5;
	m_enemySpacing = 32;
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

	m_window = SDL_CreateWindow(M_GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
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

	m_screenSurface = SDL_GetWindowSurface(m_window);

	//Fill the surface black
	SDL_FillRect(m_screenSurface, NULL, SDL_MapRGB(m_screenSurface->format, 0x00, 0x00, 0x00));

	//Update the surface
	SDL_UpdateWindowSurface(m_window);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);

	// Create player
	GameObjectsManager::getInstance().Add(std::shared_ptr<Player>(new Player(m_renderer, SCREEN_HEIGHT / 2, SCREEN_HEIGHT - 64)));
	GameObjectsManager::getInstance().Add(std::shared_ptr<MysteryShip>(new MysteryShip(m_renderer)));
	SpawnEnemies();
	SpawnBarricades();
	
	// Init text to screen
	TextRenderer::getInstance().addText("score", new Text(m_renderer, "Score <1>", { 255, 255, 255 }, 24, 0, 0, 164, 32));
	TextRenderer::getInstance().addText("highscore", new Text(m_renderer, "HI-SCORE SCORE <2>", { 255, 255, 255 }, 24, 172, 0, 164, 32));
	TextRenderer::getInstance().addText("score_value", new Text(m_renderer, "0000", { 255, 255, 255 }, 16, 0, 40, 82, 24));
	TextRenderer::getInstance().addText("highscore_value", new Text(m_renderer, "0000", { 255, 255, 255 }, 16, 172, 40, 82, 24));

	TextRenderer::getInstance().addText("startscreen_title", new Text(m_renderer, "SPACE INVADERS", { 130, 200, 255 }, 36, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 5));
	TextRenderer::getInstance().addText("startscreen_enter", new Text(m_renderer, "Press <SPACE> to start!", { 255, 255, 255 }, 24, 172, SCREEN_HEIGHT / 2, 250, 48));

	TextRenderer::getInstance().addText("paused_text", new Text(m_renderer, "Game has been paused", { 0, 255, 0 }, 24, 200, SCREEN_HEIGHT / 2, 250, 48));
	TextRenderer::getInstance().addText("paused_exit", new Text(m_renderer, "Escape for Exit", { 0, 255, 0 }, 16, 250, (SCREEN_HEIGHT / 2) + 40, 140, 32));


	TextRenderer::getInstance().addText("gameover_text", new Text(m_renderer, "Gameover. Try again?", { 0, 255, 0 }, 24, 220, SCREEN_HEIGHT / 2, 220, 32));
	TextRenderer::getInstance().addText("gameover_yes", new Text(m_renderer, "Space for yes", { 0, 255, 0 }, 16, 140, (SCREEN_HEIGHT / 2) + 40, 140, 32));
	TextRenderer::getInstance().addText("gameover_no", new Text(m_renderer, "Escape for Exit", { 0, 255, 0 }, 16, 380, (SCREEN_HEIGHT / 2) + 40, 140, 32));

	ChangeGameState(GAME_STATE::STARTSCREEN);
	GetScoreFile();
	Update();
}

/// <summary>
/// Game loop
/// </summary>
void GameHandler::Update()
{
	// Game loop
	while (m_gameState != GAME_STATE::EXIT)
	{
		UpdateDeltaTime();
		Input();
		Logic();
		Draw();
		CheckWin();
		CheckDeath();
		SDL_Delay(M_GAME_DELAY);
	}
}

/// <summary>
/// Game logic
/// </summary>
void GameHandler::Logic()
{
	switch (m_gameState)
	{
		case GAME_STATE::RUNNING:
		{
			GameObjectsManager::getInstance().Logic();
			MoveEnemies();
			UpdateScoreText();
		}
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
	SDL_RenderClear(m_renderer);
	// Draw stuff start
	switch (m_gameState)
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
	SDL_RenderPresent(m_renderer);
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
			ChangeGameState(GAME_STATE::EXIT);
		}

		if (InputManager::getInstance().KeyDown(SDLK_m))
		{
			if(SoundManager::getInstance().MusicPlaying())
			{
				SoundManager::getInstance().StopMusic();
			}else
			{
				SoundManager::getInstance().PlayMusic();
			}
		}

		if (m_gameState == GAME_STATE::PAUSED)
		{
			if (InputManager::getInstance().KeyDown(SDLK_ESCAPE))
			{
				ChangeGameState(GAME_STATE::EXIT);
			}
		}

		// Pause game
		if (InputManager::getInstance().KeyDown(SDLK_p) && m_gameState != GAME_STATE::STARTSCREEN && m_gameState != GAME_STATE::GAMEOVER)
		{
			if (m_gameState != GAME_STATE::PAUSED)
			{
				ChangeGameState(GAME_STATE::PAUSED);
			}
			else
			{
				ChangeGameState(GAME_STATE::RUNNING);
			}
		}

		if (m_gameState == GAME_STATE::GAMEOVER)
		{
			if (InputManager::getInstance().KeyDown(SDLK_ESCAPE))
			{
				ChangeGameState(GAME_STATE::EXIT);
			}
			if (InputManager::getInstance().KeyDown(SDLK_SPACE))
			{
				ChangeGameState(GAME_STATE::RUNNING);
				ResetGame();
			}
		}


		// Handle input on gameobjects
		switch (m_gameState)
		{
		case GAME_STATE::RUNNING:
			GameObjectsManager::getInstance().Input();
			break;
		case GAME_STATE::STARTSCREEN:
		{
			if (InputManager::getInstance().KeyDown(SDLK_SPACE))
			{
				ChangeGameState(GAME_STATE::RUNNING);
			}
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
	if (m_gameState == state) { return; }
	m_gameState = state;

	switch (m_gameState)
	{
	case GAME_STATE::RUNNING:
		std::cout << "GameState: Running" << std::endl;
		DisplayPausedText(false);
		DisplayStartScreenText(false);
		DisplayGameOverScreenText(false);
		DisplayGameScreenText(true);

		SoundManager::getInstance().PlayMusic();

		break;
	case GAME_STATE::STARTSCREEN:
		std::cout << "GameState: Startscreen" << std::endl;
		DisplayPausedText(false);
		DisplayStartScreenText(true);
		DisplayGameOverScreenText(false);
		DisplayGameScreenText(false);

		SoundManager::getInstance().StopMusic();
		break;
	case GAME_STATE::PAUSED:
		std::cout << "GameState: Paused" << std::endl;
		DisplayPausedText(true);
		DisplayStartScreenText(false);
		DisplayGameOverScreenText(false);
		DisplayGameScreenText(true);
		SoundManager::getInstance().StopMusic();
		break;

	case GAME_STATE::GAMEOVER:
		std::cout << "GameState: GameOver" << std::endl;

		DisplayPausedText(false);
		DisplayStartScreenText(false);
		DisplayGameOverScreenText(true);
		DisplayGameScreenText(true);
		SoundManager::getInstance().StopMusic();
		break;

	case GAME_STATE::EXIT:
		SetScoreFile();
		std::cout << "GameState: EXIT" << std::endl;
		break;
	}
}

/// <summary>
/// Spawns enemies in formation
/// </summary>
void GameHandler::SpawnEnemies()
{
	Enemy::ENEMY_TYPE type = Enemy::ENEMY_TYPE::SQUID;

	for (int y = 0; y < m_enemyRowCount; y++)
	{
		if (y == 1 || y == 2)
		{
			type = Enemy::ENEMY_TYPE::ALIEN;
		}
		else if (y == 3 || y == 4)
		{
			type = Enemy::ENEMY_TYPE::GHOST;
		}

		for (int x = 0; x < m_enemyColumnCount; x++)
		{
			GameObjectsManager::getInstance().Add(std::shared_ptr<Enemy>(new Enemy(m_renderer, (x * m_enemySpacing) + 50, (y * m_enemySpacing) + 100, type)));
		}
	}

	m_enemies = GameObjectsManager::getInstance().Find("Enemy");
}

/// <summary>
/// Reset enemies
/// </summary>
void GameHandler::ResetEnemies()
{
	m_enemyMoveDirection = -1;

	for (int y = 0; y < m_enemyRowCount; y++)
	{
		for (int x = 0; x < m_enemyColumnCount; x++)
		{
			int pos = (m_enemyColumnCount * y) + x;
			m_enemies->at(pos)->position.x = (x * m_enemySpacing) + 50;
			m_enemies->at(pos)->position.y = (y * m_enemySpacing) + 100;
			m_enemies->at(pos)->setHp(100);
			m_enemies->at(pos)->ResetAnim();
		}
	}
}

/// <summary>
/// Resets the player
/// </summary>
void GameHandler::ResetPlayer()
{
	auto playerArray = GameObjectsManager::getInstance().Find("Player");
	for (auto ply : *playerArray)
	{
		ply->setHp(100);
	}

	delete(playerArray);
}

/// <summary>
/// Resets all the barricades
/// </summary>
void GameHandler::ResetBarricades()
{
	for(auto barricade : m_barricade)
	{
		barricade->ResetBarricadeBlocks();
	}
}

/// <summary>
/// Resets the game
/// </summary>
void GameHandler::ResetGame()
{
	ResetEnemies();
	ResetPlayer();
	ResetBarricades();
	GameHandler::score = 0;
}

/// <summary>
/// Moves the enemies side to side and downwards towards the earth!
/// </summary>
void GameHandler::MoveEnemies()
{
	if (m_enemies == nullptr) { return; }

	if (m_enemyMoveTimer >= m_enemyMoveDelay)
	{
		if (m_enemyTurnAround)
		{
			m_enemyMoveDirection *= -1;
			m_enemyTurnAround = false;
		}

		for (auto enemy : *m_enemies)
		{
			if (enemy->getHp() <= 0) { continue; }

			enemy->position.x += m_enemyMoveDistance * m_enemyMoveDirection;
			if (m_enemyMoveDown)
			{
				enemy->position.y += m_enemyMoveDistance;
			}

			if (enemy->position.x <= 0 || enemy->position.x >= (SCREEN_WIDTH - enemy->position.w))
			{
				m_enemyTurnAround = true;
				m_enemyMoveDown = true;
			}
		}
		if (!m_enemyTurnAround) { m_enemyMoveDown = false; }
		m_enemyMoveTimer = 0;
	}

	m_enemyMoveTimer += getDeltaTime();
}

/// <summary>
/// Spawns barricades into the game
/// </summary>
void GameHandler::SpawnBarricades()
{
	for(int i = 0; i < 4; i++)
	{
		m_barricade[i] = new Barricade(m_renderer, (i * 120) + 100, 350);
	}
}

/// <summary>
/// Reads the highscore from file
/// </summary>
void GameHandler::GetScoreFile()
{
	std::string scoreString;
	std::ifstream highScoreFile("Resources/Text/HighScore.score");
	if (highScoreFile.is_open())
	{
		std::getline(highScoreFile, scoreString);
		highScoreFile.close();
		highScore = std::stoi(scoreString);
	}
	else
	{
		highScore = 0;
		std::cout << "Couldn't open highscore.score" << std::endl;
	}
}

/// <summary>
/// Writes the highscore to a file
/// </summary>
void GameHandler::SetScoreFile()
{
	std::string scoreString = std::to_string(highScore);
	std::ofstream highScoreFile;
	highScoreFile.open("Resources/Text/HighScore.score", std::ofstream::out | std::ofstream::trunc);
	if (highScoreFile.is_open())
	{
		highScoreFile << scoreString;
		highScoreFile.close();
	}
	else
	{
		std::cout << "Couldn't open HighScore.score";
	}
}

/// <summary>
/// Updates the score text
/// </summary>
void GameHandler::UpdateScoreText()
{
	m_scorestream.clear();
	m_scorestream.str(std::string());
	m_scorestream << std::setw(4) << std::setfill('0') << GameHandler::score;
	TextRenderer::getInstance().getText("score_value")->setText(m_scorestream.str());

	m_scorestream.clear();
	m_scorestream.str(std::string());
	m_scorestream << std::setw(4) << std::setfill('0') << GameHandler::highScore;
	TextRenderer::getInstance().getText("highscore_value")->setText(m_scorestream.str());
}



/// <summary>
/// Hides or displays given text
/// </summary>
/// <param name="shouldDisplay"></param>
void GameHandler::DisplayStartScreenText(bool shouldDisplay)
{
	TextRenderer::getInstance().getText("startscreen_title")->setVisible(shouldDisplay);
	TextRenderer::getInstance().getText("startscreen_enter")->setBlink(shouldDisplay);
}

/// <summary>
/// Hides or displays given text
/// </summary>
/// <param name="shouldDisplay"></param>
void GameHandler::DisplayGameScreenText(bool shouldDisplay)
{
	TextRenderer::getInstance().getText("score")->setVisible(shouldDisplay);
	TextRenderer::getInstance().getText("score_value")->setVisible(shouldDisplay);
	TextRenderer::getInstance().getText("highscore")->setVisible(shouldDisplay);
	TextRenderer::getInstance().getText("highscore_value")->setVisible(shouldDisplay);
}

/// <summary>
/// Hides or displays given text
/// </summary>
/// <param name="shouldDisplay"></param>
void GameHandler::DisplayGameOverScreenText(bool shouldDisplay)
{
	TextRenderer::getInstance().getText("gameover_text")->setVisible(shouldDisplay);
	TextRenderer::getInstance().getText("gameover_yes")->setVisible(shouldDisplay);
	TextRenderer::getInstance().getText("gameover_no")->setVisible(shouldDisplay);
}

/// <summary>
/// Hides or displays given text
/// </summary>
/// <param name="shouldDisplay"></param>
void GameHandler::DisplayPausedText(bool shouldDisplay)
{
	TextRenderer::getInstance().getText("paused_text")->setBlink(shouldDisplay);
	TextRenderer::getInstance().getText("paused_exit")->setBlink(shouldDisplay);

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
/// Checks if all enemies are dead and resets board if so
/// </summary>
void GameHandler::CheckWin()
{
	bool allEnemiesDead;
	for (auto enemy : *m_enemies)
	{
		if (enemy->getHp() <= 0)
		{
			allEnemiesDead = true;
		}

		if (enemy->getHp() > 0)
		{
			allEnemiesDead = false;
			return;
		}
	}

	if (allEnemiesDead)
	{
		ResetEnemies();
		m_enemyMoveDelay *= .7;
		GameHandler::level++;
	}
}

/// <summary>
/// Checks if the player dies
/// </summary>
void GameHandler::CheckDeath()
{

	if (m_gameState != GAME_STATE::STARTSCREEN && m_gameState != GAME_STATE::EXIT)
	{

		auto player = GameObjectsManager::getInstance().Find("Player");
		for (auto players : *player)
		{
			if (players->getHp() <= 0)
			{
				ChangeGameState(GAME_STATE::GAMEOVER);
				if (score > highScore)
				{
					highScore = score;
				}
			}
		}		
		delete(player);
	}
}

/// <summary>
/// GameHandler destructor
/// </summary>
GameHandler::~GameHandler()
{
	// MORE DESTROY
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}