#pragma once

#include "raylib.h"


typedef struct Ball
{
	Vector2 position;
	Vector2 speed;
	Texture2D texture;
	Sound wall;
	Sound player;
	bool isCollisions;
} Ball;

void BallBounceVert(Ball* b);
void BallBounceHor(Ball* b);
void BallRespawn(Ball* b, Vector2 field);
void BallStart(Ball* b);