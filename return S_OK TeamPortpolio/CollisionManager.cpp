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
		// MinionAttackFly �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); j++)
		{
			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionAttackFly()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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

		// MinionBlackFly �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionBlackFly()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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

		// MinionMaw �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionMaw()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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

		// MinionTumor �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
		{
			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionTumor()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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

		// MinionClot �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionClot()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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

		// MinionClotty �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionClotty()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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

		// MinionGaper �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionGaper()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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

		// MinionHorf �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionHorf()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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

		// MinionMulligan �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionMulligan()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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

		// MinionPacer �浹
		for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
		{

			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMinionPacer()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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
			// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
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

	// MinionAttackFly �浹
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
