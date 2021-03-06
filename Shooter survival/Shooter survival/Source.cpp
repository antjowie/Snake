﻿#include <iostream>
#include <time.h>
#include <thread>
#include <chrono>
#include <conio.h>

#define sleep std::this_thread::sleep_for(std::chrono::milliseconds(100))
#include "Weapon.h"
#include "Entity.h"

/* 
Weapon list
ammoCapacity, damage, fireRate, bulletPace, paramLive, paramIcon, paramMaxBullet
*/
cWeapon HandGun(10, 1, 3, 1, 5, '\xFA', 3);

class cGameManager {
	int width, heigth;
	char up, down, left, right, shootUp, shootDown, shootLeft, shootRight, reload, pause;
	bool quit;
	cEntity *player;
	cEntity *enemy;
	cWeapon *weapon;
	int score;
	int enemyAmount;
public:
	cGameManager(int paramX, int paramY) {
		srand(time(NULL));
		width = paramX; heigth = paramY;

		// Will be controlable from text file
		up = 'w';	left = 'a';		
		down = 's';	right = 'd'; 
		shootUp = 'i';	shootLeft = 'j';
		shootDown = 'k'; shootRight = 'l';
		reload = 'r'; pause = 'p';
		
		player = new cPlayer(paramX / 2, paramY / 2);
		weapon = &HandGun;
		quit = false;
		score = 0;

		enemyAmount = 1;
		enemy = new cEnemy[enemyAmount];
		(enemy + 0)->insertX(2);
		(enemy + 0)->insertY(2);

	}

	~cGameManager() {
		delete player, weapon;
		delete[] enemy;
	}

	void Draw() {
		system("cls");

		// Upper wall
		for (int x = 0; x < width + 2; x++)
			std::cout << '\xDC';
		std::cout << '\n';

		for (int y = 0; y < heigth; y++) {
			for (int x = 0; x < width; x++) {

				// Left wall
				if (x == 0)
					std::cout << '\xDB';

				bool foundBullet = false;
				
				// Weapon bullets
				for (int i = 0; i < weapon->getMaxBullet(); ++i)
					if (x == weapon->getBulletX(i) && y == weapon->getBulletY(i) && weapon->getBulletActive(i)== true) {
						std::cout << weapon->getBulletIcon();
						foundBullet = true;
						break;
					}

				if (foundBullet == false) {
					bool foundEnemy = false;

				// Enemy
					for (int i = 0; i < enemyAmount; i++)
						if ((enemy + i)->getX() == x && (enemy + i)->getY() == y && (enemy + i)->getAlive() == true) {
							std::cout << 'E';
							foundEnemy = true;
							break;
						}

				// Player
					if (foundEnemy == false) {
				if (x == player->getX() && y == player->getY())
					std::cout << '\x9D';
				
				else
						std::cout << ' ';
					}
				}

				// Rigth wall
				if(x == width - 1)
					std::cout << '\xDB';
			}
			std::cout << '\n';
		}
		// Lower wall
		for (int x = 0; x < width + 2; x++)
			std::cout << '\xDF';

		// Score and bullets
		std::cout << "\nAmmo: " << weapon->getAmmo() << '/' << weapon->getMaxAmmo() << "\t\tScore:" << score;
	}
	void Input() {
		if (_kbhit()) {
			char current = _getch();

			// Player move
			if (current == up)
				player->ChangeDir(UP);
			if (current == down)
				player->ChangeDir(DOWN);
			if (current == left)
				player->ChangeDir(LEFT);
			if (current == right)
				player->ChangeDir(RIGHT);

			// Fire weapon			
			if (weapon->getAmmo() != 0) {
				if (current == shootUp)
					weapon->Shoot(player->getX(), player->getY(), BULLETUP);
				if (current == shootDown)
					weapon->Shoot(player->getX(), player->getY(), BULLETDOWN);
				if (current == shootLeft)
					weapon->Shoot(player->getX(), player->getY(), BULLETLEFT);
				if (current == shootRight)
					weapon->Shoot(player->getX(), player->getY(), BULLETRIGHT);
			}
			else
				std::cout << '\a';

			if (current == reload)
				weapon->Reload();

			// Misc
			if (current == pause)
				Pause();
			player->Move();
		}
		player->ChangeDir(STOP);
	}
	void Logic() {

		// Checks death of enemy
		// Checks bullet pace
		for (int i = 0; i < weapon->getPace(); i++) {
		weapon->Render();
			// Loops through every bullet
			for (int j = 0; j < weapon->getMaxBullet(); j++)
				if (weapon->getBulletActive(j) == true)
					// Loops through every enemy
					for (int k = 0; k < enemyAmount; k++)
						if ((enemy + k)->getX() == weapon->getBulletX(j) && (enemy + k)->getY() == weapon->getBulletY(j))
							(enemy + k)->Reset();
		}

		// Moves enemy
		for (int i = 0; i < enemyAmount; i++) {
			(enemy + i)->ChangeDir(player);
			(enemy + i)->Move();
		}
		// Kills bullets that have reached the end of their live
		weapon->Kill();

	}
	void ScoreUp() {

	}
	void GenerateEnemy(int amount) {
		enemy = new cEnemy[amount];
		enemyAmount = amount;
	}
	void Start() {
		while (!quit) {
		Draw();
		Input();
		Logic();
		sleep;
		}
	}
	void Pause() {
		system("cls");
		// Prints pause in cool format
		std::cout 
			<< "\xDB\xDB\xDB\xDB\xDB\xDC  \xDC\xDB\xDB\xDB\xDB\xDB\xDC  \xDB\xDB  \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDC\n"
			<< "\xDB\xDB  \xDB\xDB  \xDB\xDB   \xDB\xDB  \xDB\xDB  \xDB\xDB  \xDB\xDB      \xDB\xDB      \xDB\xDB   \xDB\xDB\n"
			<< "\xDB\xDB\xDB\xDB\xDB\xDF  \xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB  \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB   \xDB\xDB\n"
			<< "\xDB\xDB      \xDB\xDB   \xDB\xDB  \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB      \xDB\xDB   \xDB\xDB\n"
			<< "\xDB\xDB      \xDB\xDB   \xDB\xDB  \xDF\xDB\xDB\xDB\xDB\xDF  \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDF\n"
			<< "Press any button to continue, q to quit\n";
		char input;

		// Pauses game till user input
		do
			input = _getch();
		while(_kbhit());
		if (input == 'q')
			quit = true;
	}
};

int main() {
	cGameManager main(30, 15);
	main.Start();

	return 0;
}