#include "stdafx.h"
#include "MinionMulligan.h"

MinionMulligan::MinionMulligan()
{
}

MinionMulligan::~MinionMulligan()
{
}

HRESULT MinionMulligan::Init(POINT position, int EnemyNumber)
{
	//����ü ���� ����
	EnemyInfo MinionMulligan;
	MinionMulligan.enemyNumber = EnemyNumber;
	MinionMulligan.enemyRect = RectMakeCenter(position.x, position.y, 50, 50);
	MinionMulligan.enemyHp = 13;
	MinionMulligan.enemyShotSpeed = 5.0f;
	MinionMulligan.enemyShotRange = 500.0f;
	MinionMulligan.enemyShotDelay = 50;
	MinionMulligan.enemySpeed = 3.0f;
	vMinionMulligan.push_back(MinionMulligan);

	enemyAreaCheck = false;

	return S_OK;
}

void MinionMulligan::Release()
{
}

void MinionMulligan::Update()
{
	EnemyAi();
	DeleteEnemy();
}

void MinionMulligan::Render(HDC hdc)
{
	for (i = 0; i < vMinionMulligan.size(); i++)
	{
		//Rectangle(hdc, vMinionMulligan[i].enemyFireRange.left, vMinionMulligan[i].enemyFireRange.top, vMinionMulligan[i].enemyFireRange.right, vMinionMulligan[i].enemyFireRange.bottom);
		Rectangle(hdc, vMinionMulligan[i].enemyRect.left, vMinionMulligan[i].enemyRect.top, vMinionMulligan[i].enemyRect.right, vMinionMulligan[i].enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionMulligan::EnemyAiTime()
{
	switch (vMinionMulligan[i].enemyNumber)
	{
	case 0:
		// AI ���� �ð�
		firstEnemyAiTime++;
		if (firstEnemyAiTime / 60 == 2)
		{
			firstEnemyAiPattern = RND->getFromIntTo(2, 5);
			firstEnemyAiTime = 0;
		}
		break;
	case 1:
		// AI ���� �ð�
		secondEnemyAiTime++;
		if (secondEnemyAiTime / 60 == 2)
		{
			secondEnemyAiPattern = RND->getFromIntTo(2, 5);
			secondEnemyAiTime = 0;
		}
		break;
	case 2:
		// AI ���� �ð�
		thirdEnemyAiTime++;
		if (thirdEnemyAiTime / 60 == 2)
		{
			thirdEnemyAiPattern = RND->getFromIntTo(2, 5);
			thirdEnemyAiTime = 0;
		}
		break;
	}
}

void MinionMulligan::EnemyAi()
{
	for (i = 0; i < vMinionMulligan.size(); i++)
	{
		RECT temp;

		// �� x��, y�� ��ǥ
		vMinionMulligan[i].enemyX = vMinionMulligan[i].enemyRect.left + (vMinionMulligan[i].enemyRect.right - vMinionMulligan[i].enemyRect.left) / 2;
		vMinionMulligan[i].enemyY = vMinionMulligan[i].enemyRect.top + (vMinionMulligan[i].enemyRect.bottom - vMinionMulligan[i].enemyRect.top) / 2;

		// �÷��̾�� ���� ������ �浹��
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionMulligan[i].enemyFireRange))
		{
			// �÷��̾ �Ѿư���.
			enemyAreaCheck = true;
			EnemyShot();
		}

		// ���࿡ �÷��̾ ���� ���� �����ȿ� ���Դٸ� �÷��̾ �Ѿư���.
		if (enemyAreaCheck)
		{
			// getdistance(���� ��ġ x, y, �÷��̾��� ��ġ x, y)
			distance = getDistance(vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionMulligan[i].enemyX) / distance * vMinionMulligan[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionMulligan[i].enemyY) / distance * vMinionMulligan[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionMulligan[i].enemySpeed;
			}

			// + - �ٲ㺸�� �̰� ���� ����� ��� �Ǵ���
			if (vMinionMulligan[i].enemyRect.left >= 10 && vMinionMulligan[i].enemyRect.right <= 950 &&
				vMinionMulligan[i].enemyRect.top >= 10 && vMinionMulligan[i].enemyRect.bottom <= 530)
			{
				collisionCheck = true;
				vMinionMulligan[i].enemyX -= vx;
				vMinionMulligan[i].enemyY -= vy;
			}
			vMinionMulligan[i].enemyRect = RectMakeCenter(vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY, 50, 50);
		}
		// �����ȿ� �÷��̾ ���ٸ� �����ൿ(AI)
		else
		{
			EnemyAiTime();

			switch (vMinionMulligan[i].enemyNumber)
			{
			case 0:
				switch (firstEnemyAiPattern)
				{
				case 1:		// IDLE
					break;
				case 2:		// LEFT
					if (vMinionMulligan[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.left -= vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.right -= vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.left <= 10)
					{
						firstEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionMulligan[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.left += vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.right += vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.right >= 950)
					{
						firstEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionMulligan[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.top -= vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.bottom -= vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.top <= 10)
					{
						firstEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionMulligan[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.top += vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.bottom += vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.bottom >= 530)
					{
						firstEnemyAiPattern = 4;
					}
					break;
				}
				break;
			case 1:
				switch (secondEnemyAiPattern)
				{
				case 1:		// IDLE
					break;
				case 2:		// LEFT
					if (vMinionMulligan[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.left -= vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.right -= vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.left <= 10)
					{
						secondEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionMulligan[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.left += vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.right += vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.right >= 950)
					{
						secondEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionMulligan[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.top -= vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.bottom -= vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.top <= 10)
					{
						secondEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionMulligan[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.top += vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.bottom += vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.bottom >= 530)
					{
						secondEnemyAiPattern = 4;
					}
					break;
				}
				break;
			case 2:
				switch (thirdEnemyAiPattern)
				{
				case 1:		// IDLE
					break;
				case 2:		// LEFT
					if (vMinionMulligan[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.left -= vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.right -= vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.left <= 10)
					{
						thirdEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionMulligan[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.left += vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.right += vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.right >= 950)
					{
						thirdEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionMulligan[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.top -= vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.bottom -= vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.top <= 10)
					{
						thirdEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionMulligan[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionMulligan[i].enemyRect.top += vMinionMulligan[i].enemySpeed;
						vMinionMulligan[i].enemyRect.bottom += vMinionMulligan[i].enemySpeed;
					}
					if (vMinionMulligan[i].enemyRect.bottom >= 530)
					{
						thirdEnemyAiPattern = 4;
					}
					break;
				}
				break;
			}
		}

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		vMinionMulligan[i].enemyFireRange = RectMakeCenter(vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY, 100, 100);
	}

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// ���� ��� �ҷ� �浹
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void MinionMulligan::EnemyShot()
{
	switch (vMinionMulligan[i].enemyNumber)
	{
	case 0:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_0, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, firstEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_90, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, firstEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_180, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, firstEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_270, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, firstEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetFirstEnemyBulletCount();
		break;
	case 1:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_0, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, secondEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_90, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, secondEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_180, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, secondEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_270, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, secondEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetSecondEnemyBulletCount();
		break;
	case 2:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_0, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, thirdEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_90, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, thirdEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_180, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, thirdEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY,
			ANGLE_270, vMinionMulligan[i].enemyShotSpeed, vMinionMulligan[i].enemyShotRange, thirdEnemyBulletCount, vMinionMulligan[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetThirdEnemyBulletCount();
		break;
	}
}

void MinionMulligan::DeleteEnemy(int num)
{
	vMinionMulligan.erase(vMinionMulligan.begin() + num);
}

void MinionMulligan::SetEnemyRectX(int enemyNum, int move)
{
	vMinionMulligan[enemyNum].enemyRect.left += move;
	vMinionMulligan[enemyNum].enemyRect.right += move;
}

void MinionMulligan::SetEnemyRectY(int enemyNum, int move)
{
	vMinionMulligan[enemyNum].enemyRect.top += move;
	vMinionMulligan[enemyNum].enemyRect.bottom += move;
}

void MinionMulligan::DeleteEnemy()
{
	for (i = 0; i < vMinionMulligan.size(); i++)
	{
		if (vMinionMulligan[i].enemyRect.left <= 10 || vMinionMulligan[i].enemyRect.right >= 950 ||
			vMinionMulligan[i].enemyRect.top <= 10 || vMinionMulligan[i].enemyRect.bottom >= 530)
		{
			if (collisionCheck)
			{
				vMinionMulligan.erase(vMinionMulligan.begin() + i);
			}
		}
	}
}