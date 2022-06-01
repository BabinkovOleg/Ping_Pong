#include "player.h"

void StartPosL(Player* p, Vector2 field) {
	p->position.x = 40;
	p->position.y = field.y / 2 - p->texture.height / 2;
	
}

void StartPosR(Player* p, Vector2 field) {
	p->position.x = field.x - p->texture.width - 40;
	p->position.y = field.y / 2 - p->texture.height / 2;
}