#include "stdafx.h"
#include "TestMinion.h"

TestMinion::TestMinion()
{
}

TestMinion::~TestMinion()
{
}

HRESULT TestMinion::Init(POINT position)
{
	// 테스트용 에네미 렉트
	enemyRect = RectMakeCenter(position.x, position.y, 50, 50);
	// 테스트용 장애물 렉트
	obstacle = RectMakeCenter(WINSIZEX / 2 + 150, WINSIZEY / 2, 50, 300);

	firstEnemyAiTime = 0;		// 행동시간
	firstEnemyAiPattern = 1;		// 행동패턴 (기본 IDLE)
	speed = 3.0f;			// 이동속도

	obstacleX = obstacle.left + (obstacle.right - obstacle.left) / 2;	// 장애물 x축 좌표
	obstacleY = obstacle.top + (obstacle.bottom - obstacle.top) / 2;	// 장애물 y축 좌표

	enemyAreaCheck = false;
	enemyCollision = false;

	return S_OK;
}

void TestMinion::Release()
{
}

void TestMinion::Update()
{
	// 적 x축, y축 좌표
	enemyX = enemyRect.left + (enemyRect.right - enemyRect.left) / 2;
	enemyY = enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2;

	// 플레이어와 판정 범위가 충돌시
	if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &fireRange))
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
		distance = getDistance(enemyX, enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

		if (distance)
		{
			// vector = ((플레이어 위치 x / y) - (적 위치 x / y) / 거리 * 적 속도;
			vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - enemyX) / distance * speed;
			vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - enemyY) / distance * speed;
		}
		else
		{
			vx = 0;
			vy = speed;
		}

		// + - 바꿔보기 이게 접근 방식이 어떻게 되는지
		enemyX += vx;
		enemyY += vy;
		enemyRect = RectMakeCenter(enemyX, enemyY, 50, 50);
	}
	// 범위안에 플레이어가 없다면 자율행동(AI)
	else
	{
		EnemyAiTime();

		switch (firstEnemyAiPattern)
		{
		case 1:		// IDLE
			motion = ENEMY_IDLE;
			break;
		case 2:		// LEFT
			motion = ENEMY_LEFT;
			if (enemyRect.left > 0)
			{
				enemyRect.left -= speed;
				enemyRect.right -= speed;
			}
			if (enemyRect.left <= 10)
			{
				firstEnemyAiPattern = 3;
			}
			break;
		case 3:		// RIGHT
			motion = ENEMY_RIGHT;
			if (enemyRect.right < WINSIZEX)
			{
				enemyRect.left += speed;
				enemyRect.right += speed;
			}
			if (enemyRect.right >= 1000)
			{
				firstEnemyAiPattern = 2;
			}
			break;
		case 4:		// UP
			motion = ENEMY_UP;
			if (enemyRect.top > 0)
			{
				enemyRect.top -= speed;
				enemyRect.bottom -= speed;
			}
			if (enemyRect.top <= 10)
			{
				firstEnemyAiPattern = 5;
			}
			break;
		case 5:		// DOWN
			motion = ENEMY_DOWN;
			if (enemyRect.bottom < WINSIZEY)
			{
				enemyRect.top += speed;
				enemyRect.bottom += speed;
			}
			if (enemyRect.bottom >= 750)
			{
				firstEnemyAiPattern = 4;
			}
			break;
		}
	}

	// 판정 범위가 항상 적의 좌표를 쫓아다님
	fireRange = RectMakeCenter(enemyX, enemyY, 300, 300);

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);

	// 적과 장애물이 충돌하면 true
	if (IntersectRect(&temp, &obstacle, &enemyRect))
	{
		enemyCollision = true;

		int tempW = temp.right - temp.left;
		int tempH = temp.bottom - temp.top;

		if (tempH > tempW)
		{
			if (temp.left == enemyRect.left)
			{
				enemyRect.left += tempW + speed;
				enemyRect.right += tempW + speed;
			}
			if (temp.right == enemyRect.right)
			{
				enemyRect.left -= tempW + speed;
				enemyRect.right -= tempW + speed;
			}
		}
		else
		{
			if (temp.top == enemyRect.top)
			{
				enemyRect.top += tempH + speed;
				enemyRect.bottom += tempH + speed;
			}
			if (temp.bottom == enemyRect.bottom)
			{
				enemyRect.top -= tempH + speed;
				enemyRect.bottom -= tempH + speed;
			}
		}

		// 장애물과 충돌시 비껴서 움직인다.
		if (PLAYERMANAGER->GetPlayerHitRectX() < obstacleX)
		{
			enemyRect.left -= speed;
			enemyRect.right -= speed;
		}
		else if (PLAYERMANAGER->GetPlayerHitRectX() >= obstacleX)
		{
			enemyRect.left += speed;
			enemyRect.right += speed;
		}
		if (PLAYERMANAGER->GetPlayerHitRectY() < obstacleY)
		{
			enemyRect.top -= speed;
			enemyRect.bottom -= speed;
		}
		else if (PLAYERMANAGER->GetPlayerHitRectY() >= obstacleY)
		{
			enemyRect.top += speed;
			enemyRect.bottom += speed;
		}
	}
	// 적과 장애물이 충돌하지 않으면 false
	else
	{
		enemyCollision = false;
	}

	// 플레이어와 적이 충돌하면 밀려난다.
	if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &enemyRect))
	{
		int tempW = temp.right - temp.left;
		int tempH = temp.bottom - temp.top;

		if (tempH > tempW)
		{
			if (temp.left == enemyRect.left)
			{
				enemyRect.left += tempW;
				enemyRect.right += tempW;
			}
			if (temp.right == enemyRect.right)
			{
				enemyRect.left -= tempW;
				enemyRect.right -= tempW;
			}
		}
		else
		{
			if (temp.top == enemyRect.top)
			{
				enemyRect.top += tempH;
				enemyRect.bottom += tempH;
			}
			if (temp.bottom == enemyRect.bottom)
			{
				enemyRect.top -= tempH;
				enemyRect.bottom -= tempH;
			}
		}
	}
}

void TestMinion::Render(HDC hdc)
{
	//Rectangle(hdc, fireRange.left, fireRange.top, fireRange.right, fireRange.bottom);
	Rectangle(hdc, enemyRect.left, enemyRect.top, enemyRect.right, enemyRect.bottom);
	Rectangle(hdc, obstacle.left, obstacle.top, obstacle.right, obstacle.bottom);

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void TestMinion::EnemyShot()
{
	// 적의 총알 발사
	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, enemyX, enemyY,
		getAngle(enemyX, enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
		5.0f, 500, firstEnemyBulletCount, 50);

	// 적의 불렛 카운트를 한 번에 플러스
	SetFirstEnemyBulletCount();
}

void TestMinion::EnemyAiTime()
{
	// AI 패턴 시간
	firstEnemyAiTime++;
	if (firstEnemyAiTime / 60 == 2)
	{
		firstEnemyAiPattern = RND->getFromIntTo(2, 5);
		firstEnemyAiTime = 0;
	}
}