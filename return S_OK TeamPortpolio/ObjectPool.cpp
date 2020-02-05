#include "stdafx.h"
#include "ObjectPool.h"


ObjectPool::ObjectPool()
{
}


ObjectPool::~ObjectPool()
{
}

void ObjectPool::Init()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		BulletInfo bullet;
		vBulletRepository.push_back(bullet);
	}
}

void ObjectPool::Render(HDC hdc)
{
	sprintf_s((str), "ÃÑ¾Ë ÀÜ¿© : %d", vBulletRepository.size());
	TextOut(hdc, 100, 100, str, strlen(str));
}

void ObjectPool::SetBulletVector(BulletInfo vSpentBullet)
{
	vBulletRepository.push_back(vSpentBullet);

}

BulletInfo ObjectPool::GetBullet()
{
	BulletInfo getBullet;
	getBullet = vBulletRepository.back();
	vBulletRepository.pop_back();
	return getBullet;
}
