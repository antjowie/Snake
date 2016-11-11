#pragma once
#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

enum eBulletDir { UP, DOWN, LEFT, RIGHT };

class cWeapon {
	int x; int y;
	int ammo; int originalAmmo;
	int damage;
	int bulletPace;
	int fireRate;
	eBulletDir direction;
public:
	cWeapon(int paramX, int paramY);
	void Move();
	void Shoot();
	void Reload();
	virtual void Damage() = 0;
};

class cFist :public cWeapon {
public:
	cFist(int paramX, int paramY);
};
#endif // !WEAPON_H_INCLUDED
