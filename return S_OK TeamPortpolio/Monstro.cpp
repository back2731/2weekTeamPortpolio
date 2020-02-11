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
	Monstro.enemyRect = RectMakeCenter(position.x, position.y, 150, 150);
	Monstro.enemyHp = 250;
	Monstro.enemyShotSpeed = 5.0f;
	Monstro.enemyShotRange = 500.0f;
	Monstro.enemyShotDelay = 150;
	Monstro.enemySpeed = 2.5f;
	vMonstro.push_back(Monstro);

	enemyAreaCheck = false;

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
		//Rectangle(hdc, vMonstro[i].enemyFireRange.left, vMonstro[i].enemyFireRange.top, vMonstro[i].enemyFireRange.right, vMonstro[i].enemyFireRange.bottom);
		Rectangle(hdc, vMonstro[i].enemyRect.left, vMonstro[i].enemyRect.top, vMonstro[i].enemyRect.right, vMonstro[i].enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void Monstro::EnemyAiTime()
{
	// AI ���� �ð�
	firstEnemyAiTime++;
	if (firstEnemyAiTime / 60 == 2)
	{
		firstEnemyAiPattern = RND->getFromIntTo(2, 5);
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

		// �÷��̾�� ���� ������ �浹��
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMonstro[i].enemyFireRange))
		{
			// �÷��̾ �Ѿư���.
			enemyAreaCheck = false;
		}

		EnemyShot();

		// ���࿡ �÷��̾ ���� ���� �����ȿ� ���Դٸ� �÷��̾ �Ѿư���.
		if (enemyAreaCheck)
		{
			// getdistance(���� ��ġ x, y, �÷��̾��� ��ġ x, y)
			distance = getDistance(vMonstro[i].enemyX, vMonstro[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMonstro[i].enemyX) / distance * vMonstro[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMonstro[i].enemyY) / distance * vMonstro[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMonstro[i].enemySpeed;
			}

			// + - �ٲ㺸�� �̰� ���� ����� ��� �Ǵ���
			vMonstro[i].enemyX += vx;
			vMonstro[i].enemyY += vy;
			vMonstro[i].enemyRect = RectMakeCenter(vMonstro[i].enemyX, vMonstro[i].enemyY, 150, 150);
		}
		// �����ȿ� �÷��̾ ���ٸ� �����ൿ(AI)
		else
		{
			EnemyAiTime();

			switch (firstEnemyAiPattern)
			{
			case 1:		// IDLE
				break;
			case 2:		// LEFT
				if (vMonstro[i].enemyRect.left > 0) // ���� �̵� ���� ����
				{
					vMonstro[i].enemyRect.left -= vMonstro[i].enemySpeed;
					vMonstro[i].enemyRect.right -= vMonstro[i].enemySpeed;
				}
				if (vMonstro[i].enemyRect.left <= 10)
				{
					firstEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMonstro[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
				{
					vMonstro[i].enemyRect.left += vMonstro[i].enemySpeed;
					vMonstro[i].enemyRect.right += vMonstro[i].enemySpeed;
				}
				if (vMonstro[i].enemyRect.right >= 950)
				{
					firstEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMonstro[i].enemyRect.top > 0) // ���� �̵� ���� ����
				{
					vMonstro[i].enemyRect.top -= vMonstro[i].enemySpeed;
					vMonstro[i].enemyRect.bottom -= vMonstro[i].enemySpeed;
				}
				if (vMonstro[i].enemyRect.top <= 10)
				{
					firstEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMonstro[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
				{
					vMonstro[i].enemyRect.top += vMonstro[i].enemySpeed;
					vMonstro[i].enemyRect.bottom += vMonstro[i].enemySpeed;
				}
				if (vMonstro[i].enemyRect.bottom >= 530)
				{
					firstEnemyAiPattern = 4;
				}
				break;
			}
		}

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		vMonstro[i].enemyFireRange = RectMakeCenter(vMonstro[i].enemyX, vMonstro[i].enemyY, WINSIZEX, WINSIZEY);
	}

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// ���� ��� �ҷ� �浹
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void Monstro::EnemyShot()
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
	else if (vMonstro[i].enemyX < PLAYERMANAGER->GetPlayerHitRectX())
	{
		for (int j = 1; j <= 15; j++)
		{
			BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMonstro[i].enemyX + 100, vMonstro[i].enemyY,
				ANGLE_0 - j, vMonstro[i].enemyShotSpeed, vMonstro[i].enemyShotRange, firstEnemyBulletCount + j, vMonstro[i].enemyShotDelay);
		}
	}

	// ������ �͹���� ��Ѹ���.
	//for (int j = 1; j <= 15; j++)
	//{
	//	int rnd = RND->getInt(100);

	//	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMonstro[i].enemyX, vMonstro[i].enemyY,
	//		ANGLE_0 + rnd, vMonstro[i].enemyShotSpeed, vMonstro[i].enemyShotRange, firstEnemyBulletCount, vMonstro[i].enemyShotDelay);
	//}

	// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
	SetFirstEnemyBulletCount();
}

void Monstro::DeleteEnemy(int num)
{
	vMonstro.erase(vMonstro.begin() + num);
}
