#include "stdafx.h"
#include "Monstro.h"

Monstro::Monstro()
{
}

Monstro::~Monstro()
{
}

HRESULT Monstro::Init(POINT position)
{
	//����ü ���� ����
	EnemyInfo Monstro;
	Monstro.enemyImage = IMAGEMANAGER->addImage("monstro", "images/monster/monstro.bmp", 192, 192, true, RGB(255, 0, 255));
	Monstro.enemyRect = RectMakeCenter(position.x, position.y, 120, 60);
	Monstro.enemyHp = 250;
	Monstro.enemyShotSpeed = 5.0f;
	Monstro.enemyShotRange = 500.0f;
	Monstro.enemyShotDelay = 30;
	Monstro.enemySpeed = 2.0f;
	vMonstro.push_back(Monstro);

	rndX = RND->getFromIntTo(-100, 100);
	rndY = RND->getFromIntTo(-100, 100);

	firstEnemyAiPattern = 1;

	return S_OK;
}

void Monstro::Release()
{
}

void Monstro::Update()
{
	EnemyAi();
}

void Monstro::Render(HDC hdc)
{
	for (i = 0; i < vMonstro.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			//Rectangle(hdc, vMonstro[i].enemyFireRange.left, vMonstro[i].enemyFireRange.top, vMonstro[i].enemyFireRange.right, vMonstro[i].enemyFireRange.bottom);
			Rectangle(hdc, vMonstro[i].enemyRect.left, vMonstro[i].enemyRect.top, vMonstro[i].enemyRect.right, vMonstro[i].enemyRect.bottom);
			HBRUSH brush = CreateSolidBrush(RGB(51, 153, 0));
			FillRect(hdc, &vMonstro[i].enemyRect, brush);
			DeleteObject(brush);
		}

		switch (firstEnemyAiPattern)
		{
		case 1:
			IMAGEMANAGER->render("monstro", hdc, vMonstro[i].enemyRect.left - 38, vMonstro[i].enemyRect.top - 80);
			break;
		case 2:
			IMAGEMANAGER->render("monstro", hdc, vMonstro[i].enemyRect.left - 38, vMonstro[i].enemyRect.top - 80);
			break;
		case 3:
			IMAGEMANAGER->render("monstro", hdc, vMonstro[i].enemyRect.left - 38, vMonstro[i].enemyRect.top - 80);
			break;
		case 4:
			if (teleportImage)
			{
				IMAGEMANAGER->render("monstro", hdc, vMonstro[i].enemyRect.left - 38, vMonstro[i].enemyRect.top - 80);
			}
			break;
		}
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void Monstro::EnemyAiTime()
{
	// AI ���� �ð�
	firstEnemyAiTime++;
	if (firstEnemyAiTime / 60 == 2)
	{
		firstEnemyAiPattern = RND->getFromIntTo(2, 4);
		firstEnemyAiTime = 0;
	}
}

void Monstro::EnemyAi()
{
	for (i = 0; i < vMonstro.size(); i++)
	{
		RECT temp;

		// �� x��, y�� ��ǥ
		vMonstro[i].enemyX = vMonstro[i].enemyRect.left + (vMonstro[i].enemyRect.right - vMonstro[i].enemyRect.left) / 2;
		vMonstro[i].enemyY = vMonstro[i].enemyRect.top + (vMonstro[i].enemyRect.bottom - vMonstro[i].enemyRect.top) / 2;

		switch (firstEnemyAiPattern)
		{
		case 1:
			teleport = false;
			jump = false;
			snowPattern = false;
			EnemyAiTime();   // AI����
			break;
		case 2:      // ���� �� ������ �߻�
			jump = true;
			snowPattern = false;
			teleport = false;
			jumpPower = 40.0f;
			break;
		case 3:      // 90�� ���� ����
			jump = false;
			snowPattern = true;
			teleport = false;
			break;
		case 4:      // �÷��̾��� ��ó�� �����̵�
			jump = false;
			snowPattern = false;
			teleport = true;
			break;
		}
		// ����2 : ����
		if (jump)
		{
			jumpCount++;

			if (jumpCount < 21)
			{
				gravity = 5.0f;
				vMonstro[i].enemyRect.top -= jumpPower;
				vMonstro[i].enemyRect.bottom -= jumpPower;
				jumpPower -= gravity;
			}
			else if (jumpCount > 20 && jumpCount < 71)
			{
				// getdistance(���� ��ġ x, y, �÷��̾��� ��ġ x, y)
				distance = getDistance(vMonstro[i].enemyX, vMonstro[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());
				if (distance)
				{
					// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
					vx = ((WINSIZEX / 2) - vMonstro[i].enemyX) / distance * vMonstro[i].enemySpeed * 5;
					vy = ((WINSIZEY / 2) - vMonstro[i].enemyY) / distance * vMonstro[i].enemySpeed * 5;
				}
				else
				{
					vx = 0;
					vy = vMonstro[i].enemySpeed;
				}
				vMonstro[i].enemyX += vx * 5;
				vMonstro[i].enemyY += vy * 5;
				vMonstro[i].enemyRect = RectMakeCenter(vMonstro[i].enemyX, vMonstro[i].enemyY, 120, 60);
			}
			else if (jumpCount > 70 && jumpCount < 100)
			{
				EnemyAllShot();
			}
			else
			{
				firstEnemyAiPattern = 1;
			}
		}
		else
		{
			jumpCount = 0;
		}
		// ����3 : ����
		if (snowPattern)
		{
			shotCount++;

			if (shotCount > 0 && shotCount < 31)
			{
				EnemySnowShot();
			}
			else
			{
				firstEnemyAiPattern = 1;
			}
		}
		else
		{
			shotCount = 0;
		}
		// ����4 : �����̵�
		if (teleport)
		{
			teleportImage = true;
			teleportCount++;

			if (teleportCount > 0 && teleportCount < 300)
			{
				teleportImage = false;

				// getdistance(���� ��ġ x, y, �÷��̾��� ��ġ x, y)
				distance = getDistance(vMonstro[i].enemyX, vMonstro[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());
				if (distance)
				{
					// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
					vx = ((PLAYERMANAGER->GetPlayerHitRectX() + rndX) - vMonstro[i].enemyX) / distance * vMonstro[i].enemySpeed;
					vy = ((PLAYERMANAGER->GetPlayerHitRectY() + rndY) - vMonstro[i].enemyY) / distance * vMonstro[i].enemySpeed;
				}
				else
				{
					vx = 0;
					vy = vMonstro[i].enemySpeed;
				}
				vMonstro[i].enemyX += vx;
				vMonstro[i].enemyY += vy;
				vMonstro[i].enemyRect = RectMakeCenter(vMonstro[i].enemyX, vMonstro[i].enemyY, 120, 60);
			}
			else
			{
				firstEnemyAiPattern = 3;
			}
		}
		else
		{
			teleportCount = 0;
		}
	}

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);

	// ���� ��� �ҷ� �浹
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void Monstro::EnemySnowShot()
{
	// ĳ������ x���� �������� ����ó�� �͹���� �����Ѵ�.
	if (vMonstro[i].enemyX > PLAYERMANAGER->GetPlayerHitRectX())
	{
		for (int j = 1; j <= 15; j++)
		{
			BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMonstro[i].enemyX - 100, vMonstro[i].enemyY,
				ANGLE_0 - j, vMonstro[i].enemyShotSpeed, vMonstro[i].enemyShotRange, firstEnemyBulletCount + j, vMonstro[i].enemyShotDelay);
		}
	}
	else if (vMonstro[i].enemyX <= PLAYERMANAGER->GetPlayerHitRectX())
	{
		for (int j = 1; j <= 15; j++)
		{
			BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMonstro[i].enemyX + 100, vMonstro[i].enemyY,
				ANGLE_0 - j, vMonstro[i].enemyShotSpeed, vMonstro[i].enemyShotRange, firstEnemyBulletCount + j, vMonstro[i].enemyShotDelay);
		}
	}

	// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
	SetFirstEnemyBulletCount();
}

void Monstro::EnemyAllShot()
{
	// ������ �͹���� ��Ѹ���.
	for (int j = 1; j <= 15; j++)
	{
		int rnd = RND->getInt(100);

		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMonstro[i].enemyX, vMonstro[i].enemyY,
			ANGLE_0 + rnd, vMonstro[i].enemyShotSpeed, vMonstro[i].enemyShotRange, secondEnemyBulletCount, vMonstro[i].enemyShotDelay);
	}

	// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
	SetSecondEnemyBulletCount();
}

void Monstro::DeleteEnemy(int num)
{
	vMonstro.erase(vMonstro.begin() + num);
}

void Monstro::SetEnemyRectX(int enemyNum, int move)
{
	vMonstro[enemyNum].enemyRect.left += move;
	vMonstro[enemyNum].enemyRect.right += move;
}

void Monstro::SetEnemyRectY(int enemyNum, int move)
{
	vMonstro[enemyNum].enemyRect.top += move;
	vMonstro[enemyNum].enemyRect.bottom += move;
}