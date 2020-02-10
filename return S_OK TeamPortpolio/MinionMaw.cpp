#include "stdafx.h"
#include "MinionMaw.h"

MinionMaw::MinionMaw()
{
}

MinionMaw::~MinionMaw()
{
}

HRESULT MinionMaw::Init(POINT position, int EnemyNumber)
{
	//����ü ���� ����
	EnemyInfo minionMaw;
	minionMaw.enemyNumber = EnemyNumber;
	minionMaw.enemyRect = RectMakeCenter(position.x, position.y, 30, 30);
	minionMaw.enemyHp = 25;
	minionMaw.enemyShotSpeed = 5.0f;
	minionMaw.enemyShotRange = 500.0f;
	minionMaw.enemyShotDelay = 50;
	minionMaw.enemySpeed = 1.5f;
	vMinionMaw.push_back(minionMaw);

	enemyAreaCheck = false;
	enemyCollision = false;

	return S_OK;
}

void MinionMaw::Release()
{
}

void MinionMaw::Update()
{
	EnemyAi();
}

void MinionMaw::Render(HDC hdc)
{
	for (i = 0; i < vMinionMaw.size(); i++)
	{
		//Rectangle(hdc, vMinionMaw[i].enemyFireRange.left, vMinionMaw[i].enemyFireRange.top, vMinionMaw[i].enemyFireRange.right, vMinionMaw[i].enemyFireRange.bottom);
		Rectangle(hdc, vMinionMaw[i].enemyRect.left, vMinionMaw[i].enemyRect.top, vMinionMaw[i].enemyRect.right, vMinionMaw[i].enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionMaw::EnemyAiTime()
{
	switch (vMinionMaw[i].enemyNumber)
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

void MinionMaw::EnemyAi()
{
	for (i = 0; i < vMinionMaw.size(); i++)
	{
		RECT temp;

		// �� x��, y�� ��ǥ
		vMinionMaw[i].enemyX = vMinionMaw[i].enemyRect.left + (vMinionMaw[i].enemyRect.right - vMinionMaw[i].enemyRect.left) / 2;
		vMinionMaw[i].enemyY = vMinionMaw[i].enemyRect.top + (vMinionMaw[i].enemyRect.bottom - vMinionMaw[i].enemyRect.top) / 2;

		// �÷��̾�� ���� ������ �浹��
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionMaw[i].enemyFireRange))
		{
			// ���� ��ֹ��� �浹���� �ʾҴٸ�
			if (!enemyCollision)
			{
				// �÷��̾ �Ѿư���.
				enemyAreaCheck = true;
				EnemyShot();
			}
		}

		// ���࿡ �÷��̾ ���� ���� �����ȿ� ���Դٸ� �÷��̾ �Ѿư���.
		if (enemyAreaCheck)
		{
			// getdistance(���� ��ġ x, y, �÷��̾��� ��ġ x, y)
			distance = getDistance(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionMaw[i].enemyX) / distance * vMinionMaw[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionMaw[i].enemyY) / distance * vMinionMaw[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionMaw[i].enemySpeed;
			}

			// + - �ٲ㺸�� �̰� ���� ����� ��� �Ǵ���
			vMinionMaw[i].enemyX += vx;
			vMinionMaw[i].enemyY += vy;
			vMinionMaw[i].enemyRect = RectMakeCenter(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY, 30, 30);
		}
		// �����ȿ� �÷��̾ ���ٸ� �����ൿ(AI)
		else
		{
			EnemyAiTime();

			switch (vMinionMaw[i].enemyNumber)
			{
			case 0:
				switch (firstEnemyAiPattern)
				{
				case 1:		// IDLE
					break;
				case 2:		// LEFT
					if (vMinionMaw[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.left <= 10)
					{
						firstEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionMaw[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.right >= 950)
					{
						firstEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionMaw[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.top <= 10)
					{
						firstEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionMaw[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.bottom >= 530)
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
					if (vMinionMaw[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.left <= 10)
					{
						secondEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionMaw[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.right >= 950)
					{
						secondEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionMaw[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.top <= 10)
					{
						secondEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionMaw[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.bottom >= 530)
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
					if (vMinionMaw[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.left <= 10)
					{
						thirdEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionMaw[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.right >= 950)
					{
						thirdEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionMaw[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.top <= 10)
					{
						thirdEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionMaw[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.bottom >= 530)
					{
						thirdEnemyAiPattern = 4;
					}
					break;
				}
				break;
			}
		}

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		vMinionMaw[i].enemyFireRange = RectMakeCenter(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY, 200, 200);
	}

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// ���� ��� �ҷ� �浹
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void MinionMaw::EnemyShot()
{
	switch (vMinionMaw[i].enemyNumber)
	{
	case 0:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
			getAngle(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionMaw[i].enemyShotSpeed, vMinionMaw[i].enemyShotRange, firstEnemyBulletCount, vMinionMaw[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetFirstEnemyBulletCount();
		break;
	case 1:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
			getAngle(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionMaw[i].enemyShotSpeed, vMinionMaw[i].enemyShotRange, secondEnemyBulletCount, vMinionMaw[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetSecondEnemyBulletCount();
		break;
	case 2:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
			getAngle(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionMaw[i].enemyShotSpeed, vMinionMaw[i].enemyShotRange, thirdEnemyBulletCount, vMinionMaw[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetThirdEnemyBulletCount();
		break;
	}
}

void MinionMaw::DeleteEnemy(int num)
{
	vMinionMaw.erase(vMinionMaw.begin() + num);
}
