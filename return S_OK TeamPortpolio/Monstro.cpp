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
	Monstro.enemyImage = IMAGEMANAGER->addImage("monstro", "images/monster/monstro.bmp", 192, 192, true, RGB(255, 0, 255));
	Monstro.enemyRect = RectMakeCenter(position.x, position.y, 130, 110);
	Monstro.enemyHp = 250;
	Monstro.enemyShotSpeed = 5.0f;
	Monstro.enemyShotRange = 500.0f;
	Monstro.enemyShotDelay = 150;
	Monstro.enemySpeed = 2.5f;
	vMonstro.push_back(Monstro);

	enemyAreaCheck = true;

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
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			//Rectangle(hdc, vMonstro[i].enemyFireRange.left, vMonstro[i].enemyFireRange.top, vMonstro[i].enemyFireRange.right, vMonstro[i].enemyFireRange.bottom);
			Rectangle(hdc, vMonstro[i].enemyRect.left, vMonstro[i].enemyRect.top, vMonstro[i].enemyRect.right, vMonstro[i].enemyRect.bottom);
			HBRUSH brush = CreateSolidBrush(RGB(51, 153, 0));
			FillRect(hdc, &vMonstro[i].enemyRect, brush);
			DeleteObject(brush);
		}

		IMAGEMANAGER->render("monstro", hdc, vMonstro[i].enemyRect.left - 33, vMonstro[i].enemyRect.top - 43);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void Monstro::EnemyAiTime()
{
	// AI 패턴 시간
	firstEnemyAiTime++;
	if (firstEnemyAiTime / 30 == 1)
	{
		firstEnemyAiPattern = RND->getFromIntTo(2, 2);
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

		// 만약에 플레이어가 적의 판정 범위안에 들어왔다면 플레이어를 쫓아간다.
		if (enemyAreaCheck)
		{
			// getdistance(적의 위치 x, y, 플레이어의 위치 x, y)
			distance = getDistance(vMonstro[i].enemyX, vMonstro[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((플레이어 위치 x / y) - (적 위치 x / y) / 거리 * 적 속도;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX() - 100.0f) - vMonstro[i].enemyX) / distance * vMonstro[i].enemySpeed * 3;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMonstro[i].enemyY) / distance * vMonstro[i].enemySpeed * 3;
			}
			else
			{
				vx = 0;
				vy = vMonstro[i].enemySpeed;
			}
		}

		EnemyAiTime();

		switch (firstEnemyAiPattern)
		{
		case 1:		// 눈꽃 발사
			shortJump = false;
			longJump = false;
			EnemySnowShot();
			break;
		case 2:		// 작은 점프
			shortJump = true;
			longJump = false;
			enemyAreaCheck = true;
			break;
		case 3:		// 큰 점프
			shortJump = false;
			longJump = true;
			enemyAreaCheck = true;
			EnemyShot();
			break;
		}

		if (shortJump)
		{
			jumpCount++;
			if (jumpCount < 20)
			{
				vMonstro[i].enemyRect.top -= 10.0f;
				vMonstro[i].enemyRect.bottom -= 10.0f;
			}
			else if (jumpCount >= 20 && jumpCount < 70)
			{
				vMonstro[i].enemyX += vx;
				vMonstro[i].enemyY += vy;
				vMonstro[i].enemyRect = RectMakeCenter(vMonstro[i].enemyX, vMonstro[i].enemyY, 130, 110);
			}
		}
		else
		{
			jumpCount = 0;
		}


	}

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// 적이 쏘는 불렛 충돌
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void Monstro::EnemySnowShot()
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

	// 적의 불렛 카운트를 한 번에 플러스
	SetFirstEnemyBulletCount();
}

void Monstro::EnemyShot()
{
	// 주위에 핏방울을 흩뿌린다.
	for (int j = 1; j <= 15; j++)
	{
		int rnd = RND->getInt(100);

		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMonstro[i].enemyX, vMonstro[i].enemyY,
			ANGLE_0 + rnd, vMonstro[i].enemyShotSpeed, vMonstro[i].enemyShotRange, firstEnemyBulletCount, vMonstro[i].enemyShotDelay);
	}

	// 적의 불렛 카운트를 한 번에 플러스
	SetFirstEnemyBulletCount();
}

void Monstro::DeleteEnemy(int num)
{
	vMonstro.erase(vMonstro.begin() + num);
}

void Monstro::SetEnemyRectX(int enemyNum, int move)
{
	vMonstro[enemyNum].enemyRect.left += move;
	vMonstro[enemyNum].enemyRect.right += move;
}

void Monstro::SetEnemyRectY(int enemyNum, int move)
{
	vMonstro[enemyNum].enemyRect.top += move;
	vMonstro[enemyNum].enemyRect.bottom += move;
}
