#include "stdafx.h"
#include "BulletManager.h"


BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
}

HRESULT BulletManager::Init()
{
	// �Ѿ� �̹��� �߰�
	IMAGEMANAGER->addImage("playerBullet", "images/playerBullet.bmp", 18 * 2, 22 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemyBullet", "images/enemyBullet.bmp", 18, 18, true, RGB(255, 0, 255));
	
	return S_OK;
}

void BulletManager::Release()
{
}

void BulletManager::Update()
{

}

void BulletManager::Render(HDC hdc)
{
}

void BulletManager::ShootBullet(string imageName, vector<BulletInfo>& bulletVector, float x, float y, float angle, float speed, float range, int count, int interval)
{
	// ī��Ʈ�� ���͹� ��� 0�� �ɶ����� ���� �������ش�.
	if (count % interval == 0)
	{

		/*
			image* bulletImage;
			float angle;
			float speed;
			float bulletX, bulletY;
			float unitX, unitY;
			float range;
			RECT rect;
		*/
		BulletInfo bullet;
		bullet = OBJECTPOOL->GetBullet();
		bullet.bulletImage = IMAGEMANAGER->findImage(imageName);
		bullet.angle = angle;
		bullet.speed = speed;
		bullet.bulletX = bullet.unitX = x;
		bullet.bulletY = bullet.unitY = y;
		bullet.range = range;
		bullet.rect = RectMakeCenter(bullet.bulletX, bullet.bulletY, bullet.bulletImage->getWidth(), bullet.bulletImage->getHeight());
		bulletVector.push_back(bullet);
	}
}

void BulletManager::MoveBullet(vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator & bulletIter)
{
	// �־�� ������ ���ͷ����͸� ���鼭 ���� �������� �Ѿ��� �������ش�.
	for (bulletIter = bulletVector.begin(); bulletIter != bulletVector.end();)
	{
		bulletIter->bulletX += cosf(bulletIter->angle) * bulletIter->speed;
		bulletIter->bulletY += -sinf(bulletIter->angle) * bulletIter->speed;

		bulletIter->rect = RectMakeCenter(bulletIter->bulletX, bulletIter->bulletY, bulletIter->bulletImage->getWidth(), bulletIter->bulletImage->getHeight());
		//if (400 < getDistance(bulletIter->x, bulletIter->y, bulletIter->fireX, bulletIter->fireY))
		//{
		//	bulletIter->y += 1;
		//}
		RECT temp;
		if (bulletIter->range < getDistance(bulletIter->bulletX, bulletIter->bulletY, bulletIter->unitX, bulletIter->unitY) ||
			IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &bulletIter->rect))
		{
			OBJECTPOOL->SetBulletVector(bulletVector.front());
			bulletIter = bulletVector.erase(bulletIter);
		}
		else ++bulletIter;
	}
}

void BulletManager::RenderBullet(HDC hdc, vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator & bulletIter)
{
	//���ͷ����͸� ���鼭 �Ѿ��� �׷��ش�.
	bulletIter = bulletVector.begin();

	for (bulletIter; bulletIter != bulletVector.end(); ++bulletIter)
	{
		bulletIter->bulletImage->render(hdc, bulletIter->rect.left, bulletIter->rect.top);
	}
}
