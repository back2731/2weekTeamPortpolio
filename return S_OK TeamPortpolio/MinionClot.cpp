#include "stdafx.h"
#include "MinionClot.h"

MinionClot::MinionClot()
{
}

MinionClot::~MinionClot()
{
}

HRESULT MinionClot::Init(POINT position, int EnemyNumber)
{
	//구조체 정보 기입
	EnemyInfo MinionClot;
	MinionClot.enemyNumber = EnemyNumber;
	MinionClot.enemyRect = RectMakeCenter(position.x, position.y, 50, 50);
	MinionClot.enemyHp = 15;
	MinionClot.enemyShotSpeed = 5.0f;
	MinionClot.enemyShotRange = 500.0f;
	MinionClot.enemyShotDelay = 200;
	MinionClot.enemySpeed = 3.0f;
	vMinionClot.push_back(MinionClot);

	enemyAreaCheck = false;

	return S_OK;
}

void MinionClot::Release()
{
}

void MinionClot::Update()
{
	EnemyAi();
	COLLISIONMANAGER->SameVectorMinionCollision(vMinionClot);
}

void MinionClot::Render(HDC hdc)
{
	for (i = 0; i < vMinionClot.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{		
			//Rectangle(hdc, vMinionClot[i].enemyFireRange.left, vMinionClot[i].enemyFireRange.top, vMinionClot[i].enemyFireRange.right, vMinionClot[i].enemyFireRange.bottom);
			Rectangle(hdc, vMinionClot[i].enemyRect.left, vMinionClot[i].enemyRect.top, vMinionClot[i].enemyRect.right, vMinionClot[i].enemyRect.bottom);
			
			HBRUSH brush = CreateSolidBrush(RGB(204, 0, 102));
			FillRect(hdc, &vMinionClot[i].enemyRect, brush);
			DeleteObject(brush);
		}
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionClot::EnemyAiTime()
{
	switch (vMinionClot[i].enemyNumber)
	{
	case 0:
		// AI 패턴 시간
		firstEnemyAiTime++;
		if (firstEnemyAiTime / 60 == 2)
		{
			firstEnemyAiPattern = RND->getFromIntTo(2, 5);
			firstEnemyAiTime = 0;
		}
		break;
	case 1:
		// AI 패턴 시간
		secondEnemyAiTime++;
		if (secondEnemyAiTime / 60 == 2)
		{
			secondEnemyAiPattern = RND->getFromIntTo(2, 5);
			secondEnemyAiTime = 0;
		}
		break;
	case 2:
		// AI 패턴 시간
		thirdEnemyAiTime++;
		if (thirdEnemyAiTime / 60 == 2)
		{
			thirdEnemyAiPattern = RND->getFromIntTo(2, 5);
			thirdEnemyAiTime = 0;
		}
		break;
	}
}

void MinionClot::EnemyAi()
{
	for (i = 0; i < vMinionClot.size(); i++)
	{
		// 적 x축, y축 좌표
		vMinionClot[i].enemyX = vMinionClot[i].enemyRect.left + (vMinionClot[i].enemyRect.right - vMinionClot[i].enemyRect.left) / 2;
		vMinionClot[i].enemyY = vMinionClot[i].enemyRect.top + (vMinionClot[i].enemyRect.bottom - vMinionClot[i].enemyRect.top) / 2;

		EnemyShot();
		EnemyAiTime();

		switch (vMinionClot[i].enemyNumber)
		{
		case 0:
			switch (firstEnemyAiPattern)
			{
			case 1:		// IDLE
				break;
			case 2:		// LEFT
				if (vMinionClot[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.left -= vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.right -= vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.left <= 10)
				{
					firstEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionClot[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.left += vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.right += vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.right >= 950)
				{
					firstEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionClot[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.top -= vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.bottom -= vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.top <= 10)
				{
					firstEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionClot[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.top += vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.bottom += vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.bottom >= 530)
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
				if (vMinionClot[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.left -= vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.right -= vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.left <= 10)
				{
					secondEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionClot[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.left += vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.right += vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.right >= 950)
				{
					secondEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionClot[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.top -= vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.bottom -= vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.top <= 10)
				{
					secondEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionClot[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.top += vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.bottom += vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.bottom >= 530)
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
				if (vMinionClot[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.left -= vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.right -= vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.left <= 10)
				{
					thirdEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionClot[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.left += vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.right += vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.right >= 950)
				{
					thirdEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionClot[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.top -= vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.bottom -= vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.top <= 10)
				{
					thirdEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionClot[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
				{
					vMinionClot[i].enemyRect.top += vMinionClot[i].enemySpeed;
					vMinionClot[i].enemyRect.bottom += vMinionClot[i].enemySpeed;
				}
				if (vMinionClot[i].enemyRect.bottom >= 530)
				{
					thirdEnemyAiPattern = 4;
				}
				break;
			}
			break;
		}
	}

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// 적이 쏘는 불렛 충돌
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void MinionClot::EnemyShot()
{
	switch (vMinionClot[i].enemyNumber)
	{
	case 0:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_45, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, firstEnemyBulletCount, vMinionClot[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_135, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, firstEnemyBulletCount, vMinionClot[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_225, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, firstEnemyBulletCount, vMinionClot[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_315, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, firstEnemyBulletCount, vMinionClot[i].enemyShotDelay);

		// 적의 불렛 카운트를 한 번에 플러스
		SetFirstEnemyBulletCount();
		break;
	case 1:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_45, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, secondEnemyBulletCount, vMinionClot[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_135, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, secondEnemyBulletCount, vMinionClot[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_225, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, secondEnemyBulletCount, vMinionClot[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_315, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, secondEnemyBulletCount, vMinionClot[i].enemyShotDelay);

		// 적의 불렛 카운트를 한 번에 플러스
		SetSecondEnemyBulletCount();
		break;
	case 2:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_45, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, thirdEnemyBulletCount, vMinionClot[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_135, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, thirdEnemyBulletCount, vMinionClot[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_225, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, thirdEnemyBulletCount, vMinionClot[i].enemyShotDelay);
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionClot[i].enemyX, vMinionClot[i].enemyY,
			ANGLE_315, vMinionClot[i].enemyShotSpeed, vMinionClot[i].enemyShotRange, thirdEnemyBulletCount, vMinionClot[i].enemyShotDelay);

		// 적의 불렛 카운트를 한 번에 플러스
		SetThirdEnemyBulletCount();
		break;
	}
}

void MinionClot::DeleteEnemy(int num)
{
	vMinionClot.erase(vMinionClot.begin() + num);
}

void MinionClot::SetEnemyRectX(int enemyNum, int move)
{
	vMinionClot[enemyNum].enemyRect.left += move;
	vMinionClot[enemyNum].enemyRect.right += move;
}

void MinionClot::SetEnemyRectY(int enemyNum, int move)
{
	vMinionClot[enemyNum].enemyRect.top += move;
	vMinionClot[enemyNum].enemyRect.bottom += move;
}
