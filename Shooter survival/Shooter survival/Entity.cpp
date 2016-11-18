#include "Entity.h"

cEntity::cEntity(int paramX, int paramY)
{
	x = paramX; y = paramY;
	originalX = paramX; originalY = paramY;
	direction = STOP;
	HP = 3;
	alive = true;
}

cEntity::cEntity()
{
}

void cEntity::ChangeDir(eEntityDir newDir)
{
	direction = newDir;
}

void cEntity::ChangeDir(cEntity * player)
{	
	// Move up
	if (y > player->getY() && direction != UP)
		direction = UP;

	// Move down
	else if (y < player->getY() && direction != DOWN)
		direction = DOWN;

	// Move left
	else if (x > player->getX() && direction != LEFT)
		direction = LEFT;

	// Move right
	else if (x < player->getX() && direction != RIGHT)
		direction = RIGHT;
}

void cEntity::Move()
{
	if (cooldown == 0)
		switch (direction)
		{
		case STOP:
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		default:
			break;
		}
	else
		--cooldown;
}

void cEntity::LowerHP()
{
	HP--;
}

const void cEntity::insertX(int paramX)
{
	x = paramX;
}

const void cEntity::insertY(int paramY)
{
	y = paramY;
}

const inline int cEntity::getX()
{
	return x;
}

const inline int cEntity::getY()
{
	return y;
}

const inline int cEntity::getHP()
{
	return HP;
}

const eEntityDir cEntity::getDir()
{
	return direction;
}

const bool cEntity::getAlive()
{
	return alive;
}

cPlayer::cPlayer(int paramX, int paramY) : cEntity(paramX, paramY)
{
}

void cPlayer::Reset()
{
	x = originalX; y = originalY;
}

cEnemy::cEnemy()
{
	HP = 1;
	alive = true;
	cooldown = 2;
}

void cEnemy::Reset()
{
	alive = false;
}
