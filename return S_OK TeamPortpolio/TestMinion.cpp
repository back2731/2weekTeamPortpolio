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
	// �׽�Ʈ�� ���׹� ��Ʈ
	enemyRect = RectMakeCenter(position.x, position.y, 50, 50);
	// �׽�Ʈ�� ��ֹ� ��Ʈ
	obstacle = RectMakeCenter(WINSIZEX / 2 + 150, WINSIZEY / 2, 50, 300);

	firstEnemyAiTime = 0;		// �ൿ�ð�
	firstEnemyAiPattern = 1;		// �ൿ���� (�⺻ IDLE)
	speed = 3.0f;			// �̵��ӵ�

	obstacleX = obstacle.left + (obstacle.right - obstacle.left) / 2;	// ��ֹ� x�� ��ǥ
	obstacleY = obstacle.top + (obstacle.bottom - obstacle.top) / 2;	// ��ֹ� y�� ��ǥ

	enemyAreaCheck = false;
	enemyCollision = false;

	return S_OK;
}

void TestMinion::Release()
{
}

void TestMinion::Update()
{
	// �� x��, y�� ��ǥ
	enemyX = enemyRect.left + (enemyRect.right - enemyRect.left) / 2;
	enemyY = enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2;

	// �÷��̾�� ���� ������ �浹��
	if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &fireRange))
	{
		// ���� ��ֹ��� �浹���� �ʾҴٸ�
		if (!enemyCollision)
		{
			// �÷��̾ �Ѿư���.
			enemyAreaCheck = true;
			EnemyShot();
		}
	}

	// ���࿡ �÷��̾ ���� ���� �����ȿ� ���Դٸ� �÷��̾ �Ѿư���.
	if (enemyAreaCheck)
	{
		// getdistance(���� ��ġ x, y, �÷��̾��� ��ġ x, y)
		distance = getDistance(enemyX, enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

		if (distance)
		{
			// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
			vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - enemyX) / distance * speed;
			vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - enemyY) / distance * speed;
		}
		else
		{
			vx = 0;
			vy = speed;
		}

		// + - �ٲ㺸�� �̰� ���� ����� ��� �Ǵ���
		enemyX += vx;
		enemyY += vy;
		enemyRect = RectMakeCenter(enemyX, enemyY, 50, 50);
	}
	// �����ȿ� �÷��̾ ���ٸ� �����ൿ(AI)
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

	// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
	fireRange = RectMakeCenter(enemyX, enemyY, 300, 300);

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);

	// ���� ��ֹ��� �浹�ϸ� true
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

		// ��ֹ��� �浹�� �񲸼� �����δ�.
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
	// ���� ��ֹ��� �浹���� ������ false
	else
	{
		enemyCollision = false;
	}

	// �÷��̾�� ���� �浹�ϸ� �з�����.
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
	// ���� �Ѿ� �߻�
	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, enemyX, enemyY,
		getAngle(enemyX, enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
		5.0f, 500, firstEnemyBulletCount, 50);

	// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
	SetFirstEnemyBulletCount();
}

void TestMinion::EnemyAiTime()
{
	// AI ���� �ð�
	firstEnemyAiTime++;
	if (firstEnemyAiTime / 60 == 2)
	{
		firstEnemyAiPattern = RND->getFromIntTo(2, 5);
		firstEnemyAiTime = 0;
	}
}