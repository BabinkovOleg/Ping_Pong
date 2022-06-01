#include "ball.h"
#include "game.h"

void BallBounceVert(Ball* b) {
	b->speed.y *= -1;
	PlaySound(b->wall);
}
void BallBounceHor(Ball* b) {
	if(b->isCollisions)
		b->speed.x *= -1.05f;
	PlaySound(b->player);
}
void BallRespawn(Ball* b, Vector2 field) {
	b->position = (Vector2) { field.x / 2 - b->texture.width / 2, field.y / 2 - b->texture.height / 2 };
	b->speed = (Vector2) { 0.0f, 0.0f };
}
void BallStart(Ball* b) {
	b->isCollisions = true;

	b->speed.x = 0.1f * GetRandomValue(30, 40);
	if (GetRandomValue(0, 1))
		b->speed.x *= -1;

	b->speed.y = 0.1f * GetRandomValue(30, 40);
	if (GetRandomValue(0, 1))
		b->speed.y *= -1;
}