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
	//����ü ���� ����
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
	// AI ���� �ð�
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

		// �� x��, y�� ��ǥ
		viMinionMaw->enemyX = viMinionMaw->enemyRect.left + (viMinionMaw->enemyRect.right - viMinionMaw->enemyRect.left) / 2;
		viMinionMaw->enemyY = viMinionMaw->enemyRect.top + (viMinionMaw->enemyRect.bottom - viMinionMaw->enemyRect.top) / 2;

		// �÷��̾�� ���� ������ �浹��
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &viMinionMaw->enemyFireRange))
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
			distance = getDistance(viMinionMaw->enemyX, viMinionMaw->enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - viMinionMaw->enemyX) / distance * viMinionMaw->enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - viMinionMaw->enemyY) / distance * viMinionMaw->enemySpeed;
			}
			else
			{
				vx = 0;
				vy = viMinionMaw->enemySpeed;
			}

			// + - �ٲ㺸�� �̰� ���� ����� ��� �Ǵ���
			viMinionMaw->enemyX += vx;
			viMinionMaw->enemyY += vy;
			viMinionMaw->enemyRect = RectMakeCenter(viMinionMaw->enemyX, viMinionMaw->enemyY, 50, 50);
		}
		// �����ȿ� �÷��̾ ���ٸ� �����ൿ(AI)
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

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		viMinionMaw->enemyFireRange = RectMakeCenter(viMinionMaw->enemyX, viMinionMaw->enemyY, 300, 300);
	}

	// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
	SetEnemyBulletCount();

	// ���� ��� �ҷ��� ������
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