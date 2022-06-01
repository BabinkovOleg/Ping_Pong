#pragma once

#include <malloc.h>

#include "raylib.h"
#include "ball.h"
#include "player.h"

typedef struct Game
{
	Ball ball;
	Vector2 field;
	Player* players;
	Texture2D background;
	int* score;
	bool needRestart;
	bool onPause;
} Game;

Game* InitGame(Vector2 windowSize, Texture2D backTex, Texture2D playerLTex, Texture2D playerRTex, Texture2D ballTex, float playerSpeed, Sound wall, Sound player);
void MainLoop(Game* g);
void DrawGame(Game* g);
void Restart(Game* g);