#include "stdafx.h"
#include "MinionTumor.h"

MinionTumor::MinionTumor()
{
}

MinionTumor::~MinionTumor()
{
}

HRESULT MinionTumor::Init(POINT position, int EnemyNumber)
{
	//����ü ���� ����
	EnemyInfo MinionTumor;
	MinionTumor.enemyNumber = EnemyNumber;
	MinionTumor.enemyRect = RectMakeCenter(position.x, position.y, 50, 50);
	MinionTumor.enemyHp = 20;
	MinionTumor.enemyShotSpeed = 4.0f;
	MinionTumor.enemyShotRange = 500.0f;
	MinionTumor.enemyShotDelay = 200;
	MinionTumor.enemySpeed = 1.5f;
	vMinionTumor.push_back(MinionTumor);

	enemyAreaCheck = false;
	enemyCollision = false;

	return S_OK;
}

void MinionTumor::Release()
{
}

void MinionTumor::Update()
{
	EnemyAi();
}

void MinionTumor::Render(HDC hdc)
{
	for (i = 0; i < vMinionTumor.size(); i++)
	{
		Rectangle(hdc, vMinionTumor[i].enemyFireRange.left, vMinionTumor[i].enemyFireRange.top, vMinionTumor[i].enemyFireRange.right, vMinionTumor[i].enemyFireRange.bottom);
		Rectangle(hdc, vMinionTumor[i].enemyRect.left, vMinionTumor[i].enemyRect.top, vMinionTumor[i].enemyRect.right, vMinionTumor[i].enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionTumor::EnemyAiTime()
{
	switch (vMinionTumor[i].enemyNumber)
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

void MinionTumor::EnemyAi()
{
	for (i = 0; i < vMinionTumor.size(); i++)
	{
		RECT temp;

		// �� x��, y�� ��ǥ
		vMinionTumor[i].enemyX = vMinionTumor[i].enemyRect.left + (vMinionTumor[i].enemyRect.right - vMinionTumor[i].enemyRect.left) / 2;
		vMinionTumor[i].enemyY = vMinionTumor[i].enemyRect.top + (vMinionTumor[i].enemyRect.bottom - vMinionTumor[i].enemyRect.top) / 2;

		// �÷��̾�� ���� ������ �浹��
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionTumor[i].enemyFireRange))
		{
			// ���� ��ֹ��� �浹���� �ʾҴٸ�
			if (!enemyCollision)
			{
				// �÷��̾ �Ѿư���.
				enemyAreaCheck = true;
			}
		}

		EnemyShot();

		// ���࿡ �÷��̾ ���� ���� �����ȿ� ���Դٸ� �÷��̾ �Ѿư���.
		if (enemyAreaCheck)
		{
			// getdistance(���� ��ġ x, y, �÷��̾��� ��ġ x, y)
			distance = getDistance(vMinionTumor[i].enemyX, vMinionTumor[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionTumor[i].enemyX) / distance * vMinionTumor[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionTumor[i].enemyY) / distance * vMinionTumor[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionTumor[i].enemySpeed;
			}

			// + - �ٲ㺸�� �̰� ���� ����� ��� �Ǵ���
			vMinionTumor[i].enemyX += vx;
			vMinionTumor[i].enemyY += vy;
			vMinionTumor[i].enemyRect = RectMakeCenter(vMinionTumor[i].enemyX, vMinionTumor[i].enemyY, 50, 50);

			if (vMinionTumor[i].enemyX < PLAYERMANAGER->GetPlayerHitRectX())
			{
				if ((vMinionTumor[i].enemyRect.top + 10) < PLAYERMANAGER->GetPlayerHitRectY() &&
					(vMinionTumor[i].enemyRect.bottom - 10) > PLAYERMANAGER->GetPlayerHitRectY())
				{
					vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed * 2;
					vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed * 2;
				}
			}
		}
		// �����ȿ� �÷��̾ ���ٸ� �����ൿ(AI)
		else if (!enemyAreaCheck)
		{
			EnemyAiTime();

			switch (vMinionTumor[i].enemyNumber)
			{
			case 0:
				switch (firstEnemyAiPattern)
				{
				case 1:		// IDLE
					break;
				case 2:		// LEFT
					if (vMinionTumor[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.left -= vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.right -= vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.left <= 10)
					{
						firstEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionTumor[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.right >= 950)
					{
						firstEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionTumor[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.top -= vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.bottom -= vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.top <= 10)
					{
						firstEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionTumor[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.top += vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.bottom += vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.bottom >= 530)
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
					if (vMinionTumor[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.left -= vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.right -= vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.left <= 10)
					{
						secondEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionTumor[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.right >= 950)
					{
						secondEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionTumor[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.top -= vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.bottom -= vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.top <= 10)
					{
						secondEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionTumor[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.top += vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.bottom += vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.bottom >= 530)
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
					if (vMinionTumor[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.left -= vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.right -= vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.left <= 10)
					{
						thirdEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionTumor[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.right >= 950)
					{
						thirdEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionTumor[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.top -= vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.bottom -= vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.top <= 10)
					{
						thirdEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionTumor[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionTumor[i].enemyRect.top += vMinionTumor[i].enemySpeed;
						vMinionTumor[i].enemyRect.bottom += vMinionTumor[i].enemySpeed;
					}
					if (vMinionTumor[i].enemyRect.bottom >= 530)
					{
						thirdEnemyAiPattern = 4;
					}
					break;
				}
				break;
			}
		}

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		vMinionTumor[i].enemyFireRange = RectMakeCenter(vMinionTumor[i].enemyX, vMinionTumor[i].enemyY, 700, 50);
	}

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);
}

void MinionTumor::EnemyShot()
{
	switch (vMinionTumor[i].enemyNumber)
	{
	case 0:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_0, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, firstEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_45, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, firstEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_135, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, firstEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_180, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, firstEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_225, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, firstEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_315, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, firstEnemyBulletCount, vMinionTumor[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetFirstEnemyBulletCount();
		break;
	case 1:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_0, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, secondEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_45, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, secondEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_135, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, secondEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_180, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, secondEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_225, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, secondEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_315, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, secondEnemyBulletCount, vMinionTumor[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetSecondEnemyBulletCount();
		break;
	case 2:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_0, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, thirdEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_45, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, thirdEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_135, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, thirdEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_180, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, thirdEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_225, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, thirdEnemyBulletCount, vMinionTumor[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionTumor[i].enemyX, vMinionTumor[i].enemyY,
			ANGLE_315, vMinionTumor[i].enemyShotSpeed, vMinionTumor[i].enemyShotRange, thirdEnemyBulletCount, vMinionTumor[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetThirdEnemyBulletCount();
		break;
	}
}