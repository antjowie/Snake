#pragma once
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

enum eEntityDir { STOP, UP, DOWN, LEFT, RIGHT };
enum eStatus { DEAD, ALIVE };

class cEntity {
protected:
	int x, y;
	int originalX, originalY;
	int HP;
	eStatus status;
	eEntityDir direction;
public:
	cEntity(int paramX, int paramY);
	cEntity();
	// Main loop
	// The first function is for player, the second for enemy
	void ChangeDir(eEntityDir newDir);
	void ChangeDir(cEntity *player);
	void Move();
	void LowerHP();
	virtual void Reset() = 0;

	// Get functions
	const inline int getX();
	const inline int getY();
	const inline int getHP();
	eEntityDir getDir();
};

class cPlayer : public cEntity {
public:
	cPlayer(int paramX, int paramY);
	void Reset();
};

class cEnemy : public cEntity {
public:
	cEnemy();
	void Reset();
};

#endif // !ENTITY_H