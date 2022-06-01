#pragma once

#include "raylib.h"

typedef struct Player
{
	Vector2 position;
	float speed;
	Texture2D texture;
} Player;

void StartPosL(Player* p, Vector2 field);
void StartPosR(Player* p, Vector2 field);