#include "stdafx.h"
#include "MinionMaw.h"

MinionMaw::MinionMaw()
{
}

MinionMaw::~MinionMaw()
{
}

HRESULT MinionMaw::Init(POINT position)
{
	//구조체 정보 기입
	EnemyInfo minionMaw;
	minionMaw.enemyRect = RectMakeCenter(position.x, position.y, 50, 50);
	minionMaw.enemyHp = 25;
	minionMaw.enemyShotSpeed = 5.0f;
	minionMaw.enemyShotRange = 500.0f;
	minionMaw.enemyShotDelay = 50;
	minionMaw.enemySpeed = 2.0f;
	vMinionMaw.push_back(minionMaw);

	enemyAreaCheck = false;
	enemyCollision = false;

	return E_NOTIMPL;
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
	viMinionMaw = vMinionMaw.begin();

	for (viMinionMaw; viMinionMaw != vMinionMaw.end(); ++viMinionMaw)
	{
		//Rectangle(hdc, viMinionMaw->enemyFireRange.left, viMinionMaw->enemyFireRange.top, viMinionMaw->enemyFireRange.right, viMinionMaw->enemyFireRange.bottom);
		Rectangle(hdc, viMinionMaw->enemyRect.left, viMinionMaw->enemyRect.top, viMinionMaw->enemyRect.right, viMinionMaw->enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionMaw::EnemyAiTime()
{
	// AI 패턴 시간
	enemyAiTime++;
	if (enemyAiTime / 60 == 2)
	{
		enemyAiPattern = RND->getFromIntTo(2, 5);
		enemyAiTime = 0;
	}
}

void MinionMaw::EnemyAi()
{
	viMinionMaw = vMinionMaw.begin();

	for (viMinionMaw; viMinionMaw != vMinionMaw.end(); ++viMinionMaw)
	{
		RECT temp;

		// 적 x축, y축 좌표
		viMinionMaw->enemyX = viMinionMaw->enemyRect.left + (viMinionMaw->enemyRect.right - viMinionMaw->enemyRect.left) / 2;
		viMinionMaw->enemyY = viMinionMaw->enemyRect.top + (viMinionMaw->enemyRect.bottom - viMinionMaw->enemyRect.top) / 2;

		// 플레이어와 판정 범위가 충돌시
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &viMinionMaw->enemyFireRange))
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
			distance = getDistance(viMinionMaw->enemyX, viMinionMaw->enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((플레이어 위치 x / y) - (적 위치 x / y) / 거리 * 적 속도;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - viMinionMaw->enemyX) / distance * viMinionMaw->enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - viMinionMaw->enemyY) / distance * viMinionMaw->enemySpeed;
			}
			else
			{
				vx = 0;
				vy = viMinionMaw->enemySpeed;
			}

			// + - 바꿔보기 이게 접근 방식이 어떻게 되는지
			viMinionMaw->enemyX += vx;
			viMinionMaw->enemyY += vy;
			viMinionMaw->enemyRect = RectMakeCenter(viMinionMaw->enemyX, viMinionMaw->enemyY, 50, 50);
		}
		// 범위안에 플레이어가 없다면 자율행동(AI)
		else
		{
			EnemyAiTime();

			switch (enemyAiPattern)
			{
			case 1:		// IDLE
				break;
			case 2:		// LEFT
				if (viMinionMaw->enemyRect.left > 0)
				{
					viMinionMaw->enemyRect.left -= viMinionMaw->enemySpeed;
					viMinionMaw->enemyRect.right -= viMinionMaw->enemySpeed;
				}
				if (viMinionMaw->enemyRect.left <= 10)
				{
					enemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (viMinionMaw->enemyRect.right < WINSIZEX)
				{
					viMinionMaw->enemyRect.left += viMinionMaw->enemySpeed;
					viMinionMaw->enemyRect.right += viMinionMaw->enemySpeed;
				}
				if (viMinionMaw->enemyRect.right >= 1000)
				{
					enemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (viMinionMaw->enemyRect.top > 0)
				{
					viMinionMaw->enemyRect.top -= viMinionMaw->enemySpeed;
					viMinionMaw->enemyRect.bottom -= viMinionMaw->enemySpeed;
				}
				if (viMinionMaw->enemyRect.top <= 10)
				{
					enemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (viMinionMaw->enemyRect.bottom < WINSIZEY)
				{
					viMinionMaw->enemyRect.top += viMinionMaw->enemySpeed;
					viMinionMaw->enemyRect.bottom += viMinionMaw->enemySpeed;
				}
				if (viMinionMaw->enemyRect.bottom >= 750)
				{
					enemyAiPattern = 4;
				}
				break;
			}
		}

		// 판정 범위가 항상 적의 좌표를 쫓아다님
		viMinionMaw->enemyFireRange = RectMakeCenter(viMinionMaw->enemyX, viMinionMaw->enemyY, 300, 300);
	}

	// 적의 불렛 카운트를 한 번에 플러스
	SetEnemyBulletCount();

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);
}

void MinionMaw::EnemyShot()
{
	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, viMinionMaw->enemyX, viMinionMaw->enemyY,
		ANGLE_0, viMinionMaw->enemyShotSpeed, viMinionMaw->enemyShotRange, enemyBulletCount, viMinionMaw->enemyShotDelay);
	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, viMinionMaw->enemyX, viMinionMaw->enemyY,
		ANGLE_90, viMinionMaw->enemyShotSpeed, viMinionMaw->enemyShotRange, enemyBulletCount, viMinionMaw->enemyShotDelay);
	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, viMinionMaw->enemyX, viMinionMaw->enemyY,
		ANGLE_180, viMinionMaw->enemyShotSpeed, viMinionMaw->enemyShotRange, enemyBulletCount, viMinionMaw->enemyShotDelay);
	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, viMinionMaw->enemyX, viMinionMaw->enemyY,
		ANGLE_270, viMinionMaw->enemyShotSpeed, viMinionMaw->enemyShotRange, enemyBulletCount, viMinionMaw->enemyShotDelay);
}