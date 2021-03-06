#include "Weapon.h"

cBullet::cBullet()
{
	active = false;
}

void cBullet::Generate(int paramX, int paramY, int paramPace, int paramLive, eBulletDir paramDirection)
{
	x = paramX; y = paramY;
	direction = paramDirection;
	pace = paramPace;
	live = paramLive;
	active = true;
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

void cBullet::Reset()
{
	active = false;
}

const inline int cBullet::getX()
{
	return x;
}

const inline int cBullet::getY()
{
	return y;
}

const inline int cBullet::getLive()
{
	return live;
}

const inline bool cBullet::getActive()
{
	return active;
}

const inline void cBullet::changeActive(bool newActive)
{
	active = newActive;
}

cWeapon::cWeapon(int ammoCapacity, int damage, int paramFireRate, int bulletPace, int paramLive, char paramIcon, int paramMaxBullet)
{
	ammo = ammoCapacity; originalAmmo = ammoCapacity;
	fireRate = paramFireRate;
	defaultPace = bulletPace;
	defaultLive = paramLive;
	maxBullet = paramMaxBullet;
	bullet = new cBullet[10];
	icon = paramIcon;
}

cWeapon::~cWeapon()
{
	delete[] bullet;
}

void cWeapon::Shoot(int paramX, int paramY, eBulletDir paramDirection)
{
	if (ammo != 0) {
		for (int i = 0; i < maxBullet; i++)
			if ((bullet + i)->getActive() == false) {
				(bullet + i)->Generate(paramX, paramY, defaultPace, defaultLive, paramDirection);
				break;
			}
		--ammo;
	}
}

void cWeapon::Render()
{
	for (int i = 0; i < maxBullet; i++)
		if ((bullet + i)->getActive() == true)
			(bullet + i)->Move();
}

void cWeapon::Kill()
{
	// Checks all bullets for dead ones
	for (int i = 0; i < maxBullet; i++)
		if ((bullet + i)->getActive() == true && (bullet + i)->getLive() == 0)
			(bullet + i)->changeActive(false);
	
}

void cWeapon::Reload()
{
	ammo = originalAmmo;
}

int cWeapon::Damage()
{
	return damage;
}

const bool cWeapon::getBulletActive(int number)
{
	if ((bullet + number)->getActive() == true)
		return true;
	else
		return false;
}

const int cWeapon::getMaxBullet()
{
	return maxBullet;
}

const int cWeapon::getBulletX(int number)
{
	if ((bullet + number) != nullptr)
		return (bullet + number)->getX();
	else
		return 0;
}

const int cWeapon::getBulletY(int number)
{
	if ((bullet + number) != nullptr)
		return (bullet + number)->getY();
	else
		return 0;
}

const char cWeapon::getBulletIcon()
{
	return icon;
}

const int cWeapon::getAmmo()
{
	return ammo;
}

const int cWeapon::getMaxAmmo()
{
	return originalAmmo;
}

const int cWeapon::getPace()
{
	return defaultPace;
}