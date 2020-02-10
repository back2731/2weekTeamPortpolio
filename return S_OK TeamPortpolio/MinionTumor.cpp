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
		RECT temp;

		// 적 x축, y축 좌표
		vMinionTumor[i].enemyX = vMinionTumor[i].enemyRect.left + (vMinionTumor[i].enemyRect.right - vMinionTumor[i].enemyRect.left) / 2;
		vMinionTumor[i].enemyY = vMinionTumor[i].enemyRect.top + (vMinionTumor[i].enemyRect.bottom - vMinionTumor[i].enemyRect.top) / 2;

		// 플레이어와 판정 범위가 충돌시
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionTumor[i].enemyFireRange))
		{
			// 적과 장애물이 충돌하지 않았다면
			if (!enemyCollision)
			{
				// 플레이어를 쫓아가라.
				enemyAreaCheck = true;
			}
		}

		EnemyShot();

		// 만약에 플레이어가 적의 판정 범위안에 들어왔다면 플레이어를 쫓아간다.
		if (enemyAreaCheck)
		{
			// getdistance(적의 위치 x, y, 플레이어의 위치 x, y)
			distance = getDistance(vMinionTumor[i].enemyX, vMinionTumor[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((플레이어 위치 x / y) - (적 위치 x / y) / 거리 * 적 속도;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionTumor[i].enemyX) / distance * vMinionTumor[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionTumor[i].enemyY) / distance * vMinionTumor[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionTumor[i].enemySpeed;
			}

			// + - 바꿔보기 이게 접근 방식이 어떻게 되는지
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
		// 범위안에 플레이어가 없다면 자율행동(AI)
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
					if (vMinionTumor[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionTumor[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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

		// 판정 범위가 항상 적의 좌표를 쫓아다님
		vMinionTumor[i].enemyFireRange = RectMakeCenter(vMinionTumor[i].enemyX, vMinionTumor[i].enemyY, 700, 50);
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