#pragma once
#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

enum eBulletDir { BULLETUP, BULLETDOWN, BULLETLEFT, BULLETRIGHT };

class cBullet {
	int x; int y;
	int pace;
	int live;
	eBulletDir direction;

public:
	cBullet(int paramX, int paramY, int paramPace, int paramLive, eBulletDir paramDirection);
	void Move();

	inline int getX();
	inline int getY();
	inline int getLive();
	};

class cWeapon {
	int ammo; int originalAmmo;
	int fireRate;
	int live;
protected:
	int pace;
	int damage;
	cBullet *bullet1;
	cBullet *bullet2;
	cBullet *bullet3;
public:
	cWeapon(int ammoCapacity, int damage, int fireRate, int bulletPace);
	~cWeapon();
	void Shoot(int paramX, int paramY, eBulletDir paramDirection);
	void Render();
	void Kill();
	void Reload();
	virtual int Damage() = 0;

};

class cFist :public cWeapon {
public:
	cFist(int ammoCapacity, int damage, int fireRate, int bulletPace);
	int Damage();
};
#endif // !WEAPON_H_INCLUDED
