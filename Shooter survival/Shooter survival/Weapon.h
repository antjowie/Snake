#pragma once
#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

enum eBulletDir { BULLETUP, BULLETDOWN, BULLETLEFT, BULLETRIGHT };

class cBullet {
	int x; int y;
	int pace;
	int live;
	bool active;
	eBulletDir direction;

public:
	cBullet();
	void Generate(int paramX, int paramY, int paramPace, int paramLive, eBulletDir paramDirection);

	void Move();
	void Reset();
	
	const int getX();
	const int getY();
	const int getLive();
	const bool getActive();
	const void changeActive(bool newActive);

	};

class cWeapon {
	int ammo; int originalAmmo;
	int fireRate;
	char icon;
	int defaultLive;
	int defaultPace;
	int maxBullet;
	cBullet *bullet;
protected:
	int damage;
public:
	cWeapon(int ammoCapacity, int damage, int fireRate, int bulletPace, int paramLive, char paramIcon, int paramMaxBullet);
	~cWeapon();
	void Shoot(int paramX, int paramY, eBulletDir paramDirection);
	void Render();
	void Kill();
	void Reload();
	int Damage();

	const int getMaxBullet();
	const bool getBulletActive(int number);
	const int getBulletX(int number);
	const int getBulletY(int number);
	const char getBulletIcon();
	const int getAmmo();
	const int getMaxAmmo();
	const int getPace();

};
#endif // !WEAPON_H_INCLUDED
