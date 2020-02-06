#include "stdafx.h"
#include "TestMinion.h"

TestMinion::TestMinion()
{
}

TestMinion::~TestMinion()
{
}

HRESULT TestMinion::Init()
{
	//테스트용 에네미 렉트
	enemyRect = RectMakeCenter(WINSIZEX / 2 + 300, WINSIZEY / 2, 50, 50);
	enemyBulletInterval = 0;
	obstacle = RectMakeCenter(WINSIZEX / 2 + 150, WINSIZEY / 2, 50, 300);

	time = 0;		//행동시간
	rnd = 1;		//행동패턴 (기본 IDLE)
	speed = 3.0f;	//이동속도

	obstacleX = obstacle.left + (obstacle.right - obstacle.left) / 2;
	obstacleY = obstacle.top + (obstacle.bottom - obstacle.top) / 2;

	areaCheck = false;
	collision = false;

	return S_OK;
}

void TestMinion::Release()
{
}

void TestMinion::Update()
{
	enemyX = enemyRect.left + (enemyRect.right - enemyRect.left) / 2;
	enemyY = enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2;

	if (areaCheck)
	{
		//getdistance(적의 위치 x, y, 플레이어의 위치 x, y)
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
	else
	{
		EnemyAiTime();

		switch (rnd)
		{
		case 1:		//IDLE
			motion = ENEMY_IDLE;
			break;
		case 2:		//LEFT
			motion = ENEMY_LEFT;
			if (enemyRect.left > 0)
			{
				enemyRect.left -= speed;
				enemyRect.right -= speed;
			}
			if (enemyRect.left <= 10)
			{
				rnd = 3;
			}
			break;
		case 3:		//RIGHT
			motion = ENEMY_RIGHT;
			if (enemyRect.right < WINSIZEX)
			{
				enemyRect.left += speed;
				enemyRect.right += speed;
			}
			if (enemyRect.right >= 1000)
			{
				rnd = 2;
			}
			break;
		case 4:		//UP
			motion = ENEMY_UP;
			if (enemyRect.top > 0)
			{
				enemyRect.top -= speed;
				enemyRect.bottom -= speed;
			}
			if (enemyRect.top <= 10)
			{
				rnd = 5;
			}
			break;
		case 5:		//DOWN
			motion = ENEMY_DOWN;
			if (enemyRect.bottom < WINSIZEY)
			{
				enemyRect.top += speed;
				enemyRect.bottom += speed;
			}
			if (enemyRect.bottom >= 750)
			{
				rnd = 4;
			}
			break;
		}
	}

	fireRange = RectMakeCenter(enemyX, enemyY, 500, 500);

	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);

	if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &fireRange))
	{
		if (!collision)
		{
			areaCheck = true;
			EnemyShot();
		}
	}
	else
	{
		areaCheck = false;
	}

	if (IntersectRect(&temp, &obstacle, &enemyRect))
	{
		collision = true;

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
	else
	{
		collision = false;
	}

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
	Rectangle(hdc, fireRange.left, fireRange.top, fireRange.right, fireRange.bottom);
	Rectangle(hdc, enemyRect.left, enemyRect.top, enemyRect.right, enemyRect.bottom);
	Rectangle(hdc, obstacle.left, obstacle.top, obstacle.right, obstacle.bottom);

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void TestMinion::EnemyShot()
{
	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, enemyX, enemyY,
		getAngle(enemyX, enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
		5.0f, 500, enemyBulletInterval++, 50);
}

void TestMinion::EnemyAiTime()
{
	time++;
	if (time / 60 == 2)
	{
		rnd = RND->getFromIntTo(2, 5);
		time = 0;
	}
}
