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
}

void CollisionManager::PlayerBulletCollision(vector<BulletInfo>& playerBulletVector, vector<BulletInfo>::iterator& playerBulletIter)
{
	RECT temp;

	if (!playerBulletVector.empty())
	{
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
<<<<<<< HEAD
}

void CollisionManager::PlayerToMinionCollision()
{		
	RECT temp;

	// MinionAttackFly 충돌
	for (int j = 0; j < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyRect))
		{
			if (PLAYERMANAGER->GetPlayerHitRectX() > ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyX &&
				PLAYERMANAGER->GetPlayerHitRectY() > ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyY)
			{
				PLAYERMANAGER->SetPlayerRectX(50);
			}
		
		}
	}

}

=======
}
>>>>>>> dev
