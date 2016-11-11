#include <iostream>
#include <time.h>
#include <conio.h>

#include "Entity.h"
//#include "Weapon.h"

class cGameManager {
	int width, heigth;
	char up, down, left, right, shootUp, shootDown, shootLeft, shootRight, reload, pause;
	bool quit;
	cEntity *player;
	cEntity *enemy;
	int score;
public:
	cGameManager(int paramX, int paramY) {
		srand(time(NULL));
		width = paramX; heigth = paramY;
		up = 'w';	left = 'a';		
		down = 's';	right = 'd'; 
		shootUp = 'i';	shootLeft = 'j';
		shootDown = 'k'; shootRight = 'l';
		reload = 'r'; pause = 'p';
		player = new cPlayer(paramX / 2, paramY / 2);
		enemy = new cEnemy[2];
		}

	~cGameManager() {
		delete player;
		delete[] enemy;
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

				// Player
				if (x == player->getX() && y == player->getY())
					std::cout << '\x9D';

				else std::cout << ' ';

				// Rigth wall
				if(x == width - 1)
					std::cout << '\xDB';

			}
			std::cout << '\n';
		}
		// Lower wall
		for (int x = 0; x < width + 2; x++)
			std::cout << '\xDF';

	}
	void Input() {
		if (kbhit()) {
			char current = getch();

			// Player move
			if (current == up)
				player->ChangeDir(UP);
			if (current == down)
				player->ChangeDir(DOWN);
			if (current == left)
				player->ChangeDir(LEFT);
			if (current == right)
				player->ChangeDir(RIGHT);
		
			// Fire
			if (current == shootUp)
				weapon->shootDir(UP);
		}
	}
	void Logic() {

	}
	void ScoreUp() {

	}
	void GenerateEnemy(int ammount) {

	}
	void Start() {

	}
	void Pause() {

	}
};

int main() {
	cGameManager main(30, 15);
	main.Draw();



	return 0;
}