#include <iostream>
#include <time.h>
#include <thread>
#include <chrono>
#include <conio.h>

#define sleep std::this_thread::sleep_for(std::chrono::milliseconds(100))
#include "Weapon.h"
#include "Entity.h"

class cGameManager {
	int width, heigth;
	char up, down, left, right, shootUp, shootDown, shootLeft, shootRight, reload, pause;
	bool quit;
	cEntity *player;
	cEntity *enemy;
	cWeapon *weapon;
	int score;
	int enemyAmmount;
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
		weapon = new cFist(9999,1,1,1,1,'#');
		quit = false;
		score = 0;
	}

	~cGameManager() {
		delete player, weapon;
		//delete[] enemy;
	}

	void Draw() {
		system("cls");

		// Upper wall
		for (int x = 0; x < width+2; x++)
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
					if (x == weapon->getBulletX(i) && y == weapon->getBulletY(i)) {
						std::cout << 'x' << weapon->getBulletX(i) << 'y' << weapon->getBulletY(i);
						std::cin.ignore();
						foundBullet = true;
						break;
					}

				// Player
				if (foundBullet == false) {

				if (x == player->getX() && y == player->getY())
					std::cout << '\x9D';

				else
						std::cout << ' ';
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
			if (current == shootUp)
				weapon->Shoot(player->getX(), player->getY(), BULLETUP);
			if (current == shootDown)
				weapon->Shoot(player->getX(), player->getY(), BULLETDOWN);
			if (current == shootLeft)
				weapon->Shoot(player->getX(), player->getY(), BULLETLEFT);
			if (current == shootRight)
				weapon->Shoot(player->getX(), player->getY(), BULLETRIGHT);

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


	}
	void ScoreUp() {

	}
	void GenerateEnemy(int ammount) {
		enemy = new cEnemy[ammount];
		enemyAmmount = ammount;
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
	cBullet *bullet[10];
	for (int i = 0; i < 10; i++) {
		int result = ((*(bullet + i))->getActive() ? 1 : 0);
		std::cout << result << '\n';
	}


	return 0;
}