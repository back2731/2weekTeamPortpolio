#include "stdafx.h"
#include "MinionGaper.h"

MinionGaper::MinionGaper()
{
}

MinionGaper::~MinionGaper()
{
}

HRESULT MinionGaper::Init(POINT position, int EnemyNumber)
{
	//����ü ���� ����
	EnemyInfo MinionGaper;
	MinionGaper.enemyNumber = EnemyNumber;
	MinionGaper.enemyRect = RectMakeCenter(position.x, position.y, 30, 30);
	MinionGaper.enemyHp = 10;
	MinionGaper.enemySpeed = 2.5f;
	vMinionGaper.push_back(MinionGaper);

	enemyAreaCheck = false;

	return S_OK;
}

void MinionGaper::Release()
{
}

void MinionGaper::Update()
{
	EnemyAi();
	COLLISIONMANAGER->SameVectorMinionCollision(vMinionGaper);
}

void MinionGaper::Render(HDC hdc)
{
	for (i = 0; i < vMinionGaper.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			//Rectangle(hdc, vMinionGaper[i].enemyFireRange.left, vMinionGaper[i].enemyFireRange.top, vMinionGaper[i].enemyFireRange.right, vMinionGaper[i].enemyFireRange.bottom);
			Rectangle(hdc, vMinionGaper[i].enemyRect.left, vMinionGaper[i].enemyRect.top, vMinionGaper[i].enemyRect.right, vMinionGaper[i].enemyRect.bottom);

			HBRUSH brush = CreateSolidBrush(RGB(102, 0, 204));
			FillRect(hdc, &vMinionGaper[i].enemyRect, brush);
			DeleteObject(brush);
		}
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionGaper::EnemyAiTime()
{
	switch (vMinionGaper[i].enemyNumber)
	{
	case 0:
		// AI ���� �ð�
		firstEnemyAiTime++;
		if (firstEnemyAiTime / 60 == 2)
		{
			firstEnemyAiPattern = RND->getFromIntTo(2, 5);
			firstEnemyAiTime = 0;
		}
		break;
	case 1:
		// AI ���� �ð�
		secondEnemyAiTime++;
		if (secondEnemyAiTime / 60 == 2)
		{
			secondEnemyAiPattern = RND->getFromIntTo(2, 5);
			secondEnemyAiTime = 0;
		}
		break;
	case 2:
		// AI ���� �ð�
		thirdEnemyAiTime++;
		if (thirdEnemyAiTime / 60 == 2)
		{
			thirdEnemyAiPattern = RND->getFromIntTo(2, 5);
			thirdEnemyAiTime = 0;
		}
		break;
	}
}

void MinionGaper::EnemyAi()
{
	for (i = 0; i < vMinionGaper.size(); i++)
	{
		RECT temp;

		// �� x��, y�� ��ǥ
		vMinionGaper[i].enemyX = vMinionGaper[i].enemyRect.left + (vMinionGaper[i].enemyRect.right - vMinionGaper[i].enemyRect.left) / 2;
		vMinionGaper[i].enemyY = vMinionGaper[i].enemyRect.top + (vMinionGaper[i].enemyRect.bottom - vMinionGaper[i].enemyRect.top) / 2;

		// �÷��̾�� ���� ������ �浹��
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionGaper[i].enemyFireRange))
		{
			// �÷��̾ �Ѿư���.
			enemyAreaCheck = true;
		}

		// ���࿡ �÷��̾ ���� ���� �����ȿ� ���Դٸ� �÷��̾ �Ѿư���.
		if (enemyAreaCheck)
		{
			// getdistance(���� ��ġ x, y, �÷��̾��� ��ġ x, y)
			distance = getDistance(vMinionGaper[i].enemyX, vMinionGaper[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((�÷��̾� ��ġ x / y) - (�� ��ġ x / y) / �Ÿ� * �� �ӵ�;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionGaper[i].enemyX) / distance * vMinionGaper[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionGaper[i].enemyY) / distance * vMinionGaper[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionGaper[i].enemySpeed;
			}

			// + - �ٲ㺸�� �̰� ���� ����� ��� �Ǵ���
			vMinionGaper[i].enemyX += vx;
			vMinionGaper[i].enemyY += vy;
			vMinionGaper[i].enemyRect = RectMakeCenter(vMinionGaper[i].enemyX, vMinionGaper[i].enemyY, 30, 30);
		}
		// �����ȿ� �÷��̾ ���ٸ� �����ൿ(AI)
		else
		{
			EnemyAiTime();

			switch (vMinionGaper[i].enemyNumber)
			{
			case 0:
				switch (firstEnemyAiPattern)
				{
				case 1:		// IDLE
					break;
				case 2:		// LEFT
					if (vMinionGaper[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.left -= vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.right -= vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.left <= 10)
					{
						firstEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionGaper[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.left += vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.right += vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.right >= 830)
					{
						firstEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionGaper[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.top -= vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.bottom -= vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.top <= 10)
					{
						firstEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionGaper[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.top += vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.bottom += vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.bottom >= 530)
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
					if (vMinionGaper[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.left -= vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.right -= vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.left <= 10)
					{
						secondEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionGaper[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.left += vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.right += vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.right >= 830)
					{
						secondEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionGaper[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.top -= vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.bottom -= vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.top <= 10)
					{
						secondEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionGaper[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.top += vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.bottom += vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.bottom >= 530)
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
					if (vMinionGaper[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.left -= vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.right -= vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.left <= 10)
					{
						thirdEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionGaper[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.left += vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.right += vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.right >= 830)
					{
						thirdEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionGaper[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.top -= vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.bottom -= vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.top <= 10)
					{
						thirdEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionGaper[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionGaper[i].enemyRect.top += vMinionGaper[i].enemySpeed;
						vMinionGaper[i].enemyRect.bottom += vMinionGaper[i].enemySpeed;
					}
					if (vMinionGaper[i].enemyRect.bottom >= 530)
					{
						thirdEnemyAiPattern = 4;
					}
					break;
				}
				break;
			}
		}

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		vMinionGaper[i].enemyFireRange = RectMakeCenter(vMinionGaper[i].enemyX, vMinionGaper[i].enemyY, 300, 300);
	}

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);

	// ���� ��� �ҷ� �浹
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void MinionGaper::DeleteEnemy(int num)
{
	vMinionGaper.erase(vMinionGaper.begin() + num);
}

void MinionGaper::SetEnemyRectX(int enemyNum, int move)
{
	vMinionGaper[enemyNum].enemyRect.left += move;
	vMinionGaper[enemyNum].enemyRect.right += move;
}

void MinionGaper::SetEnemyRectY(int enemyNum, int move)
{
	vMinionGaper[enemyNum].enemyRect.top += move;
	vMinionGaper[enemyNum].enemyRect.bottom += move;
}
