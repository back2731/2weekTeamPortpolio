#include "stdafx.h"
#include "Monstro.h"

Monstro::Monstro()
{
}

Monstro::~Monstro()
{
}

HRESULT Monstro::Init(POINT position)
{
	//구조체 정보 기입
	EnemyInfo Monstro;
	Monstro.enemyRect = RectMakeCenter(position.x, position.y, 150, 150);
	Monstro.enemyHp = 250;
	Monstro.enemyShotSpeed = 5.0f;
	Monstro.enemyShotRange = 500.0f;
	Monstro.enemyShotDelay = 150;
	Monstro.enemySpeed = 2.5f;
	vMonstro.push_back(Monstro);

	enemyAreaCheck = false;

	return S_OK;
}

void Monstro::Release()
{
}

void Monstro::Update()
{
	EnemyAi();
}

void Monstro::Render(HDC hdc)
{
	for (i = 0; i < vMonstro.size(); i++)
	{
		//Rectangle(hdc, vMonstro[i].enemyFireRange.left, vMonstro[i].enemyFireRange.top, vMonstro[i].enemyFireRange.right, vMonstro[i].enemyFireRange.bottom);
		Rectangle(hdc, vMonstro[i].enemyRect.left, vMonstro[i].enemyRect.top, vMonstro[i].enemyRect.right, vMonstro[i].enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void Monstro::EnemyAiTime()
{
	// AI 패턴 시간
	firstEnemyAiTime++;
	if (firstEnemyAiTime / 60 == 2)
	{
		firstEnemyAiPattern = RND->getFromIntTo(2, 5);
		firstEnemyAiTime = 0;
	}
}

void Monstro::EnemyAi()
{
	for (i = 0; i < vMonstro.size(); i++)
	{
		RECT temp;

		// 적 x축, y축 좌표
		vMonstro[i].enemyX = vMonstro[i].enemyRect.left + (vMonstro[i].enemyRect.right - vMonstro[i].enemyRect.left) / 2;
		vMonstro[i].enemyY = vMonstro[i].enemyRect.top + (vMonstro[i].enemyRect.bottom - vMonstro[i].enemyRect.top) / 2;

		// 플레이어와 판정 범위가 충돌시
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMonstro[i].enemyFireRange))
		{
			// 플레이어를 쫓아가라.
			enemyAreaCheck = false;
		}

		EnemyShot();

		// 만약에 플레이어가 적의 판정 범위안에 들어왔다면 플레이어를 쫓아간다.
		if (enemyAreaCheck)
		{
			// getdistance(적의 위치 x, y, 플레이어의 위치 x, y)
			distance = getDistance(vMonstro[i].enemyX, vMonstro[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((플레이어 위치 x / y) - (적 위치 x / y) / 거리 * 적 속도;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMonstro[i].enemyX) / distance * vMonstro[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMonstro[i].enemyY) / distance * vMonstro[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMonstro[i].enemySpeed;
			}

			// + - 바꿔보기 이게 접근 방식이 어떻게 되는지
			vMonstro[i].enemyX += vx;
			vMonstro[i].enemyY += vy;
			vMonstro[i].enemyRect = RectMakeCenter(vMonstro[i].enemyX, vMonstro[i].enemyY, 150, 150);
		}
		// 범위안에 플레이어가 없다면 자율행동(AI)
		else
		{
			EnemyAiTime();

			switch (firstEnemyAiPattern)
			{
			case 1:		// IDLE
				break;
			case 2:		// LEFT
				if (vMonstro[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
				{
					vMonstro[i].enemyRect.left -= vMonstro[i].enemySpeed;
					vMonstro[i].enemyRect.right -= vMonstro[i].enemySpeed;
				}
				if (vMonstro[i].enemyRect.left <= 10)
				{
					firstEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMonstro[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
				{
					vMonstro[i].enemyRect.left += vMonstro[i].enemySpeed;
					vMonstro[i].enemyRect.right += vMonstro[i].enemySpeed;
				}
				if (vMonstro[i].enemyRect.right >= 950)
				{
					firstEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMonstro[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
				{
					vMonstro[i].enemyRect.top -= vMonstro[i].enemySpeed;
					vMonstro[i].enemyRect.bottom -= vMonstro[i].enemySpeed;
				}
				if (vMonstro[i].enemyRect.top <= 10)
				{
					firstEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMonstro[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
				{
					vMonstro[i].enemyRect.top += vMonstro[i].enemySpeed;
					vMonstro[i].enemyRect.bottom += vMonstro[i].enemySpeed;
				}
				if (vMonstro[i].enemyRect.bottom >= 530)
				{
					firstEnemyAiPattern = 4;
				}
				break;
			}
		}

		// 판정 범위가 항상 적의 좌표를 쫓아다님
		vMonstro[i].enemyFireRange = RectMakeCenter(vMonstro[i].enemyX, vMonstro[i].enemyY, WINSIZEX, WINSIZEY);
	}

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// 적이 쏘는 불렛 충돌
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void Monstro::EnemyShot()
{
	// 캐릭터의 x축을 기준으로 눈꽃처럼 핏방울을 분출한다.
	if (vMonstro[i].enemyX > PLAYERMANAGER->GetPlayerHitRectX())
	{
		for (int j = 1; j <= 15; j++)
		{
			BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMonstro[i].enemyX - 100, vMonstro[i].enemyY,
				ANGLE_0 - j, vMonstro[i].enemyShotSpeed, vMonstro[i].enemyShotRange, firstEnemyBulletCount + j, vMonstro[i].enemyShotDelay);
		}
	}
	else if (vMonstro[i].enemyX < PLAYERMANAGER->GetPlayerHitRectX())
	{
		for (int j = 1; j <= 15; j++)
		{
			BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMonstro[i].enemyX + 100, vMonstro[i].enemyY,
				ANGLE_0 - j, vMonstro[i].enemyShotSpeed, vMonstro[i].enemyShotRange, firstEnemyBulletCount + j, vMonstro[i].enemyShotDelay);
		}
	}

	// 주위에 핏방울을 흩뿌린다.
	//for (int j = 1; j <= 15; j++)
	//{
	//	int rnd = RND->getInt(100);

	//	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMonstro[i].enemyX, vMonstro[i].enemyY,
	//		ANGLE_0 + rnd, vMonstro[i].enemyShotSpeed, vMonstro[i].enemyShotRange, firstEnemyBulletCount, vMonstro[i].enemyShotDelay);
	//}

	// 적의 불렛 카운트를 한 번에 플러스
	SetFirstEnemyBulletCount();
}

void Monstro::DeleteEnemy(int num)
{
	vMonstro.erase(vMonstro.begin() + num);
}
