#include "raylib.h"
#include "game.h"

#define MAX_SCORE 1

Game* InitGame(Vector2 windowSize, Texture2D backTex, Texture2D playerLTex, Texture2D playerRTex, Texture2D ballTex, float playerSpeed, Sound wall, Sound player) {
	Game* g = (Game*)malloc(sizeof(Game));
	if (g) {
		g->field = windowSize;
		g->background = backTex;
		g->score = (int*)malloc(sizeof(int) * 2);
		g->needRestart = false;
		g->onPause = true;
		g->ball.texture = ballTex;
		g->ball.wall = wall;
		g->ball.player = player;
		BallRespawn(&g->ball, g->field);
		//g->ball.speed = (Vector2) { 2.0f, 2.5f };

		if (g->score) {
			g->players = (Player*)malloc(sizeof(Player) * 2);

			if (g->players) {
				g->players[0].texture = playerLTex;
				g->players[1].texture = playerRTex;
				g->players[0].speed = playerSpeed;
				g->players[1].speed = playerSpeed;
				
				StartPosL(&g->players[0], g->field);
				StartPosR(&g->players[1], g->field);

				g->score[0] = 0;
				g->score[1] = 0;
			}
		}
	}

	return g;
}

void MainLoop(Game* g) {
	if (!g->onPause) {
		g->ball.position.x += g->ball.speed.x;
		g->ball.position.y += g->ball.speed.y;
	}
	else {
		if (g->ball.speed.x == 0)
			BallStart(&g->ball);
	}

	if (g->ball.position.y < 0 || g->ball.position.y > g->field.y - g->ball.texture.height) {
		BallBounceVert(&g->ball);
	}

	if (g->ball.position.x - g->players[0].position.x < g->ball.speed.x || g->players[1].position.x - g->ball.position.x < g->ball.speed.x ) {
		g->ball.isCollisions = false;
	}

	if ((g->ball.position.x < g->players[0].position.x + g->players[0].texture.width) &&
		((g->ball.position.y + g->ball.texture.height > g->players[0].position.y) &&
		(g->ball.position.y < g->players[0].position.y + g->players[0].texture.height))){
		BallBounceHor(&g->ball);
	}
	if ((g->ball.position.x + g->ball.texture.width > g->players[1].position.x) &&
		(g->ball.position.y < g->players[1].position.y + g->players[1].texture.height) &&
		(g->ball.position.y + g->ball.texture.height > g->players[1].position.y)) {
		BallBounceHor(&g->ball);
	}
	if (g->ball.position.x + g->ball.texture.width < 0) {
		g->score[1] += 1;
		BallRespawn(&g->ball, g->field);
		g->onPause = true;
	}
	if (g->ball.position.x > g->field.x) {
		g->score[0] += 1;
		BallRespawn(&g->ball, g->field);
		g->onPause = true;
	}
}

void DrawGame(Game* g) {
	ClearBackground(RAYWHITE);

	DrawTexture(g->background, 0, 0, WHITE);

	DrawLineBezier((Vector2) { g->field.x / 2, 0 }, (Vector2) { g->field.x / 2, g->field.y }, 3, WHITE);

	DrawTexture(g->ball.texture, g->ball.position.x, g->ball.position.y, WHITE);

	DrawTexture(g->players[0].texture, g->players[0].position.x, g->players[0].position.y, WHITE);
	DrawTexture(g->players[1].texture, g->players[1].position.x, g->players[1].position.y, WHITE);

	DrawText(TextFormat("%d", g->score[0]), g->field.x / 4, g->field.y / 4, 40, WHITE);
	DrawText(TextFormat("%d", g->score[1]), 3 * g->field.x / 4, g->field.y / 4, 40, WHITE);

	if (g->score[0] >= MAX_SCORE || g->score[1] >= MAX_SCORE) {
		g->needRestart = true;
	}
	if (g->score[0] >= MAX_SCORE) {
		DrawText("PLAYER 1 WINS!", g->field.x / 2 - 260, g->field.y / 2 - 60, 60, RED);
		DrawText("R to restart", g->field.x / 2 - 200, g->field.y / 2, 60, RED);
	}
	if (g->score[1] >= MAX_SCORE) {
		DrawText("PLAYER 2 WINS!", g->field.x / 2 - 260, g->field.y / 2 - 60, 60, RED);
		DrawText("R to restart", g->field.x / 2 - 200, g->field.y / 2, 60, RED);
	}
}

void Restart(Game* g) {
	g->needRestart = false;
	g->onPause = true;
	g->score[0] = 0;
	g->score[1] = 0;
	BallRespawn(&g->ball, g->field);
	StartPosL(&g->players[0], g->field);
	StartPosR(&g->players[1], g->field);
}