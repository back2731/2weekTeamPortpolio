#include "stdafx.h"
#include "MinionPacer.h"

MinionPacer::MinionPacer()
{
}

MinionPacer::~MinionPacer()
{
}

HRESULT MinionPacer::Init(POINT position, int EnemyNumber)
{
	//����ü ���� ����
	EnemyInfo MinionPacer;
	MinionPacer.enemyNumber = EnemyNumber;
	MinionPacer.enemyRect = RectMakeCenter(position.x, position.y, 30, 30);
	MinionPacer.enemyHp = 10;
	MinionPacer.enemySpeed = 3.0f;
	vMinionPacer.push_back(MinionPacer);

	return S_OK;
}

void MinionPacer::Release()
{
}

void MinionPacer::Update()
{
	EnemyAi();
}

void MinionPacer::Render(HDC hdc)
{
	for (i = 0; i < vMinionPacer.size(); i++)
	{
		//Rectangle(hdc, vMinionPacer[i].enemyFireRange.left, vMinionPacer[i].enemyFireRange.top, vMinionPacer[i].enemyFireRange.right, vMinionPacer[i].enemyFireRange.bottom);
		Rectangle(hdc, vMinionPacer[i].enemyRect.left, vMinionPacer[i].enemyRect.top, vMinionPacer[i].enemyRect.right, vMinionPacer[i].enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionPacer::EnemyAiTime()
{
	switch (vMinionPacer[i].enemyNumber)
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

void MinionPacer::EnemyAi()
{
	for (i = 0; i < vMinionPacer.size(); i++)
	{
			EnemyAiTime();

			switch (vMinionPacer[i].enemyNumber)
			{
			case 0:
				switch (firstEnemyAiPattern)
				{
				case 1:		// IDLE
					break;
				case 2:		// LEFT
					if (vMinionPacer[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.left -= vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.right -= vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.left <= 10)
					{
						firstEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionPacer[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.left += vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.right += vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.right >= 950)
					{
						firstEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionPacer[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.top -= vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.bottom -= vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.top <= 10)
					{
						firstEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionPacer[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.top += vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.bottom += vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.bottom >= 530)
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
					if (vMinionPacer[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.left -= vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.right -= vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.left <= 10)
					{
						secondEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionPacer[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.left += vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.right += vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.right >= 950)
					{
						secondEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionPacer[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.top -= vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.bottom -= vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.top <= 10)
					{
						secondEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionPacer[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.top += vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.bottom += vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.bottom >= 530)
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
					if (vMinionPacer[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.left -= vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.right -= vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.left <= 10)
					{
						thirdEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionPacer[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.left += vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.right += vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.right >= 950)
					{
						thirdEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionPacer[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.top -= vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.bottom -= vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.top <= 10)
					{
						thirdEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionPacer[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionPacer[i].enemyRect.top += vMinionPacer[i].enemySpeed;
						vMinionPacer[i].enemyRect.bottom += vMinionPacer[i].enemySpeed;
					}
					if (vMinionPacer[i].enemyRect.bottom >= 530)
					{
						thirdEnemyAiPattern = 4;
					}
					break;
				}
				break;
			}

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		vMinionPacer[i].enemyFireRange = RectMakeCenter(vMinionPacer[i].enemyX, vMinionPacer[i].enemyY, 200, 200);
	}
}

void MinionPacer::DeleteEnemy(int num)
{
	vMinionPacer.erase(vMinionPacer.begin() + num);
}