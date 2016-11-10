#pragma once
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

enum eDir { STOP, UP, DOWN, LEFT, RIGHT };

class cEntity {
protected:
	int x, y;
	int originalX, originalY;
	int HP;
	eDir direction;
public:
	cEntity(int paramX, int paramY);

	// Main loop
	// The first function is for player, the second for enemy
	void ChangeDir(eDir newDir);
	void ChangeDir(cEntity *player);
	void Move();
	void LowerHP();
	virtual void Reset() = 0;

	// Get functions
	inline int getX();
	inline int getY();
	inline int getHP();
	eDir getDir();
};

class cPlayer : public cEntity {
public:
	cPlayer(int paramX, int paramY);
	void Reset();
};

class cEnemy : public cEntity {
public:
	cEnemy(int paramX, int paramY);
};

#endif // !ENTITY_H