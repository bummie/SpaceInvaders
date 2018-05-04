#ifndef GAMEHANDLER_H_INCLUDED
#define GAMEHANDLER_H_INCLUDED

#include "SDL.h"
#undef main
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "../GameObjects/Player.h"
#include "Text.h"
#include "../GameObjects/Barricade.h"

class GameHandler
{
public:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	static int score;
	static int highScore;
private:
	const enum GAME_STATE { RUNNING, STARTSCREEN, GAMEOVER, PAUSED, EXIT };

	const char* M_GAME_NAME = "Space Invaders 2018";

	const int M_GAME_DELAY = 1000 / 60;

	SDL_Window* m_window;
	SDL_Surface* m_screenSurface;
	SDL_Renderer* m_renderer;
	GAME_STATE m_gameState;

	Player* m_player;

	Uint64 dtNow, dtLast;
	static double deltaTime;

	std::stringstream m_scorestream;
	std::vector<std::shared_ptr<GameObject>>* m_enemies;
	float m_enemyMoveDelay;
	float m_enemyMoveTimer;
	int m_enemyMoveDistance;
	int m_enemyMoveDirection;
	bool m_enemyTurnAround;
	bool m_enemyMoveDown;
	int m_enemyRowCount;
	int m_enemyColumnCount;
	int m_enemySpacing;
	Barricade* m_barricade[4];

	void Update();
	void Draw();
	void Logic();
	void Input();
	void UpdateDeltaTime();
	void ChangeGameState(GameHandler::GAME_STATE state);
	void SpawnEnemies();
	void ResetEnemies();
	void ResetPlayer();
	void ResetBarricades();
	void ResetGame();
	void MoveEnemies();
	void CheckWin();
	void CheckDeath();
	void SpawnBarricades();

	void GetScoreFile();
	void SetScoreFile();
	void UpdateScoreText();

	void DisplayStartScreenText(bool shouldDisplay);
	void DisplayGameScreenText(bool shouldDisplay);
	void DisplayGameOverScreenText(bool shouldDisplay);
	void DisplayPausedText(bool shouldDisplay);

public:
	GameHandler();
	~GameHandler();
	void Init();
	
	static double getDeltaTime();
};

#endif
