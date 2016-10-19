#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#define fruitRate 10
#define sleep std::this_thread::sleep_for(std::chrono::milliseconds(250))

// Allows us to change matrix size
#define width 21
#define length 21

enum class moveset { up, down, left, right, neutral }direction;

struct entity {
	int x = 1;
	int y = 1;
	entity *next = nullptr;
}*list, *old;

char matrix[width][length];
bool alive;

moveset input();
void insertEntity(char value, entity *snake, entity *fruit);
bool logic(entity *snake, entity *fruit);
void resetMatrix(entity *snake);
void printMatrix();
void spawnFruit(int &counter, entity *snake, entity *fruit);
void checkFruit(entity *snake, entity *fruit);
void addSnake(entity *snake);
void followSnake(entity *snake);

int main() {
	srand(time(0));
	entity *snake = new entity;
	entity *fruit = new entity;
	int counter = fruitRate;

	resetMatrix(snake);
	while (alive == true) {
		printMatrix();
		if (logic(snake, fruit) == false)
			alive = false;
		spawnFruit(counter, snake, fruit);
	}
	std::cout << "You died!\n";
	std::cin.ignore();
	return 0;
}

void resetMatrix(entity *snake) {

	// Makes sure to not move
	direction = moveset::neutral;

	// Loop to go through matrix
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {

			// Fills matrix with dots
			matrix[x][y] = ' ';

			// Adds borders
			if (x == 0)
				matrix[x][y] = '_';
			else if (x == width - 1)
				matrix[x][y] = '=';
			else if (y == 0)
				matrix[x][y] = '|';
			else if (y == length - 1)
				matrix[x][y] = '|';
		}
		std::cout << '\n';
	}

	// Resets snakes location
	snake->x = width / 2;
	snake->y = length / 2;

	alive = true;
}

void printMatrix() {

	// Adds a refresh effect
	for (int i = width + length; i > 0; i--)
		std::cout << '\n';

	// Prints the matrix
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++)
			std::cout << matrix[x][y] << ' ';
	std::cout << '\n';
	}
	sleep;
}

void insertEntity(char value, entity *snake, entity *fruit) {
	
	// List snake
	if (value != 'F')
		list = snake->next;
	
	// List fruit
	else if (value != 'o')
		list = fruit->next;

	while (list != nullptr){
			matrix[list->x][list->y] = value;
			list = list->next;
		}
}

bool logic(entity *snake, entity *fruit) {

	// Remove outdated location
	insertEntity(' ', snake, fruit);
	matrix[snake->x][snake->y] = ' ';

	do {
		// Checks for user input
		if (_kbhit())
			direction = input();

		if (direction == moveset::neutral) {
			std::cout << "Game paused...\nMove to continue.\n";
			direction = input();
		}

		//Allows for an pause function
	} while (direction == moveset::neutral);

	// Makes snake follow eachother
	followSnake(snake);

	// Moveset
	switch (direction) {
	case moveset::up:
		snake->x -= 1;
		break;
	case moveset::left:
		snake->y -= 1;
		break;
	case moveset::down:
		snake->x += 1;
		break;
	case moveset::right:
		snake->y += 1;
		break;
	}

	// Checks for fruit because fruit != ' '
	checkFruit(snake, fruit);

	// Checks for possible death
	if (matrix[snake->x][snake->y] != ' ')
		return false;

	// Checks for lose by 4 fruits
	list = fruit;
	for (int counter = 4; list != nullptr; counter--) {
		if (counter == 0)
			return false;
		list = list->next;
	}
	
	// Inserts entities coords into matrix
	insertEntity('o', snake, fruit);
	insertEntity('F', snake, fruit);

	// Inserts player head in matrix
	matrix[snake->x][snake->y] = 'O';
	return true;
}

moveset input() {
	switch (_getch())
	{
	case 'w':
	case 'W':
		return moveset::up;
		break;
	case 'a':
	case 'A':
		return moveset::left;
		break;
	case 's':
	case 'S':
		return moveset::down;
		break;
	case 'd':
	case 'D':
		return moveset::right;
		break;
	default:
		return moveset::neutral;
		break;
	}
}

void spawnFruit(int &counter, entity *snake, entity *fruit) {
	if (counter == 0) {
		// Gives fruit coordinates
		int tempx = rand() % (width - 2);
		int tempy = rand() % (length - 2);
		tempx++;
		tempy++;

		// Checks if fruit didn't spawn on something
		if (matrix[tempx][tempy] != ' ')
			spawnFruit(counter, snake, fruit);

		// Inserts cords to latest fruit
		list = fruit;
		while (list->next != nullptr)
			list = list->next;
		list->next = new entity;
		list = list->next;
		list->x = tempx;
		list->y = tempy;

		// Inserts fruit
		insertEntity('F', snake, fruit);
		
		// Resets counter for next fruit
		counter = fruitRate;
	}
	counter--;
}

void checkFruit(entity *snake, entity *fruit) {
	if (fruit->next != nullptr)
		for (list = fruit; list->next != nullptr; list = list->next) {

			// If fruit and playerhead coords match
			if (list->next->x == snake->x && list->next->y == snake->y) {

				// Removes graphical indicator
				matrix[list->next->x][list->next->y] = ' ';
				std::cin.ignore();

				// Removes food
				old = list;
				if (list->next->next != nullptr)
					list = list->next->next;
				old->next = nullptr;
				delete old->next;
				
				// Adds new snake part
				addSnake(snake);
				break;
			}
		}
}

void addSnake(entity *snake) {
	list = snake;

	// Locates latest snake
	while (list->next != nullptr)
		list = list->next;
	list->next = new entity;
}

void followSnake(entity *snake) {
	if (snake->next != nullptr) {
		list = snake;
			int tempx = list->x;
			int tempy = list->y;
		while (list->next != nullptr) {
			int tempx1 = list->next->x;
			int tempy1 = list->next->y;
			list->next->x = tempx;
			list->next->y = tempy;
			list = list->next;
			tempx = tempx1;
			tempy = tempy1;
		}
	}
}