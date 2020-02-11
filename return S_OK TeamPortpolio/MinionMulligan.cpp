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
	//구조체 정보 기입
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

void MinionMulligan::EnemyAi()
{
	for (i = 0; i < vMinionMulligan.size(); i++)
	{
		RECT temp;

		// 적 x축, y축 좌표
		vMinionMulligan[i].enemyX = vMinionMulligan[i].enemyRect.left + (vMinionMulligan[i].enemyRect.right - vMinionMulligan[i].enemyRect.left) / 2;
		vMinionMulligan[i].enemyY = vMinionMulligan[i].enemyRect.top + (vMinionMulligan[i].enemyRect.bottom - vMinionMulligan[i].enemyRect.top) / 2;

		// 플레이어와 판정 범위가 충돌시
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionMulligan[i].enemyFireRange))
		{
			// 플레이어를 쫓아가라.
			enemyAreaCheck = true;
			EnemyShot();
		}

		// 만약에 플레이어가 적의 판정 범위안에 들어왔다면 플레이어를 쫓아간다.
		if (enemyAreaCheck)
		{
			// getdistance(적의 위치 x, y, 플레이어의 위치 x, y)
			distance = getDistance(vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((플레이어 위치 x / y) - (적 위치 x / y) / 거리 * 적 속도;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionMulligan[i].enemyX) / distance * vMinionMulligan[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionMulligan[i].enemyY) / distance * vMinionMulligan[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionMulligan[i].enemySpeed;
			}

			// + - 바꿔보기 이게 접근 방식이 어떻게 되는지
			if (vMinionMulligan[i].enemyRect.left >= 10 && vMinionMulligan[i].enemyRect.right <= 950 &&
				vMinionMulligan[i].enemyRect.top >= 10 && vMinionMulligan[i].enemyRect.bottom <= 530)
			{
				collisionCheck = true;
				vMinionMulligan[i].enemyX -= vx;
				vMinionMulligan[i].enemyY -= vy;
			}
			vMinionMulligan[i].enemyRect = RectMakeCenter(vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY, 50, 50);
		}
		// 범위안에 플레이어가 없다면 자율행동(AI)
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
					if (vMinionMulligan[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionMulligan[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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

		// 판정 범위가 항상 적의 좌표를 쫓아다님
		vMinionMulligan[i].enemyFireRange = RectMakeCenter(vMinionMulligan[i].enemyX, vMinionMulligan[i].enemyY, 100, 100);
	}

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// 적이 쏘는 불렛 충돌
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

		// 적의 불렛 카운트를 한 번에 플러스
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

		// 적의 불렛 카운트를 한 번에 플러스
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

		// 적의 불렛 카운트를 한 번에 플러스
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