#include "stdafx.h"
#include "MinionAttackFly.h"

MinionAttackFly::MinionAttackFly()
{
}

MinionAttackFly::~MinionAttackFly()
{
}

HRESULT MinionAttackFly::Init(POINT position, int EnemyNumber)
{
	//구조체 정보 기입
	EnemyInfo MinionAttackFly;
	MinionAttackFly.enemyNumber = EnemyNumber;
	MinionAttackFly.enemyRect = RectMakeCenter(position.x, position.y, 30, 30);
	MinionAttackFly.enemyHp = 5;
	MinionAttackFly.enemySpeed = 2.0f;
	vMinionAttackFly.push_back(MinionAttackFly);

	enemyAreaCheck = false;

	return S_OK;
}

void MinionAttackFly::Release()
{
}

void MinionAttackFly::Update()
{
	EnemyAi();
	COLLISIONMANAGER->SameVectorMinionCollision(vMinionAttackFly);
}

void MinionAttackFly::Render(HDC hdc)
{
	for (i = 0; i < vMinionAttackFly.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			//Rectangle(hdc, vMinionAttackFly[i].enemyFireRange.left, vMinionAttackFly[i].enemyFireRange.top, vMinionAttackFly[i].enemyFireRange.right, vMinionAttackFly[i].enemyFireRange.bottom);
			Rectangle(hdc, vMinionAttackFly[i].enemyRect.left, vMinionAttackFly[i].enemyRect.top, vMinionAttackFly[i].enemyRect.right, vMinionAttackFly[i].enemyRect.bottom);

			HBRUSH brush = CreateSolidBrush(RGB(163, 255, 0));
			FillRect(hdc, &vMinionAttackFly[i].enemyRect, brush);
			DeleteObject(brush);
		}
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionAttackFly::EnemyAiTime()
{
	switch (vMinionAttackFly[i].enemyNumber)
	{
	case 0:
		// AI 패턴 시간
		firstEnemyAiTime++;
		if (firstEnemyAiTime / 60 == 2)
		{
			firstEnemyAiPattern = RND->getFromIntTo(2, 5);
			firstEnemyAiTime = 0;
		}
		break;
	case 1:
		// AI 패턴 시간
		secondEnemyAiTime++;
		if (secondEnemyAiTime / 60 == 2)
		{
			secondEnemyAiPattern = RND->getFromIntTo(2, 5);
			secondEnemyAiTime = 0;
		}
		break;
	case 2:
		// AI 패턴 시간
		thirdEnemyAiTime++;
		if (thirdEnemyAiTime / 60 == 2)
		{
			thirdEnemyAiPattern = RND->getFromIntTo(2, 5);
			thirdEnemyAiTime = 0;
		}
		break;
	}
}

void MinionAttackFly::EnemyAi()
{
	for (i = 0; i < vMinionAttackFly.size(); i++)
	{
		RECT temp;

		// 적 x축, y축 좌표
		vMinionAttackFly[i].enemyX = vMinionAttackFly[i].enemyRect.left + (vMinionAttackFly[i].enemyRect.right - vMinionAttackFly[i].enemyRect.left) / 2;
		vMinionAttackFly[i].enemyY = vMinionAttackFly[i].enemyRect.top + (vMinionAttackFly[i].enemyRect.bottom - vMinionAttackFly[i].enemyRect.top) / 2;

		// 플레이어와 판정 범위가 충돌시
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionAttackFly[i].enemyFireRange))
		{
			// 플레이어를 쫓아가라.
			enemyAreaCheck = true;
		}

		// 만약에 플레이어가 적의 판정 범위안에 들어왔다면 플레이어를 쫓아간다.
		if (enemyAreaCheck)
		{
			// getdistance(적의 위치 x, y, 플레이어의 위치 x, y)
			distance = getDistance(vMinionAttackFly[i].enemyX, vMinionAttackFly[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((플레이어 위치 x / y) - (적 위치 x / y) / 거리 * 적 속도;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionAttackFly[i].enemyX) / distance * vMinionAttackFly[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionAttackFly[i].enemyY) / distance * vMinionAttackFly[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionAttackFly[i].enemySpeed;
			}

			// + - 바꿔보기 이게 접근 방식이 어떻게 되는지
			vMinionAttackFly[i].enemyX += vx;
			vMinionAttackFly[i].enemyY += vy;
			vMinionAttackFly[i].enemyRect = RectMakeCenter(vMinionAttackFly[i].enemyX, vMinionAttackFly[i].enemyY, 30, 30);
		}
		// 범위안에 플레이어가 없다면 자율행동(AI)
		else
		{
			EnemyAiTime();

			switch (vMinionAttackFly[i].enemyNumber)
			{
			case 0:
				switch (firstEnemyAiPattern)
				{
				case 1:		// IDLE
					break;
				case 2:		// LEFT
					if (vMinionAttackFly[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.left -= vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.right -= vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.left <= 10)
					{
						firstEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionAttackFly[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.left += vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.right += vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.right >= 950)
					{
						firstEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionAttackFly[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.top -= vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.bottom -= vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.top <= 10)
					{
						firstEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionAttackFly[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.top += vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.bottom += vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.bottom >= 530)
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
					if (vMinionAttackFly[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.left -= vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.right -= vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.left <= 10)
					{
						secondEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionAttackFly[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.left += vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.right += vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.right >= 950)
					{
						secondEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionAttackFly[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.top -= vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.bottom -= vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.top <= 10)
					{
						secondEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionAttackFly[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.top += vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.bottom += vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.bottom >= 530)
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
					if (vMinionAttackFly[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.left -= vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.right -= vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.left <= 10)
					{
						thirdEnemyAiPattern = 3;
					}
					break;
				case 3:		// RIGHT
					if (vMinionAttackFly[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.left += vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.right += vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.right >= 950)
					{
						thirdEnemyAiPattern = 2;
					}
					break;
				case 4:		// UP
					if (vMinionAttackFly[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.top -= vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.bottom -= vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.top <= 10)
					{
						thirdEnemyAiPattern = 5;
					}
					break;
				case 5:		// DOWN
					if (vMinionAttackFly[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
					{
						vMinionAttackFly[i].enemyRect.top += vMinionAttackFly[i].enemySpeed;
						vMinionAttackFly[i].enemyRect.bottom += vMinionAttackFly[i].enemySpeed;
					}
					if (vMinionAttackFly[i].enemyRect.bottom >= 530)
					{
						thirdEnemyAiPattern = 4;
					}
					break;
				}
				break;
			}
		}

		// 판정 범위가 항상 적의 좌표를 쫓아다님
		vMinionAttackFly[i].enemyFireRange = RectMakeCenter(vMinionAttackFly[i].enemyX, vMinionAttackFly[i].enemyY, 300, 300);
	}

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// 적이 쏘는 불렛 충돌
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void MinionAttackFly::DeleteEnemy(int num)
{
	vMinionAttackFly.erase(vMinionAttackFly.begin() + num);
}

void MinionAttackFly::SetEnemyRectX(int enemyNum, int move)
{
	vMinionAttackFly[enemyNum].enemyRect.left += move;
	vMinionAttackFly[enemyNum].enemyRect.right += move;
}

void MinionAttackFly::SetEnemyRectY(int enemyNum, int move)
{
	vMinionAttackFly[enemyNum].enemyRect.top += move;
	vMinionAttackFly[enemyNum].enemyRect.bottom += move;
}


