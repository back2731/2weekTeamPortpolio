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
	//구조체 정보 기입
	EnemyInfo MinionTumor;
	MinionTumor.enemyNumber = EnemyNumber;
	MinionTumor.enemyRect = RectMakeCenter(position.x, position.y, 50, 50);
	MinionTumor.enemyHp = 20;
	MinionTumor.enemyShotSpeed = 5.0f;
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
		//Rectangle(hdc, vMinionTumor[i].enemyFireRange.left, vMinionTumor[i].enemyFireRange.top, vMinionTumor[i].enemyFireRange.right, vMinionTumor[i].enemyFireRange.bottom);
		Rectangle(hdc, vMinionTumor[i].enemyRect.left, vMinionTumor[i].enemyRect.top, vMinionTumor[i].enemyRect.right, vMinionTumor[i].enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionTumor::EnemyAiTime()
{
	switch (vMinionTumor[i].enemyNumber)
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

void MinionTumor::EnemyAi()
{
	for (i = 0; i < vMinionTumor.size(); i++)
	{
		// 적 x축, y축 좌표
		vMinionTumor[i].enemyX = vMinionTumor[i].enemyRect.left + (vMinionTumor[i].enemyRect.right - vMinionTumor[i].enemyRect.left) / 2;
		vMinionTumor[i].enemyY = vMinionTumor[i].enemyRect.top + (vMinionTumor[i].enemyRect.bottom - vMinionTumor[i].enemyRect.top) / 2;

		EnemyShot();
		EnemyAiTime();

		switch (vMinionTumor[i].enemyNumber)
		{
		case 0:
			switch (firstEnemyAiPattern)
			{
			case 1:		// IDLE
				break;
			case 2:	
				if (vMinionTumor[i].enemyRect.left > 0 || vMinionTumor[i].enemyRect.top > 0)
				{
					vMinionTumor[i].enemyRect.left -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom -= vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.left <= 30 || vMinionTumor[i].enemyRect.top <= 30)
				{
					firstEnemyAiPattern = 5;
				}
				break;
			case 3:	
				if (vMinionTumor[i].enemyRect.left > 0 || vMinionTumor[i].enemyRect.bottom > WINSIZEY)
				{
					vMinionTumor[i].enemyRect.left -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom += vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.left <= 30 || vMinionTumor[i].enemyRect.bottom >= 510)
				{
					firstEnemyAiPattern = 4;
				}
				break;
			case 4:	
				if (vMinionTumor[i].enemyRect.right < WINSIZEX || vMinionTumor[i].enemyRect.top > 0)
				{
					vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom -= vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.right >= 510 || vMinionTumor[i].enemyRect.top <= 30)
				{
					firstEnemyAiPattern = 3;
				}
				break;
			case 5:	
				if (vMinionTumor[i].enemyRect.right < WINSIZEX || vMinionTumor[i].enemyRect.bottom < WINSIZEY)
				{
					vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom += vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.right >= 510 || vMinionTumor[i].enemyRect.bottom >= 510)
				{
					firstEnemyAiPattern = 2;
				}
				break;
			}
			break;
		case 1:
			switch (secondEnemyAiPattern)
			{
			case 1:		// IDLE
				break;
			case 2:	
				if (vMinionTumor[i].enemyRect.left > 0 || vMinionTumor[i].enemyRect.top > 0)
				{
					vMinionTumor[i].enemyRect.left -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom -= vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.left <= 30 || vMinionTumor[i].enemyRect.top <= 30)
				{
					secondEnemyAiPattern = 5;
				}
				break;
			case 3:	
				if (vMinionTumor[i].enemyRect.left > 0 || vMinionTumor[i].enemyRect.bottom > WINSIZEY)
				{
					vMinionTumor[i].enemyRect.left -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom += vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.left <= 30 || vMinionTumor[i].enemyRect.bottom >= 510)
				{
					secondEnemyAiPattern = 4;
				}
				break;
			case 4:		
				if (vMinionTumor[i].enemyRect.right < WINSIZEX || vMinionTumor[i].enemyRect.top > 0)
				{
					vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom -= vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.right >= 510 || vMinionTumor[i].enemyRect.top <= 30)
				{
					secondEnemyAiPattern = 3;
				}
				break;
			case 5:		
				if (vMinionTumor[i].enemyRect.right < WINSIZEX || vMinionTumor[i].enemyRect.bottom < WINSIZEY)
				{
					vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom += vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.right >= 510 || vMinionTumor[i].enemyRect.bottom >= 510)
				{
					secondEnemyAiPattern = 2;
				}
				break;
			}
			break;
		case 2:
			switch (thirdEnemyAiPattern)
			{
			case 1:		// IDLE
				break;
			case 2:
				if (vMinionTumor[i].enemyRect.left > 0 || vMinionTumor[i].enemyRect.top > 0)
				{
					vMinionTumor[i].enemyRect.left -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom -= vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.left <= 30 || vMinionTumor[i].enemyRect.top <= 30)
				{
					thirdEnemyAiPattern = 5;
				}
				break;
			case 3:		
				if (vMinionTumor[i].enemyRect.left > 0 || vMinionTumor[i].enemyRect.bottom > WINSIZEY)
				{
					vMinionTumor[i].enemyRect.left -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom += vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.left <= 30 || vMinionTumor[i].enemyRect.bottom >= 510)
				{
					thirdEnemyAiPattern = 4;
				}
				break;
			case 4:		
				if (vMinionTumor[i].enemyRect.right < WINSIZEX || vMinionTumor[i].enemyRect.top > 0)
				{
					vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top -= vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom -= vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.right >= 510 || vMinionTumor[i].enemyRect.top <= 30)
				{
					thirdEnemyAiPattern = 3;
				}
				break;
			case 5:		
				if (vMinionTumor[i].enemyRect.right < WINSIZEX || vMinionTumor[i].enemyRect.bottom < WINSIZEY)
				{
					vMinionTumor[i].enemyRect.left += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.right += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.top += vMinionTumor[i].enemySpeed;
					vMinionTumor[i].enemyRect.bottom += vMinionTumor[i].enemySpeed;
				}
				if (vMinionTumor[i].enemyRect.right >= 510 || vMinionTumor[i].enemyRect.bottom >= 510)
				{
					thirdEnemyAiPattern = 2;
				}
				break;
			}
			break;
		}
	}

	// 적이 쏘는 불렛의 움직임
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

		// 적의 불렛 카운트를 한 번에 플러스
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

		// 적의 불렛 카운트를 한 번에 플러스
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

		// 적의 불렛 카운트를 한 번에 플러스
		SetThirdEnemyBulletCount();
		break;
	}
}