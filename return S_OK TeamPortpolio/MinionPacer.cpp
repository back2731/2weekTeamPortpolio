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
	MinionPacer.enemyRect = RectMakeCenter(position.x, position.y, 30, 22);
	MinionPacer.enemyHp = 10;
	MinionPacer.enemySpeed = 2.5f;
	// �ִϸ��̼� Idle
	MinionPacer.enemyShadowImage = IMAGEMANAGER->addImage("PacerShadow", "images/monster/pacer/pacerShadow.bmp", 120 / 3, 49 / 3, true, RGB(255, 0, 255));
	MinionPacer.enemyImage = IMAGEMANAGER->addFrameImage("PacerMove", "images/monster/pacer/pacerMove.bmp", 1419 / 2, 828 / 2, 11, 6, true, RGB(255, 0, 255));
	int arrPacerIdle[] = { 54 };
	ANIMATIONMANAGER->addAnimation("pacer", "PacerMove", arrPacerIdle, 1, 1, true);
	minionAni = ANIMATIONMANAGER->findAnimation("pacer");
	vMinionPacer.push_back(MinionPacer);

	return S_OK;
}

void MinionPacer::Release()
{
}

void MinionPacer::Update()
{
	EnemyAi();
	COLLISIONMANAGER->SameVectorMinionCollision(vMinionPacer);
}

void MinionPacer::Render(HDC hdc)
{
	for (i = 0; i < vMinionPacer.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			//Rectangle(hdc, vMinionPacer[i].enemyFireRange.left, vMinionPacer[i].enemyFireRange.top, vMinionPacer[i].enemyFireRange.right, vMinionPacer[i].enemyFireRange.bottom);
			Rectangle(hdc, vMinionPacer[i].enemyRect.left, vMinionPacer[i].enemyRect.top, vMinionPacer[i].enemyRect.right, vMinionPacer[i].enemyRect.bottom);

			HBRUSH brush = CreateSolidBrush(RGB(102, 255, 204));
			FillRect(hdc, &vMinionPacer[i].enemyRect, brush);
			DeleteObject(brush);
		}

		vMinionPacer[i].enemyShadowImage->alphaRender(hdc, vMinionPacer[i].enemyRect.left - 5, vMinionPacer[i].enemyRect.top + 13, 70);
		vMinionPacer[i].enemyImage->aniRender(hdc, vMinionPacer[i].enemyRect.left - 23, vMinionPacer[i].enemyRect.top - 25, minionAni);
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
				// �ִϸ��̼� Idle
				ANIMATIONMANAGER->resume("pacer");
				break;
			case 2:		// LEFT
				// �ִϸ��̼� Left
				ANIMATIONMANAGER->addAnimation("pacerLeft", "PacerMove", 0, 21, 15, false, true);
				minionAni = ANIMATIONMANAGER->findAnimation("pacerLeft");
				ANIMATIONMANAGER->resume("pacerLeft");

				if (vMinionPacer[i].enemyRect.left > 105) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.left -= vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.right -= vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.left <= 120)
				{
					firstEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				// �ִϸ��̼� RIGHT
				ANIMATIONMANAGER->addAnimation("pacerRight", "PacerMove", 22, 43, 15, false, true);
				minionAni = ANIMATIONMANAGER->findAnimation("pacerRight");
				ANIMATIONMANAGER->resume("pacerRight");

				if (vMinionPacer[i].enemyRect.right < 780) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.left += vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.right += vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.right >= 760)
				{
					firstEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				// �ִϸ��̼� Up
				ANIMATIONMANAGER->addAnimation("pacerUp", "PacerMove", 44, 65, 15, false, true);
				minionAni = ANIMATIONMANAGER->findAnimation("pacerUp");
				ANIMATIONMANAGER->resume("pacerUp");

				if (vMinionPacer[i].enemyRect.top > 105) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.top -= vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.bottom -= vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.top <= 120)
				{
					firstEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				// �ִϸ��̼� Down
				ANIMATIONMANAGER->addAnimation("pacerDown", "PacerMove", 44, 65, 15, false, true);
				minionAni = ANIMATIONMANAGER->findAnimation("pacerDown");
				ANIMATIONMANAGER->resume("pacerDown");

				if (vMinionPacer[i].enemyRect.bottom < 465) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.top += vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.bottom += vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.bottom >= 450)
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
				if (vMinionPacer[i].enemyRect.left > 105) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.left -= vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.right -= vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.left <= 120)
				{
					secondEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionPacer[i].enemyRect.right < 780) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.left += vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.right += vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.right >= 760)
				{
					secondEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionPacer[i].enemyRect.top > 105) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.top -= vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.bottom -= vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.top <= 120)
				{
					secondEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionPacer[i].enemyRect.bottom < 465) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.top += vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.bottom += vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.bottom >= 450)
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
				if (vMinionPacer[i].enemyRect.left > 105) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.left -= vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.right -= vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.left <= 120)
				{
					thirdEnemyAiPattern = 3;
				}
				break;
			case 3:		// RIGHT
				if (vMinionPacer[i].enemyRect.right < 780) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.left += vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.right += vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.right >= 760)
				{
					thirdEnemyAiPattern = 2;
				}
				break;
			case 4:		// UP
				if (vMinionPacer[i].enemyRect.top > 105) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.top -= vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.bottom -= vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.top <= 120)
				{
					thirdEnemyAiPattern = 5;
				}
				break;
			case 5:		// DOWN
				if (vMinionPacer[i].enemyRect.bottom < 465) // ���� �̵� ���� ����
				{
					vMinionPacer[i].enemyRect.top += vMinionPacer[i].enemySpeed;
					vMinionPacer[i].enemyRect.bottom += vMinionPacer[i].enemySpeed;
				}
				if (vMinionPacer[i].enemyRect.bottom >= 450)
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

void MinionPacer::SetEnemyRectX(int enemyNum, int move)
{
	vMinionPacer[enemyNum].enemyRect.left += move;
	vMinionPacer[enemyNum].enemyRect.right += move;
}

void MinionPacer::SetEnemyRectY(int enemyNum, int move)
{
	vMinionPacer[enemyNum].enemyRect.top += move;
	vMinionPacer[enemyNum].enemyRect.bottom += move;
}
