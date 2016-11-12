#include "Weapon.h"

cBullet::cBullet(int paramX, int paramY, int paramPace, int paramLive, eBulletDir paramDirection)
{
	x = paramX; y = paramY;
	direction = paramDirection;
	pace = paramPace;
	live = paramLive;
}

void cBullet::Move()
{
	switch (direction)
	{
	case BULLETUP:
		--y;
		break;
	case BULLETDOWN:
		++y;
		break;
	case BULLETLEFT:
		--x;
		break;
	case BULLETRIGHT:
		++x;
		break;
	default:
		break;
	}
	--live;
}

inline int cBullet::getX()
{
	return x;
}

inline int cBullet::getY()
{
	return y;
}

inline int cBullet::getLive()
{
	return live;
}

cWeapon::cWeapon(int ammoCapacity, int damage, int paramFireRate, int bulletPace)
{
	ammo = ammoCapacity; originalAmmo = ammoCapacity;
	fireRate = paramFireRate;
	pace = bulletPace;
}

cWeapon::~cWeapon()
{
	delete bullet1, bullet2, bullet3;
}

void cWeapon::Shoot(int paramX, int paramY, eBulletDir paramDirection)
{
	if (ammo != 0) {

	if (bullet1 == nullptr)
		bullet1 = new cBullet(paramX, paramY, pace, live, paramDirection);
	else if (bullet2 == nullptr)
		bullet2 = new cBullet(paramX, paramY, pace, live, paramDirection);
	else if (bullet3 == nullptr)
		bullet3 = new cBullet(paramX, paramY, pace, live, paramDirection);
	--ammo;
	}
}

void cWeapon::Render()
{
	if (bullet1 != nullptr)
		bullet1->Move();
	if (bullet1 != nullptr)
		bullet2->Move();
	if (bullet1 != nullptr)
		bullet3->Move();
}

void cWeapon::Kill()
{
	if (bullet1 != nullptr && bullet1->getLive() == 0)
		delete bullet1;
	if (bullet2 != nullptr && bullet2->getLive() == 0)
		delete bullet2;	
	if (bullet3 != nullptr && bullet3->getLive() == 0)
		delete bullet3;
}

void cWeapon::Reload()
{
	ammo = originalAmmo;
}

cFist::cFist(int ammoCapacity, int damage, int fireRate, int bulletPace) :cWeapon(ammoCapacity, damage, fireRate, bulletPace)
{
}

int cFist::Damage()
{
	return damage;
}

