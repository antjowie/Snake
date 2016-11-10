#include "Entity.h"

cEntity::cEntity(int paramX, int paramY)
{
	x = paramX; y = paramY;
	originalX = paramX; originalY = paramY;
	direction = STOP;
	HP = 3;
}

void cEntity::ChangeDir(eDir newDir)
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
}

void cEntity::LowerHP()
{
	HP--;
}

inline int cEntity::getX()
{
	return x;
}

inline int cEntity::getY()
{
	return y;
}

inline int cEntity::getHP()
{
	return HP;
}

eDir cEntity::getDir()
{
	return direction;
}

cPlayer::cPlayer(int paramX, int paramY): cEntity(paramX,paramY)
{
}

void cPlayer::Reset()
{
	x = originalX; y = originalY;
}

cEnemy::cEnemy(int paramX, int paramY) : cEntity(paramX,paramY)
{
	HP = 1;
}