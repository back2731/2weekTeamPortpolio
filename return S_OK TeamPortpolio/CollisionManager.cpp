#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::UpdateCollision()
{
	PlayerToMinionCollision();
	SameVectorMinionCollision();
	MinionToMinionCollision();
}

void CollisionManager::PlayerBulletCollision(vector<BulletInfo>& playerBulletVector, vector<BulletInfo>::iterator& playerBulletIter)
{
	RECT temp;

	if (!playerBulletVector.empty())
	{
		// Monstro 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMonstro()->GetMinionVector().size(); j++)
		{
			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMonstro()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMonstro()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMonstro()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionAttackFly 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); j++)
		{
			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionAttackFly()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionBlackFly 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionBlackFly()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionMaw 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionMaw()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionTumor 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
		{
			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionTumor()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionClot 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionClot()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionClotty 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionClotty()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionGaper 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionGaper()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionHorf 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionHorf()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionHorf()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionMulligan 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionMulligan()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}

		// MinionPacer 충돌
		for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
				{
					// 오브젝트 풀로 총알을 돌려주는 함수
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// 피격이 된 적의 벡터를 지우는 함수
					ENEMYMANAGER->GetMinionPacer()->DeleteEnemy(j);

					// j번째 미니언이 피격 시 j를 0으로 초기화
					j = 0;

					// 벡터값이 비어있으면 for문을 빠져나간다.
					if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().empty())
					{
						break;
					}
				}
				else
				{
					++playerBulletIter;
				}
			}
		}
	}
}

void CollisionManager::EnemyBulletCollision(vector<BulletInfo>& enemyBulletVector, vector<BulletInfo>::iterator & enemyBulletIter)
{
	RECT temp;

	for (enemyBulletIter = enemyBulletVector.begin(); enemyBulletIter != enemyBulletVector.end();)
	{
		if (IntersectRect(&temp, &enemyBulletIter->rect, &PLAYERMANAGER->GetPlayerHitRect()))
		{
			// 오브젝트 풀로 총알을 돌려주는 함수
			OBJECTPOOL->SetBulletVector(enemyBulletVector.front());
			enemyBulletIter = enemyBulletVector.erase(enemyBulletIter);
		}
		else
		{
			++enemyBulletIter;
		}
	}
}

void CollisionManager::PlayerToMinionCollision()
{
	RECT temp;

	// MinionAttackFly 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionBlackFly 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionMaw 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionTumor 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionClot 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionClotty 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionGaper 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionHorf 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionMulligan 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionPacer 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
		{
			// temp의 Width와 Height 선언
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// 왼쪽 충돌시 오른쪽으로 밀어줌
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// 오른쪽 충돌시 왼쪽으로 밀어줌
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// 위쪽 충돌시 아래쪽으로 밀어줌
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// 아래쪽 충돌시 위쪽으로 밀어줌
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}
}

void CollisionManager::SameVectorMinionCollision()
{
	RECT temp;

	// MinionAttackFly 충돌
	if (ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionBlackFly 충돌
	if (ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionMaw 충돌
	if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionTumor 충돌
	if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionClot 충돌
	if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionClotty 충돌
	if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionGaper 충돌
	if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionHorf 충돌
	if (ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionMulligan 충돌
	if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionPacer 충돌
	if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp의 Width와 Height 선언
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// 왼쪽 충돌시 오른쪽으로 밀어줌
						if (temp.left == ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionPacer()->SetEnemyRectX(i, tempW);
						}
						// 오른쪽 충돌시 왼쪽으로 밀어줌
						else if (temp.right == ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionPacer()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// 위쪽 충돌시 아래쪽으로 밀어줌
						if (temp.top == ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionPacer()->SetEnemyRectY(i, tempH);
						}
						// 아래쪽 충돌시 위쪽으로 밀어줌
						else if (temp.bottom == ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionPacer()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}
}

void CollisionManager::MinionToMinionCollision()
{	
	RECT temp;

	// MinionHorf을 기준으로 다른 미니언 충돌
	if (ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size() > 0)
	{
		//MinionHorf To MinionAttackFly 충돌
		if (ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionBlackFly 충돌
		if (ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionMaw 충돌
		if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionTumor 충돌
		if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionClot 충돌
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionClotty 충돌
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionGaper 충돌
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionMulligan 충돌
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionPacer 충돌
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}
	}

	// MinionAttackFly을 기준으로 다른 미니언 충돌
	if (ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size() > 0)
	{
		//MinionAttackFly To MinionBlackFly 충돌
		if (ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionMaw 충돌
		if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionTumor 충돌
		if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionClot 충돌
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionClotty 충돌
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionGaper 충돌
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionMulligan 충돌
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionPacer 충돌
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}
	}

	// MinionBlackFly을 기준으로 다른 미니언 충돌
	if (ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size() > 0)
	{
		//MinionBlackFly To MinionMaw 충돌
		if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionTumor 충돌
		if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionClot 충돌
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionClotty 충돌
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionGaper 충돌
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionMulligan 충돌
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionPacer 충돌
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}
	}

	// MinionMaw을 기준으로 다른 미니언 충돌
	if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
	{
		//MinionMaw To MinionTumor 충돌
		if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionClot 충돌
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionClotty 충돌
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionGaper 충돌
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionMulligan 충돌
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionPacer 충돌
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}
	}

	// MinionTumor을 기준으로 다른 미니언 충돌
	if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
	{
		//MinionTumor To MinionClot 충돌
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionTumor To MinionClotty 충돌
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionTumor To MinionGaper 충돌
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionTumor To MinionMulligan 충돌
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionTumor To MinionPacer 충돌
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}
	}

	// MinionClot을 기준으로 다른 미니언 충돌
	if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
	{
		//MinionClot To MinionClotty 충돌
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClot To MinionGaper 충돌
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClot To MinionMulligan 충돌
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClot To MinionPacer 충돌
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}
	}

	// MinionClotty을 기준으로 다른 미니언 충돌
	if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
	{
		//MinionClotty To MinionGaper 충돌
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClotty To MinionMulligan 충돌
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClotty To MinionPacer 충돌
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

	}

	// MinionGaper을 기준으로 다른 미니언 충돌
	if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
	{
		//MinionGaper To MinionMulligan 충돌
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionGaper To MinionPacer 충돌
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}
	}

	// MinionMulligan을 기준으로 다른 미니언 충돌
	if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
	{
		//MinionMulligan To MinionPacer 충돌
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp의 Width와 Height 선언
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// 왼쪽 충돌시 오른쪽으로 밀어줌
							if (temp.left == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectX(i, tempW);
							}
							// 오른쪽 충돌시 왼쪽으로 밀어줌
							else if (temp.right == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// 위쪽 충돌시 아래쪽으로 밀어줌
							if (temp.top == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectY(i, tempH);
							}
							// 아래쪽 충돌시 위쪽으로 밀어줌
							else if (temp.bottom == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}
	}
}
