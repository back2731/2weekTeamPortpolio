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
		// Monstro �浹
		for (int j = 0; j < ENEMYMANAGER->GetMonstro()->GetMinionVector().size(); j++)
		{
			for (playerBulletIter = playerBulletVector.begin(); playerBulletIter != playerBulletVector.end(); )
			{
				if (IntersectRect(&temp, &playerBulletIter->rect, &ENEMYMANAGER->GetMonstro()->GetMinionVector()[j].enemyRect))
				{
					// ������Ʈ Ǯ�� �Ѿ��� �����ִ� �Լ�
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);

					// �ǰ��� �� ���� ���͸� ����� �Լ�
					ENEMYMANAGER->GetMonstro()->DeleteEnemy(j);

					// j��° �̴Ͼ��� �ǰ� �� j�� 0���� �ʱ�ȭ
					j = 0;

					// ���Ͱ��� ��������� for���� ����������.
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
}

void CollisionManager::PlayerToMinionCollision()
{
	RECT temp;

	// MinionAttackFly �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionBlackFly �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionMaw �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionTumor �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionClot �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionClotty �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionGaper �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionHorf �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionMulligan �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
				else if (temp.bottom == PLAYERMANAGER->GetPlayerHitRect().bottom)
				{
					PLAYERMANAGER->SetPlayerRectY(-tempH);
				}
			}
		}
	}

	// MinionPacer �浹
	for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
	{
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
		{
			// temp�� Width�� Height ����
			int tempW = temp.right - temp.left;
			int tempH = temp.bottom - temp.top;

			if (tempH > tempW)
			{
				// ���� �浹�� ���������� �о���
				if (temp.left == PLAYERMANAGER->GetPlayerHitRect().left)
				{
					PLAYERMANAGER->SetPlayerRectX(tempW);
				}
				// ������ �浹�� �������� �о���
				else if (temp.right == PLAYERMANAGER->GetPlayerHitRect().right)
				{
					PLAYERMANAGER->SetPlayerRectX(-tempW);
				}
			}
			else
			{
				// ���� �浹�� �Ʒ������� �о���
				if (temp.top == PLAYERMANAGER->GetPlayerHitRect().top)
				{
					PLAYERMANAGER->SetPlayerRectY(tempH);
				}
				// �Ʒ��� �浹�� �������� �о���
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

	// MinionAttackFly �浹
	if (ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionBlackFly �浹
	if (ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionMaw �浹
	if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionTumor �浹
	if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionClot �浹
	if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionClotty �浹
	if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionGaper �浹
	if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionHorf �浹
	if (ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionMulligan �浹
	if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
						else if (temp.bottom == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.bottom)
						{
							ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectY(i, -tempH);
						}
					}
				}
			}
		}
	}

	// MinionPacer �浹
	if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
	{
		for (int i = 0; i < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); i++)
		{
			for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
			{
				if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
				{
					if (i == j) continue;

					// temp�� Width�� Height ����
					int tempW = temp.right - temp.left;
					int tempH = temp.bottom - temp.top;

					if (tempH > tempW)
					{
						// ���� �浹�� ���������� �о���
						if (temp.left == ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[i].enemyRect.left)
						{
							ENEMYMANAGER->GetMinionPacer()->SetEnemyRectX(i, tempW);
						}
						// ������ �浹�� �������� �о���
						else if (temp.right == ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[i].enemyRect.right)
						{
							ENEMYMANAGER->GetMinionPacer()->SetEnemyRectX(i, -tempW);
						}
					}
					else
					{
						// ���� �浹�� �Ʒ������� �о���
						if (temp.top == ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[i].enemyRect.top)
						{
							ENEMYMANAGER->GetMinionPacer()->SetEnemyRectY(i, tempH);
						}
						// �Ʒ��� �浹�� �������� �о���
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

	// MinionHorf�� �������� �ٸ� �̴Ͼ� �浹
	if (ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size() > 0)
	{
		//MinionHorf To MinionAttackFly �浹
		if (ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionBlackFly �浹
		if (ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionMaw �浹
		if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionTumor �浹
		if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionClot �浹
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionClotty �浹
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionGaper �浹
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionMulligan �浹
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionHorf To MinionPacer �浹
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionHorf()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionHorf()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionHorf()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
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

	// MinionAttackFly�� �������� �ٸ� �̴Ͼ� �浹
	if (ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size() > 0)
	{
		//MinionAttackFly To MinionBlackFly �浹
		if (ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionMaw �浹
		if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionTumor �浹
		if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionClot �浹
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionClotty �浹
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionGaper �浹
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionMulligan �浹
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionAttackFly To MinionPacer �浹
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionAttackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionAttackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
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

	// MinionBlackFly�� �������� �ٸ� �̴Ͼ� �浹
	if (ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size() > 0)
	{
		//MinionBlackFly To MinionMaw �浹
		if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionTumor �浹
		if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionClot �浹
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionClotty �浹
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionGaper �浹
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionMulligan �浹
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionBlackFly To MinionPacer �浹
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionBlackFly()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionBlackFly()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
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

	// MinionMaw�� �������� �ٸ� �̴Ͼ� �浹
	if (ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size() > 0)
	{
		//MinionMaw To MinionTumor �浹
		if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionClot �浹
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionClotty �浹
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionGaper �浹
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionMulligan �浹
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionMaw To MinionPacer �浹
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMaw()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionMaw()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMaw()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
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

	// MinionTumor�� �������� �ٸ� �̴Ͼ� �浹
	if (ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size() > 0)
	{
		//MinionTumor To MinionClot �浹
		if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionTumor To MinionClotty �浹
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionTumor To MinionGaper �浹
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionTumor To MinionMulligan �浹
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionTumor To MinionPacer �浹
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionTumor()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionTumor()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionTumor()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
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

	// MinionClot�� �������� �ٸ� �̴Ͼ� �浹
	if (ENEMYMANAGER->GetMinionClot()->GetMinionVector().size() > 0)
	{
		//MinionClot To MinionClotty �浹
		if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClot To MinionGaper �浹
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClot To MinionMulligan �浹
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClot To MinionPacer �浹
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClot()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionClot()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClot()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
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

	// MinionClotty�� �������� �ٸ� �̴Ͼ� �浹
	if (ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size() > 0)
	{
		//MinionClotty To MinionGaper �浹
		if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClotty To MinionMulligan �浹
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionClotty To MinionPacer �浹
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionClotty()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionClotty()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionClotty()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
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

	// MinionGaper�� �������� �ٸ� �̴Ͼ� �浹
	if (ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size() > 0)
	{
		//MinionGaper To MinionMulligan �浹
		if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
							else if (temp.bottom == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.bottom)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, -tempH);
							}
						}
					}
				}
			}
		}

		//MinionGaper To MinionPacer �浹
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionGaper()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionGaper()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionGaper()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
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

	// MinionMulligan�� �������� �ٸ� �̴Ͼ� �浹
	if (ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size() > 0)
	{
		//MinionMulligan To MinionPacer �浹
		if (ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size() > 0)
		{
			for (int i = 0; i < ENEMYMANAGER->GetMinionMulligan()->GetMinionVector().size(); i++)
			{
				for (int j = 0; j < ENEMYMANAGER->GetMinionPacer()->GetMinionVector().size(); j++)
				{
					if (IntersectRect(&temp, &ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect, &ENEMYMANAGER->GetMinionPacer()->GetMinionVector()[j].enemyRect))
					{
						// temp�� Width�� Height ����
						int tempW = temp.right - temp.left;
						int tempH = temp.bottom - temp.top;

						if (tempH > tempW)
						{
							// ���� �浹�� ���������� �о���
							if (temp.left == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.left)
							{
								ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectX(i, tempW);
							}
							// ������ �浹�� �������� �о���
							else if (temp.right == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.right)
							{
								ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectX(i, -tempW);
							}
						}
						else
						{
							// ���� �浹�� �Ʒ������� �о���
							if (temp.top == ENEMYMANAGER->GetMinionMulligan()->GetMinionVector()[i].enemyRect.top)
							{
								ENEMYMANAGER->GetMinionMulligan()->SetEnemyRectY(i, tempH);
							}
							// �Ʒ��� �浹�� �������� �о���
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
