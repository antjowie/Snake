#include <iostream>

#include "Entity.h"

void print(cEntity *c) {
	std::cout << "Entity [" << c->getX() << ',' << c->getY() << "] [" << c->getDir() << "]\n";
}
int main() {
	cEntity *player = new cPlayer(5,8);
	cEntity *enemy = new cPlayer(10, 5);

	while (player->getX() != enemy->getX() || player->getY() != enemy->getY()) {
	print(enemy);
	enemy->ChangeDir(player);
	enemy->Move();
	}
	print(enemy);



	return 0;
}