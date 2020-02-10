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
	//구조체 정보 기입
	EnemyInfo MinionBlackFly;
	MinionBlackFly.enemyNumber = EnemyNumber;
	MinionBlackFly.enemyRect = RectMakeCenter(position.x, position.y, 30, 30);
	MinionBlackFly.enemyHp = 20;
	MinionBlackFly.enemySpeed = 2.0f;
	vMinionBlackFly.push_back(MinionBlackFly);

	enemyMove = true;
	enemyAreaCheck = false;
	enemyCollision = false;

	return S_OK;
}

void MinionBlackFly::Release()
{
}

void MinionBlackFly::Update()
{
	EnemyAi();
}

void MinionBlackFly::Render(HDC hdc)
{
	for (i = 0; i < vMinionBlackFly.size(); i++)
	{
		//Rectangle(hdc, vMinionBlackFly[i].enemyFireRange.left, vMinionBlackFly[i].enemyFireRange.top, vMinionBlackFly[i].enemyFireRange.right, vMinionBlackFly[i].enemyFireRange.bottom);
		Rectangle(hdc, vMinionBlackFly[i].enemyRect.left, vMinionBlackFly[i].enemyRect.top, vMinionBlackFly[i].enemyRect.right, vMinionBlackFly[i].enemyRect.bottom);
	}
}

void MinionBlackFly::EnemyAiTime()
{
	switch (vMinionBlackFly[i].enemyNumber)
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

void MinionBlackFly::EnemyAi()
{
	for (i = 0; i < vMinionBlackFly.size(); i++)
	{
		RECT temp;

		// 적 x축, y축 좌표
		vMinionBlackFly[i].enemyX = vMinionBlackFly[i].enemyRect.left + (vMinionBlackFly[i].enemyRect.right - vMinionBlackFly[i].enemyRect.left) / 2;
		vMinionBlackFly[i].enemyY = vMinionBlackFly[i].enemyRect.top + (vMinionBlackFly[i].enemyRect.bottom - vMinionBlackFly[i].enemyRect.top) / 2;

		// 플레이어와 판정 범위가 충돌시
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionBlackFly[i].enemyFireRange))
		{
			// 적과 장애물이 충돌하지 않았다면
			if (!enemyCollision)
			{
				enemyAreaCheck = true;
			}
		}
		else
		{
			enemyAreaCheck = false;
		}

		// 왼쪽 일직선
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
		// 오른쪽 일직선
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
		// 위 일직선
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
		// 아래 일직선
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

		// 왼쪽이면 빠르게 움직여라
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
		// 오른쪽이면 빠르게 움직여라
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
		// 위면 빠르게 움직여라
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
		// 아래면 빠르게 움직여라
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

		// 자율행동(AI)
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
					if (vMinionBlackFly[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.left > 0) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.right < WINSIZEX) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.top > 0) // 몬스터 이동 범위 제한
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
					if (vMinionBlackFly[i].enemyRect.bottom < WINSIZEY) // 몬스터 이동 범위 제한
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

		// 판정 범위가 항상 적의 좌표를 쫓아다님
		vMinionBlackFly[i].enemyFireRange = RectMakeCenter(vMinionBlackFly[i].enemyX, vMinionBlackFly[i].enemyY, 300, 300);
	}
}