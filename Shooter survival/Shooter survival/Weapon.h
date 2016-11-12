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
	
	const inline int getX();
	const inline int getY();
	const inline int getLive();
	const inline bool getActive();
	const inline void changeActive(bool newActive);

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

	const bool getBulletState(int number);
	const int getMaxBullet();
	const int getBulletX(int number);
	const int getBulletY(int number);
	const char getBulletIcon(int number);

	virtual int Damage() = 0;

};

class cFist :public cWeapon {
public:
	cFist(int ammoCapacity, int damage, int fireRate, int bulletPace , int bulletLive, char paramIcon);
	int Damage();
};
#endif // !WEAPON_H_INCLUDED
