#include "raylib.h"
#include "game.h"

#define RES_FOLDER "resources/"

#define TEXTURE_BALL "ball.png"
#define TEXTURE_PLAYER1 "player1.png"
#define TEXTURE_PLAYER2 "player2.png"
#define TEXTURE_BACKGROUND "background.png"

#define SOUND_WALL_BOUNCE "wall.wav"
#define SOUND_PLAYER_BOUNCE "player.wav"
#define PLAYER_SPEED 4.0f

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	Texture2D ball = LoadTexture(RES_FOLDER TEXTURE_BALL);
	Texture2D player1 = LoadTexture(RES_FOLDER TEXTURE_PLAYER1);
	Texture2D player2 = LoadTexture(RES_FOLDER TEXTURE_PLAYER2);
	Texture2D background = LoadTexture(RES_FOLDER TEXTURE_BACKGROUND);

	InitAudioDevice();

	Sound wallBounce = LoadSound(RES_FOLDER SOUND_WALL_BOUNCE);
	Sound playerBounce = LoadSound(RES_FOLDER SOUND_PLAYER_BOUNCE);

	Game* game = InitGame((Vector2) { screenWidth, screenHeight }, background, player1, player2, ball, PLAYER_SPEED, wallBounce, playerBounce);

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_W))
			game->players[0].position.y -= game->players[0].speed;
		if(IsKeyDown(KEY_S))
			game->players[0].position.y += game->players[0].speed;

		if (game->players[0].position.y + game->players[0].texture.height > screenHeight)
			game->players[0].position.y = screenHeight - game->players[0].texture.height;
		if (game->players[0].position.y < 0)
			game->players[0].position.y = 0;

		if(IsKeyDown(KEY_UP))
			game->players[1].position.y -= game->players[1].speed;
		if (IsKeyDown(KEY_DOWN))
			game->players[1].position.y += game->players[1].speed;

		if (game->players[1].position.y + game->players[1].texture.height > screenHeight)
			game->players[1].position.y = screenHeight - game->players[1].texture.height;
		if (game->players[1].position.y < 0)
			game->players[1].position.y = 0;

		MainLoop(game);

		if (IsKeyPressed(KEY_SPACE) && game->needRestart == false) {
			if (game->onPause == true) {
				game->onPause = false;
			}
			else {
				game->onPause = true;
			}
		}

		if (game->needRestart == true && IsKeyPressed(KEY_R)){
			Restart(game);
		}

		BeginDrawing();
		
		DrawGame(game);

		EndDrawing();
	}
	CloseWindow();


	free(game);
	return 0;
}