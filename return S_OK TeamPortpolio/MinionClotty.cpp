#include "stdafx.h"
#include "MinionClotty.h"

MinionClotty::MinionClotty()
{
}

MinionClotty::~MinionClotty()
{
}

HRESULT MinionClotty::Init(POINT position, int EnemyNumber)
{
	//����ü ���� ����
	EnemyInfo MinionClotty;
	MinionClotty.enemyNumber = EnemyNumber;
	MinionClotty.enemyRect = RectMakeCenter(position.x, position.y, 50, 50);
	MinionClotty.enemyHp = 15;
	MinionClotty.enemyShotSpeed = 5.0f;
	MinionClotty.enemyShotRange = 500.0f;
	MinionClotty.enemyShotDelay = 200;
	MinionClotty.enemySpeed = 3.0f;
	vMinionClotty.push_back(MinionClotty);

	enemyAreaCheck = false;
	enemyCollision = false;
	return S_OK;
}

void MinionClotty::Release()
{
}

void MinionClotty::Update()
{
	EnemyAi();
}

void MinionClotty::Render(HDC hdc)
{
	for (i = 0; i < vMinionClotty.size(); i++)
	{
		//Rectangle(hdc, vMinionClotty[i].enemyFireRange.left, vMinionClotty[i].enemyFireRange.top, vMinionClotty[i].enemyFireRange.right, vMinionClotty[i].enemyFireRange.bottom);
		Rectangle(hdc, vMinionClotty[i].enemyRect.left, vMinionClotty[i].enemyRect.top, vMinionClotty[i].enemyRect.right, vMinionClotty[i].enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionClotty::EnemyAiTime()
{
	switch (vMinionClotty[i].enemyNumber)
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

void MinionClotty::EnemyAi()
{
	for (i = 0; i < vMinionClotty.size(); i++)
	{
		// �� x��, y�� ��ǥ
		vMinionClotty[i].enemyX = vMinionClotty[i].enemyRect.left + (vMinionClotty[i].enemyRect.right - vMinionClotty[i].enemyRect.left) / 2;
		vMinionClotty[i].enemyY = vMinionClotty[i].enemyRect.top + (vMinionClotty[i].enemyRect.bottom - vMinionClotty[i].enemyRect.top) / 2;

		EnemyShot();
		EnemyAiTime();

		switch (vMinionClotty[i].enemyNumber)
		{
		case 0:
			switch (firstEnemyAiPattern)
			{
			case 1:		// IDLE
				break;
			case 2:		// LEFT
				if (vMinionClotty[i].enemyRect.left > 0)
				{
					vMinionClotty[i].enemyRect.left -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.left <= 10)
				{
					firstEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionClotty[i].enemyRect.right < WINSIZEX)
				{
					vMinionClotty[i].enemyRect.left += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.right >= 950)
				{
					firstEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionClotty[i].enemyRect.top > 0)
				{
					vMinionClotty[i].enemyRect.top -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.top <= 10)
				{
					firstEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionClotty[i].enemyRect.bottom < WINSIZEY)
				{
					vMinionClotty[i].enemyRect.top += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.bottom >= 530)
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
				if (vMinionClotty[i].enemyRect.left > 0)
				{
					vMinionClotty[i].enemyRect.left -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.left <= 10)
				{
					secondEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionClotty[i].enemyRect.right < WINSIZEX)
				{
					vMinionClotty[i].enemyRect.left += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.right >= 950)
				{
					secondEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionClotty[i].enemyRect.top > 0)
				{
					vMinionClotty[i].enemyRect.top -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.top <= 10)
				{
					secondEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionClotty[i].enemyRect.bottom < WINSIZEY)
				{
					vMinionClotty[i].enemyRect.top += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.bottom >= 530)
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
				if (vMinionClotty[i].enemyRect.left > 0)
				{
					vMinionClotty[i].enemyRect.left -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.left <= 10)
				{
					thirdEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionClotty[i].enemyRect.right < WINSIZEX)
				{
					vMinionClotty[i].enemyRect.left += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.right >= 950)
				{
					thirdEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionClotty[i].enemyRect.top > 0)
				{
					vMinionClotty[i].enemyRect.top -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.top <= 10)
				{
					thirdEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionClotty[i].enemyRect.bottom < WINSIZEY)
				{
					vMinionClotty[i].enemyRect.top += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.bottom >= 530)
				{
					thirdEnemyAiPattern = 4;
				}
				break;
			}
			break;
		}
	}

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);
}

void MinionClotty::EnemyShot()
{
	switch (vMinionClotty[i].enemyNumber)
	{
	case 0:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_0, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, firstEnemyBulletCount, vMinionClotty[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_90, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, firstEnemyBulletCount, vMinionClotty[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_180, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, firstEnemyBulletCount, vMinionClotty[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_270, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, firstEnemyBulletCount, vMinionClotty[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetFirstEnemyBulletCount();
		break;
	case 1:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_0, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, secondEnemyBulletCount, vMinionClotty[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_90, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, secondEnemyBulletCount, vMinionClotty[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_180, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, secondEnemyBulletCount, vMinionClotty[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_270, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, secondEnemyBulletCount, vMinionClotty[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetSecondEnemyBulletCount();
		break;
	case 2:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_0, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, thirdEnemyBulletCount, vMinionClotty[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_90, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, thirdEnemyBulletCount, vMinionClotty[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_180, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, thirdEnemyBulletCount, vMinionClotty[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClotty[i].enemyX, vMinionClotty[i].enemyY,
			ANGLE_270, vMinionClotty[i].enemyShotSpeed, vMinionClotty[i].enemyShotRange, thirdEnemyBulletCount, vMinionClotty[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetThirdEnemyBulletCount();
		break;
	}
}