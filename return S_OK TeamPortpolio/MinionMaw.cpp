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
	//구조체 정보 기입
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

void MinionMaw::EnemyAi()
{
	for (i = 0; i < vMinionMaw.size(); i++)
	{
		RECT temp;

		// 적 x축, y축 좌표
		vMinionMaw[i].enemyX = vMinionMaw[i].enemyRect.left + (vMinionMaw[i].enemyRect.right - vMinionMaw[i].enemyRect.left) / 2;
		vMinionMaw[i].enemyY = vMinionMaw[i].enemyRect.top + (vMinionMaw[i].enemyRect.bottom - vMinionMaw[i].enemyRect.top) / 2;

		// 플레이어와 판정 범위가 충돌시
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionMaw[i].enemyFireRange))
		{
			// 적과 장애물이 충돌하지 않았다면
			if (!enemyCollision)
			{
				// 플레이어를 쫓아가라.
				enemyAreaCheck = true;
				EnemyShot();
			}
		}

		// 만약에 플레이어가 적의 판정 범위안에 들어왔다면 플레이어를 쫓아간다.
		if (enemyAreaCheck)
		{
			// getdistance(적의 위치 x, y, 플레이어의 위치 x, y)
			distance = getDistance(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((플레이어 위치 x / y) - (적 위치 x / y) / 거리 * 적 속도;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionMaw[i].enemyX) / distance * vMinionMaw[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionMaw[i].enemyY) / distance * vMinionMaw[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionMaw[i].enemySpeed;
			}

			// + - 바꿔보기 이게 접근 방식이 어떻게 되는지
			vMinionMaw[i].enemyX += vx;
			vMinionMaw[i].enemyY += vy;
			vMinionMaw[i].enemyRect = RectMakeCenter(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY, 30, 30);
		}
		// 범위안에 플레이어가 없다면 자율행동(AI)
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
					if (vMinionMaw[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMaw[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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

		// 판정 범위가 항상 적의 좌표를 쫓아다님
		vMinionMaw[i].enemyFireRange = RectMakeCenter(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY, 200, 200);
	}

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// 적이 쏘는 불렛 충돌
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

		// 적의 불렛 카운트를 한 번에 플러스
		SetFirstEnemyBulletCount();
		break;
	case 1:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
			getAngle(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionMaw[i].enemyShotSpeed, vMinionMaw[i].enemyShotRange, secondEnemyBulletCount, vMinionMaw[i].enemyShotDelay);

		// 적의 불렛 카운트를 한 번에 플러스
		SetSecondEnemyBulletCount();
		break;
	case 2:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
			getAngle(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionMaw[i].enemyShotSpeed, vMinionMaw[i].enemyShotRange, thirdEnemyBulletCount, vMinionMaw[i].enemyShotDelay);

		// 적의 불렛 카운트를 한 번에 플러스
		SetThirdEnemyBulletCount();
		break;
	}
}

void MinionMaw::DeleteEnemy(int num)
{
	vMinionMaw.erase(vMinionMaw.begin() + num);
}
