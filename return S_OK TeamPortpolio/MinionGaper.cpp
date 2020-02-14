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
	//구조체 정보 기입
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

void MinionGaper::EnemyAi()
{
	for (i = 0; i < vMinionGaper.size(); i++)
	{
		RECT temp;

		// 적 x축, y축 좌표
		vMinionGaper[i].enemyX = vMinionGaper[i].enemyRect.left + (vMinionGaper[i].enemyRect.right - vMinionGaper[i].enemyRect.left) / 2;
		vMinionGaper[i].enemyY = vMinionGaper[i].enemyRect.top + (vMinionGaper[i].enemyRect.bottom - vMinionGaper[i].enemyRect.top) / 2;

		// 플레이어와 판정 범위가 충돌시
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionGaper[i].enemyFireRange))
		{
			// 플레이어를 쫓아가라.
			enemyAreaCheck = true;
		}

		// 만약에 플레이어가 적의 판정 범위안에 들어왔다면 플레이어를 쫓아간다.
		if (enemyAreaCheck)
		{
			// getdistance(적의 위치 x, y, 플레이어의 위치 x, y)
			distance = getDistance(vMinionGaper[i].enemyX, vMinionGaper[i].enemyY, PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY());

			if (distance)
			{
				// vector = ((플레이어 위치 x / y) - (적 위치 x / y) / 거리 * 적 속도;
				vx = ((PLAYERMANAGER->GetPlayerHitRectX()) - vMinionGaper[i].enemyX) / distance * vMinionGaper[i].enemySpeed;
				vy = ((PLAYERMANAGER->GetPlayerHitRectY()) - vMinionGaper[i].enemyY) / distance * vMinionGaper[i].enemySpeed;
			}
			else
			{
				vx = 0;
				vy = vMinionGaper[i].enemySpeed;
			}

			// + - 바꿔보기 이게 접근 방식이 어떻게 되는지
			vMinionGaper[i].enemyX += vx;
			vMinionGaper[i].enemyY += vy;
			vMinionGaper[i].enemyRect = RectMakeCenter(vMinionGaper[i].enemyX, vMinionGaper[i].enemyY, 30, 30);
		}
		// 범위안에 플레이어가 없다면 자율행동(AI)
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
					if (vMinionGaper[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionGaper[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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

		// 판정 범위가 항상 적의 좌표를 쫓아다님
		vMinionGaper[i].enemyFireRange = RectMakeCenter(vMinionGaper[i].enemyX, vMinionGaper[i].enemyY, 300, 300);
	}

	// 적이 쏘는 불렛의 움직임
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);

	// 적이 쏘는 불렛 충돌
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
