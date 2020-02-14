#include "stdafx.h"
#include "MinionBlackFly.h"

MinionBlackFly::MinionBlackFly()
{
}

MinionBlackFly::~MinionBlackFly()
{
}

HRESULT MinionBlackFly::Init(POINT position, int EnemyNumber)
{
	//blackFly = IMAGEMANAGER->addFrameImage("blackfly", "images/monster/blackfly.bmp", 128 * 2, 128 * 2, 4, 4, true, RGB(255, 0, 255));
	//ANIMATIONMANAGER->addDefAnimation("ani1", "blackfly", 10, false, true);
	//ani = ANIMATIONMANAGER->findAnimation("ani1");

	//����ü ���� ����
	EnemyInfo MinionBlackFly;
	MinionBlackFly.enemyNumber = EnemyNumber;
	MinionBlackFly.enemyRect = RectMakeCenter(position.x, position.y, 30, 30);
	MinionBlackFly.enemyHp = 20;
	MinionBlackFly.enemySpeed = 2.0f;
	vMinionBlackFly.push_back(MinionBlackFly);

	enemyMove = true;
	enemyAreaCheck = false;

	return S_OK;
}

void MinionBlackFly::Release()
{
}

void MinionBlackFly::Update()
{
	EnemyAi();
	COLLISIONMANAGER->SameVectorMinionCollision(vMinionBlackFly);
}

void MinionBlackFly::Render(HDC hdc)
{
	for (i = 0; i < vMinionBlackFly.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			//Rectangle(hdc, vMinionBlackFly[i].enemyFireRange.left, vMinionBlackFly[i].enemyFireRange.top, vMinionBlackFly[i].enemyFireRange.right, vMinionBlackFly[i].enemyFireRange.bottom);
			Rectangle(hdc, vMinionBlackFly[i].enemyRect.left, vMinionBlackFly[i].enemyRect.top, vMinionBlackFly[i].enemyRect.right, vMinionBlackFly[i].enemyRect.bottom);

			HBRUSH brush = CreateSolidBrush(RGB(255, 153, 0));
			FillRect(hdc, &vMinionBlackFly[i].enemyRect, brush);
			DeleteObject(brush);
		}
		//blackFly->aniRender(hdc, vMinionBlackFly[i].enemyRect.left - 20, vMinionBlackFly[i].enemyRect.top - 15, ani);
	}
}

void MinionBlackFly::EnemyAiTime()
{
	switch (vMinionBlackFly[i].enemyNumber)
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

void MinionBlackFly::EnemyAi()
{
	for (i = 0; i < vMinionBlackFly.size(); i++)
	{
		//�ִϸ��̼� ������
		//ani = ANIMATIONMANAGER->findAnimation("ani1");
		//ANIMATIONMANAGER->start("ani1");

		RECT temp;

		// �� x��, y�� ��ǥ
		vMinionBlackFly[i].enemyX = vMinionBlackFly[i].enemyRect.left + (vMinionBlackFly[i].enemyRect.right - vMinionBlackFly[i].enemyRect.left) / 2;
		vMinionBlackFly[i].enemyY = vMinionBlackFly[i].enemyRect.top + (vMinionBlackFly[i].enemyRect.bottom - vMinionBlackFly[i].enemyRect.top) / 2;

		// �÷��̾�� ���� ������ �浹��
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionBlackFly[i].enemyFireRange))
		{
			enemyAreaCheck = true;
		}
		else
		{
			enemyAreaCheck = false;
		}

		// ���� ������
		if (vMinionBlackFly[i].enemyX > PLAYERMANAGER->GetPlayerHitRectX() &&
			(vMinionBlackFly[i].enemyRect.top) < PLAYERMANAGER->GetPlayerHitRectY() &&
			(vMinionBlackFly[i].enemyRect.bottom) > PLAYERMANAGER->GetPlayerHitRectY() &&
			enemyAreaCheck)
		{
			enemyMove = false;
			enemyLeftBoost = true;
			enemyRightBoost = false;
			enemyUpBoost = false;
			enemyDownBoost = false;
		}
		// ������ ������
		else if (vMinionBlackFly[i].enemyX < PLAYERMANAGER->GetPlayerHitRectX() &&
			(vMinionBlackFly[i].enemyRect.top) < PLAYERMANAGER->GetPlayerHitRectY() &&
			(vMinionBlackFly[i].enemyRect.bottom) > PLAYERMANAGER->GetPlayerHitRectY() &&
			enemyAreaCheck)
		{
			enemyMove = false;
			enemyRightBoost = true;
			enemyLeftBoost = false;
			enemyUpBoost = false;
			enemyDownBoost = false;
		}
		// �� ������
		else if (vMinionBlackFly[i].enemyY > PLAYERMANAGER->GetPlayerHitRectY())
		{
			if ((vMinionBlackFly[i].enemyRect.left) < PLAYERMANAGER->GetPlayerHitRectX() &&
				(vMinionBlackFly[i].enemyRect.right) > PLAYERMANAGER->GetPlayerHitRectX() &&
				enemyAreaCheck)
			{
				enemyMove = false;
				enemyUpBoost = true;
				enemyDownBoost = false;
				enemyLeftBoost = false;
				enemyRightBoost = false;
			}
		}
		// �Ʒ� ������
		else if (vMinionBlackFly[i].enemyY < PLAYERMANAGER->GetPlayerHitRectY())
		{
			if ((vMinionBlackFly[i].enemyRect.left) < PLAYERMANAGER->GetPlayerHitRectX() &&
				(vMinionBlackFly[i].enemyRect.right) > PLAYERMANAGER->GetPlayerHitRectX() &&
				enemyAreaCheck)
			{
				enemyMove = false;
				enemyDownBoost = true;
				enemyUpBoost = false;
				enemyLeftBoost = false;
				enemyRightBoost = false;
			}
		}

		// �����̸� ������ ��������
		if (enemyLeftBoost)
		{
			vMinionBlackFly[i].enemyRect.left -= vMinionBlackFly[i].enemySpeed * 2;
			vMinionBlackFly[i].enemyRect.right -= vMinionBlackFly[i].enemySpeed * 2;

			if (vMinionBlackFly[i].enemyRect.left <= 30)
			{
				enemyMove = true;
				enemyLeftBoost = false;
				enemyAreaCheck = false;
			}
		}
		// �������̸� ������ ��������
		else if (enemyRightBoost)
		{
			vMinionBlackFly[i].enemyRect.left += vMinionBlackFly[i].enemySpeed * 2;
			vMinionBlackFly[i].enemyRect.right += vMinionBlackFly[i].enemySpeed * 2;

			if (vMinionBlackFly[i].enemyRect.right >= 930)
			{
				enemyMove = true;
				enemyRightBoost = false;
				enemyAreaCheck = false;
			}
		}
		// ���� ������ ��������
		else if (enemyUpBoost)
		{
			vMinionBlackFly[i].enemyRect.top -= vMinionBlackFly[i].enemySpeed * 2;
			vMinionBlackFly[i].enemyRect.bottom -= vMinionBlackFly[i].enemySpeed * 2;

			if (vMinionBlackFly[i].enemyRect.top <= 30)
			{
				enemyMove = true;
				enemyUpBoost = false;
				enemyAreaCheck = false;
			}
		}
		// �Ʒ��� ������ ��������
		else if (enemyDownBoost)
		{
			vMinionBlackFly[i].enemyRect.top += vMinionBlackFly[i].enemySpeed * 2;
			vMinionBlackFly[i].enemyRect.bottom += vMinionBlackFly[i].enemySpeed * 2;

			if (vMinionBlackFly[i].enemyRect.bottom >= 510)
			{
				enemyMove = true;
				enemyDownBoost = false;
				enemyAreaCheck = false;
			}
		}

		// �����ൿ(AI)
		if (enemyMove)
		{

			EnemyAiTime();

			switch (vMinionBlackFly[i].enemyNumber)
			{
			case 0:
				switch (firstEnemyAiPattern)
				{
				case 1:		// IDLE
					break;
				case 2:		// LEFT
					if (vMinionBlackFly[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.left -= vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.right -= vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.left <= 10)
					{
						firstEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionBlackFly[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.left += vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.right += vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.right >= 950)
					{
						firstEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionBlackFly[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.top -= vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.bottom -= vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.top <= 10)
					{
						firstEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionBlackFly[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.top += vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.bottom += vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.bottom >= 530)
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
					if (vMinionBlackFly[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.left -= vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.right -= vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.left <= 10)
					{
						secondEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionBlackFly[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.left += vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.right += vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.right >= 950)
					{
						secondEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionBlackFly[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.top -= vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.bottom -= vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.top <= 10)
					{
						secondEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionBlackFly[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.top += vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.bottom += vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.bottom >= 530)
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
					if (vMinionBlackFly[i].enemyRect.left > 0) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.left -= vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.right -= vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.left <= 10)
					{
						thirdEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionBlackFly[i].enemyRect.right < WINSIZEX) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.left += vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.right += vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.right >= 950)
					{
						thirdEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionBlackFly[i].enemyRect.top > 0) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.top -= vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.bottom -= vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.top <= 10)
					{
						thirdEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionBlackFly[i].enemyRect.bottom < WINSIZEY) // ���� �̵� ���� ����
					{
						vMinionBlackFly[i].enemyRect.top += vMinionBlackFly[i].enemySpeed;
						vMinionBlackFly[i].enemyRect.bottom += vMinionBlackFly[i].enemySpeed;
					}
					if (vMinionBlackFly[i].enemyRect.bottom >= 530)
					{
						thirdEnemyAiPattern = 4;
					}
					break;
				}
				break;
			}
		}

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		vMinionBlackFly[i].enemyFireRange = RectMakeCenter(vMinionBlackFly[i].enemyX, vMinionBlackFly[i].enemyY, 200, 200);
	}
}

void MinionBlackFly::DeleteEnemy(int num)
{
	vMinionBlackFly.erase(vMinionBlackFly.begin() + num);
}

void MinionBlackFly::SetEnemyRectX(int enemyNum, int move)
{
	vMinionBlackFly[enemyNum].enemyRect.left += move;
	vMinionBlackFly[enemyNum].enemyRect.right += move;
}

void MinionBlackFly::SetEnemyRectY(int enemyNum, int move)
{
	vMinionBlackFly[enemyNum].enemyRect.top += move;
	vMinionBlackFly[enemyNum].enemyRect.bottom += move;
}
