#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#define sleep std::this_thread::sleep_for(std::chrono::milliseconds(60))


enum eDir {STOP, RIGHTDOWN, RIGHT, RIGHTUP, LEFTDOWN, LEFT, LEFTUP};

class cBall{
	/* Manages:
		Ball movement
		Ball reset
		Ball direction
	*/
	int x, y;
	int originalX, originalY;
	eDir ballDir;
public:
	cBall(int posX, int posY){
		x = posX; y = posY;
		originalX = posX, originalY = posY;
		ballDir = STOP;
	}
	
	void Reset() {
		x = originalX; y = originalY;
		ballDir = STOP;
	}

	// Inserts new direction
	void ChangeDir(eDir newDir) {
		ballDir = newDir;
	}

	// Declares new direction upon collision or start
	void RandomDir() {
		ballDir = eDir (rand() % 6 + 1);
	}

	void Move()
	{
		switch (ballDir)
		{
		case STOP:
			break;
		case RIGHTDOWN:
			x++; y++;
			break;
		case RIGHT:
			x++;
			break;
		case RIGHTUP:
			x++; y--;
			break;
		case LEFTDOWN:
			x--; y++;
			break;
		case LEFT:
			x--;
			break;
		case LEFTUP:
			x--; y--;
			break;
		default:
			break;
		}
	}

	inline int getX() { return x; }

	inline int getY() { return y; }

	inline eDir getDirection() { return ballDir; }

	// Prints ball cords
	friend std::ostream & operator<<(std::ostream & o, cBall c) {
		o << "Ball [" << c.x << ',' << c.y << "] [" << c.ballDir << "]\n";
		return o;
	}
};

class cPaddle {
	/* Manages:
		Paddle movement
		Paddle reset
	*/
	int x, y;
	int originalX, originalY;
public:
	cPaddle(int posX, int posY) {
		x = posX; y = posY;
		originalX = posX; originalY = posY;
	}

	void Reset() {
		x = originalX; y = originalY;
	}

	void MoveUp() { y--; }

	void MoveDown() { y++; }

	inline int getX() { return x; }

	inline int getY() { return y; }

	friend std::ostream & operator<<(std::ostream & o, cPaddle c) {
		o << "Paddle [" << c.x << ',' << c.y << "]\n";
		return o;
	}
};

class cGameMananger {
	/* Manages:
		Player input (object movement)
		Game logic (deaths, score, player ammount)
		Game graphics/draw
		Game loop
	*/
	int width, height;
	int score1, score2, targetScore;
	char up1, up2, down1, down2;
	bool quit;
	cBall *ball;
	cPaddle *player1, *player2;
public:
	cGameMananger(int paramWidth, int paramHeigth, int maxScore) {
		srand(time(NULL));
		width = paramWidth;
		height = paramHeigth;
		up1 =   'w';   up2 = 'i';
		down1 = 's'; down2 = 'k';
		quit = false;
		score1 = score2 = 0;
		targetScore = maxScore;
		ball = new cBall(paramWidth / 2, paramHeigth / 2);
		player1 = new cPaddle(1, paramHeigth / 2 - 2);
		player2 = new cPaddle(paramWidth - 2, paramHeigth / 2 - 2);
	}

	~cGameMananger() {
		delete ball, player1, player2;
	}

	void Draw() {
		system("cls");
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		// Upper wall
		for (int i = 0; i < width + 2; i++)
			std::cout << '\xB1';
		std::cout << std::endl;

		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++) {

				// Left wall
				if (j == 0)
					std::cout << '\xB1';

				// Ball print
				if (ballX == j && ballY == i)
					std::cout << 'O';

				// Paddle print
				else if (player1x == j && player1y == i)
					std::cout << '\xDB';
				else if (player1x == j && player1y + 1 == i)
					std::cout << '\xDB';
				else if (player1x == j && player1y + 2 == i)
					std::cout << '\xDB';
				else if (player1x == j && player1y + 3 == i)
					std::cout << '\xDB';

				else if (player2x == j && player2y == i)
					std::cout << '\xDB';
				else if (player2x == j && player2y + 1 == i)
					std::cout << '\xDB';
				else if (player2x == j && player2y + 2 == i)
					std::cout << '\xDB';
				else if (player2x == j && player2y + 3 == i)
					std::cout << '\xDB';
				else
				std::cout << ' ';

				// Right wall
				if (j == width - 1)
					std::cout << '\xB1';
			}
			std::cout << std::endl;
	}

		// Lower wall
		for (int i = 0; i < width + 2; i++)
			std::cout << '\xB1';
		std::cout << std::endl << "Score:\nPlayer 1: " << score1 << "\tPlayer 2: " << score2 << std::endl;
	}

	void Input() {

		//Moves the ball
		ball->Move();

		int player1y = player1->getY();
		int player2y = player2->getY();

		if (_kbhit()) {
			char current = _getch();

			// Our moveset
			if (current == up1)
				if(player1y > 0)
				player1->MoveUp();
			if (current == up2)
				if (player2y > 0)
					player2->MoveUp();
			if (current == down1)
				if (player1y + 4 < height)
					player1->MoveDown();
			if (current == down2)
				if (player2y + 4 < height)
					player2->MoveDown();
		
			// Waits for an input to begin
			if (ball->getDirection() == STOP)
				ball->RandomDir();
		
			if (current == 'q')
				quit = true;
		}
	}

	void Logic() {
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		// Left paddle collision
		for (int i = 0; i < 4; i++)
			if (ballX == player1x && ballY == player1y + i)
				ball->ChangeDir(eDir(rand() % 3 + 1));
		// Right passle collision
		for (int i = 0; i < 4; i++)
			if (ballX == player2x && ballY == player2y + i)
				ball->ChangeDir(eDir(rand() % 6 + 4));

		// Upper wall collision
		if (ballY == 0)
			ball->ChangeDir(ball->getDirection() == LEFTUP ? LEFTDOWN : RIGHTDOWN);
		// Lower wall collision
		if (ballY == height - 1)
			ball->ChangeDir(ball->getDirection() == LEFTDOWN ? LEFTUP : RIGHTUP);
		// Rigth wall collision (player 1 scores)
		if (ballX == width - 1)
			ScoreUp(player1);
		// Left wall collision (player 2 scores)
		else if (ballX == 0)
			ScoreUp(player2);

	}

	void ScoreUp(cPaddle *player) {
		if (player == player1)
			score1++;
		else
			score2++;

		if (score1 == targetScore) {
			std::cout << "Player 1 won!\n";
			quit = true;
		}
		if (score2 == targetScore) {
			std::cout << "Player 2 won!\n";
			quit = true;
		}

		// Resets locations
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}

	void Start() {
		while (!quit) {
			Draw();
			Input();
			Logic();
			sleep;
		}
	}
};

int main() {
	int width, height, maxScore;

	std::cout << "\tWelcome to Pong!"
		"\nPong currently has no AI to play against."
		"\nPlayer 1 uses \'w\' and \'s\' to move, player 2 uses \'i\' and \'k\'."
		"\nCorrespondingly up and down. For now, please enter the preferred width (40 recommended)"
		"\n(enter 0 if you want the default values)."
		"\n -";
	std::cin >> width;
	if (width != 0) {
	std::cout << "Now please, enter the preferred height (15 recommended).\n -";
	std::cin >> height;
	std::cout << "All set! do note that pace scaling has not been implemented yet. If you notice any screen flikkering,"
		"\nyour width or height value may be to large. Now please, enter the target score."
		"\n - ";
	std::cin >> maxScore;
	std::cout << "Saving settings has not been implemented yet. Press enter to start...";
	std::cin.ignore();
	cGameMananger custom(width, height, maxScore);
	custom.Start();
	}
	else {
		cGameMananger main(40, 15, 10);
		main.Start();
	}
	std::cin.ignore();
	return 0;
}