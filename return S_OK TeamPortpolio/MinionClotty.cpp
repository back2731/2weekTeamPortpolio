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
	//구조체 정보 기입
	EnemyInfo MinionClotty;
	MinionClotty.enemyNumber = EnemyNumber;
	MinionClotty.enemyRect = RectMakeCenter(position.x, position.y, 50, 50);
	MinionClotty.enemyHp = 15;
	MinionClotty.enemyShotSpeed = 5.0f;
	MinionClotty.enemyShotRange = 500.0f;
	MinionClotty.enemyShotDelay = 200;
	MinionClotty.enemySpeed = 2.5f;
	vMinionClotty.push_back(MinionClotty);

	enemyAreaCheck = false;

	return S_OK;
}

void MinionClotty::Release()
{
}

void MinionClotty::Update()
{
	EnemyAi();
	COLLISIONMANAGER->SameVectorMinionCollision(vMinionClotty);
}

void MinionClotty::Render(HDC hdc)
{
	for (i = 0; i < vMinionClotty.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			//Rectangle(hdc, vMinionClotty[i].enemyFireRange.left, vMinionClotty[i].enemyFireRange.top, vMinionClotty[i].enemyFireRange.right, vMinionClotty[i].enemyFireRange.bottom);
			Rectangle(hdc, vMinionClotty[i].enemyRect.left, vMinionClotty[i].enemyRect.top, vMinionClotty[i].enemyRect.right, vMinionClotty[i].enemyRect.bottom);			
			
			HBRUSH brush = CreateSolidBrush(RGB(102, 0, 153));
			FillRect(hdc, &vMinionClotty[i].enemyRect, brush);
			DeleteObject(brush);
		}
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionClotty::EnemyAiTime()
{
	switch (vMinionClotty[i].enemyNumber)
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

void MinionClotty::EnemyAi()
{
	for (i = 0; i < vMinionClotty.size(); i++)
	{
		// 적 x축, y축 좌표
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
				if (vMinionClotty[i].enemyRect.left > 105) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.left -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.left <= 120)
				{
					firstEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionClotty[i].enemyRect.right < 780) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.left += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.right >= 760)
				{
					firstEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionClotty[i].enemyRect.top > 105) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.top -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.top <= 120)
				{
					firstEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionClotty[i].enemyRect.bottom < 465) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.top += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.bottom >= 450)
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
				if (vMinionClotty[i].enemyRect.left > 105) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.left -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.left <= 120)
				{
					secondEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionClotty[i].enemyRect.right < 780) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.left += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.right >= 760)
				{
					secondEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionClotty[i].enemyRect.top > 105) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.top -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.top <= 120)
				{
					secondEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionClotty[i].enemyRect.bottom < 465) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.top += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.bottom >= 450)
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
				if (vMinionClotty[i].enemyRect.left > 105) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.left -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.left <= 120)
				{
					thirdEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionClotty[i].enemyRect.right < 780) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.left += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.right += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.right >= 760)
				{
					thirdEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionClotty[i].enemyRect.top > 105) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.top -= vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom -= vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.top <= 120)
				{
					thirdEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionClotty[i].enemyRect.bottom < 465) // 몬스터 이동 범위 제한
				{
					vMinionClotty[i].enemyRect.top += vMinionClotty[i].enemySpeed;
					vMinionClotty[i].enemyRect.bottom += vMinionClotty[i].enemySpeed;
				}
				if (vMinionClotty[i].enemyRect.bottom >= 450)
				{
					thirdEnemyAiPattern = 4;
				}
				break;
			}
			break;
		}
	}

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);

	// 적이 쏘는 불렛 충돌
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
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

		// 적의 불렛 카운트를 한 번에 플러스
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

		// 적의 불렛 카운트를 한 번에 플러스
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

		// 적의 불렛 카운트를 한 번에 플러스
		SetThirdEnemyBulletCount();
		break;
	}
}

void MinionClotty::DeleteEnemy(int num)
{
	vMinionClotty.erase(vMinionClotty.begin() + num);
}

void MinionClotty::SetEnemyRectX(int enemyNum, int move)
{
	vMinionClotty[enemyNum].enemyRect.left += move;
	vMinionClotty[enemyNum].enemyRect.right += move;
}

void MinionClotty::SetEnemyRectY(int enemyNum, int move)
{
	vMinionClotty[enemyNum].enemyRect.top += move;
	vMinionClotty[enemyNum].enemyRect.bottom += move;
}
