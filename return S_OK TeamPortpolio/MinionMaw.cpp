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
	//����ü ���� ����
	EnemyInfo MinionMaw;
	MinionMaw.enemyNumber = EnemyNumber;
	MinionMaw.enemyRect = RectMakeCenter(position.x, position.y, 35, 35);
	MinionMaw.enemyHp = 25;
	MinionMaw.enemyShotSpeed = 5.0f;
	MinionMaw.enemyShotRange = 500.0f;
	MinionMaw.enemyShotDelay = 50;
	MinionMaw.enemySpeed = 1.5f;
	// �ִϸ��̼� Idle
	MinionMaw.enemyImage = IMAGEMANAGER->addFrameImage("mawIdle", "images/monster/maw/mawIdle.bmp", 64 * 2, 33 * 2, 2, 1, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addDefAnimation("maw", "mawIdle", 15, false, true);
	minionAni = ANIMATIONMANAGER->findAnimation("maw");
	vMinionMaw.push_back(MinionMaw);

	// IDLE
	firstEnemyAiPattern = 1;
	secondEnemyAiPattern = 1;
	thirdEnemyAiPattern = 1;

	enemyAreaCheck = false;

	return S_OK;
}

void MinionMaw::Release()
{
}

void MinionMaw::Update()
{
	EnemyAi();
	COLLISIONMANAGER->SameVectorMinionCollision(vMinionMaw);
}

void MinionMaw::Render(HDC hdc)
{
	for (i = 0; i < vMinionMaw.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			//Rectangle(hdc, vMinionMaw[i].enemyFireRange.left, vMinionMaw[i].enemyFireRange.top, vMinionMaw[i].enemyFireRange.right, vMinionMaw[i].enemyFireRange.bottom);
			Rectangle(hdc, vMinionMaw[i].enemyRect.left, vMinionMaw[i].enemyRect.top, vMinionMaw[i].enemyRect.right, vMinionMaw[i].enemyRect.bottom);

			HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
			FillRect(hdc, &vMinionMaw[i].enemyRect, brush);
			DeleteObject(brush);
		}

		if (enemyAtk)
		{
			vMinionMaw[i].enemyImage->aniRender(hdc, vMinionMaw[i].enemyRect.left - 20, vMinionMaw[i].enemyRect.top - 30, minionAni);
		}
		else
		{
			vMinionMaw[i].enemyImage->aniRender(hdc, vMinionMaw[i].enemyRect.left - 15, vMinionMaw[i].enemyRect.top - 15, minionAni);
		}
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionMaw::EnemyAiTime()
{
	switch (vMinionMaw[i].enemyNumber)
	{
	case 0:
		// AI ���� �ð�
		firstEnemyAiTime++;
		if (firstEnemyAiTime / 60 == 3)
		{
			firstEnemyAiPattern = RND->getFromIntTo(2, 5);
			firstEnemyAiTime = 0;
		}
		break;
	case 1:
		// AI ���� �ð�
		secondEnemyAiTime++;
		if (secondEnemyAiTime / 60 == 3)
		{
			secondEnemyAiPattern = RND->getFromIntTo(2, 5);
			secondEnemyAiTime = 0;
		}
		break;
	case 2:
		// AI ���� �ð�
		thirdEnemyAiTime++;
		if (thirdEnemyAiTime / 60 == 3)
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

		// �� x��, y�� ��ǥ
		vMinionMaw[i].enemyX = vMinionMaw[i].enemyRect.left + (vMinionMaw[i].enemyRect.right - vMinionMaw[i].enemyRect.left) / 2;
		vMinionMaw[i].enemyY = vMinionMaw[i].enemyRect.top + (vMinionMaw[i].enemyRect.bottom - vMinionMaw[i].enemyRect.top) / 2;

		// �÷��̾�� ���� ������ �浹��
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionMaw[i].enemyFireRange))
		{
			// �÷��̾ �Ѿư���.
			enemyAreaCheck = true;
		}

		// ���࿡ �÷��̾ ���� ���� �����ȿ� ���Դٸ� �÷��̾ �Ѿư���.
		if (enemyAreaCheck)
		{
			EnemyShot();

			// getdistance(���� ��ġ x, y, �÷��̾��� ��ġ x, y)
			distance = getDistance(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionMaw[i].enemyX) / distance * vMinionMaw[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionMaw[i].enemyY) / distance * vMinionMaw[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionMaw[i].enemySpeed;
			}

			// + - �ٲ㺸�� �̰� ���� ����� ��� �Ǵ���
			vMinionMaw[i].enemyX += vx;
			vMinionMaw[i].enemyY += vy;
			vMinionMaw[i].enemyRect = RectMakeCenter(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY, 35, 35);
		}
		// �����ȿ� �÷��̾ ���ٸ� �����ൿ(AI)
		else
		{
			enemyAtk = false;
			EnemyAiTime();

			switch (vMinionMaw[i].enemyNumber)
			{
			case 0:
				switch (firstEnemyAiPattern)
				{
				case 1:		// IDLE
					//�ִϸ��̼� ������
					ANIMATIONMANAGER->start("maw");
					break;
				case 2:		// LEFT
					if (vMinionMaw[i].enemyRect.left > 105) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.left <= 120)
					{
						firstEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionMaw[i].enemyRect.right < 780) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.right >= 760)
					{
						firstEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionMaw[i].enemyRect.top > 105) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.top <= 120)
					{
						firstEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionMaw[i].enemyRect.bottom < 465) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.bottom >= 450)
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
					//�ִϸ��̼� ������
					ANIMATIONMANAGER->start("maw");
					break;
				case 2:		// LEFT
					if (vMinionMaw[i].enemyRect.left > 105) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.left <= 120)
					{
						secondEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionMaw[i].enemyRect.right < 780) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.right >= 760)
					{
						secondEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionMaw[i].enemyRect.top > 105) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.top <= 120)
					{
						secondEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionMaw[i].enemyRect.bottom < 465) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.bottom >= 450)
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
					//�ִϸ��̼� ������
					ANIMATIONMANAGER->start("maw");
					break;
				case 2:		// LEFT
					if (vMinionMaw[i].enemyRect.left > 105) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.left <= 120)
					{
						thirdEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionMaw[i].enemyRect.right < 780) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.left += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.right += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.right >= 760)
					{
						thirdEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionMaw[i].enemyRect.top > 105) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top -= vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom -= vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.top <= 120)
					{
						thirdEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionMaw[i].enemyRect.bottom < 465) // ���� �̵� ���� ����
					{
						vMinionMaw[i].enemyRect.top += vMinionMaw[i].enemySpeed;
						vMinionMaw[i].enemyRect.bottom += vMinionMaw[i].enemySpeed;
					}
					if (vMinionMaw[i].enemyRect.bottom >= 450)
					{
						thirdEnemyAiPattern = 4;
					}
					break;
				}
				break;
			}
		}

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		vMinionMaw[i].enemyFireRange = RectMakeCenter(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY, 300, 300);
	}

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);

	// ���� ��� �ҷ� �浹
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void MinionMaw::EnemyShot()
{
	enemyAtk = true;

	if (enemyAtk)
	{
		// �ִϸ��̼�
		vMinionMaw[i].enemyImage = IMAGEMANAGER->addFrameImage("mawAttack", "images/monster/maw/mawAttack.bmp", 1510 / 2, 604 / 2, 10, 4, true, RGB(255, 0, 255));
		if (vMinionMaw[i].enemyX >= PLAYERMANAGER->GetPlayerHitRectX())
		{
			ANIMATIONMANAGER->addAnimation("mawAtkLeft", "mawAttack", 20, 39, 25, false, true);
			minionAni = ANIMATIONMANAGER->findAnimation("mawAtkLeft");
			ANIMATIONMANAGER->resume("mawAtkLeft");
		}
		else
		{
			ANIMATIONMANAGER->addAnimation("mawAtkRight", "mawAttack", 0, 19, 25, false, true);
			minionAni = ANIMATIONMANAGER->findAnimation("mawAtkRight");
			ANIMATIONMANAGER->resume("mawAtkRight");
		}
	}

	switch (vMinionMaw[i].enemyNumber)
	{
	case 0:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
			getAngle(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionMaw[i].enemyShotSpeed, vMinionMaw[i].enemyShotRange, firstEnemyBulletCount, vMinionMaw[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetFirstEnemyBulletCount();
		break;
	case 1:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
			getAngle(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionMaw[i].enemyShotSpeed, vMinionMaw[i].enemyShotRange, secondEnemyBulletCount, vMinionMaw[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetSecondEnemyBulletCount();
		break;
	case 2:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
			getAngle(vMinionMaw[i].enemyX, vMinionMaw[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionMaw[i].enemyShotSpeed, vMinionMaw[i].enemyShotRange, thirdEnemyBulletCount, vMinionMaw[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetThirdEnemyBulletCount();
		break;
	}
}

void MinionMaw::DeleteEnemy(int num)
{
	vMinionMaw.erase(vMinionMaw.begin() + num);
}

void MinionMaw::SetEnemyRectX(int enemyNum, int move)
{
	vMinionMaw[enemyNum].enemyRect.left += move;
	vMinionMaw[enemyNum].enemyRect.right += move;
}

void MinionMaw::SetEnemyRectY(int enemyNum, int move)
{
	vMinionMaw[enemyNum].enemyRect.top += move;
	vMinionMaw[enemyNum].enemyRect.bottom += move;
}
