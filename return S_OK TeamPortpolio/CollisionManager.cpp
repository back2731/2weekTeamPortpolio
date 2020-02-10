#include "stdafx.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::PlayerBulletCollision(vector<BulletInfo>& playerBulletVector, vector<BulletInfo>::iterator& playerBulletIter)
{
	
	RECT temp;
	if (playerBulletVector.size() > 0)
	{
		for (playerBulletIter = playerBulletVector.begin(); playerBulletIter < playerBulletVector.end();)
		{
			for (int i = 0; i < ENEMYMANAGER->getMinionTumor()->GetMinionVector().size(); i++)
			{
				if (IntersectRect(&temp, &playerBulletVector[i].rect, &ENEMYMANAGER->getMinionTumor()->GetMinionVector()[i].enemyRect))
				{
					OBJECTPOOL->SetBulletVector(playerBulletVector.front());
					playerBulletIter = playerBulletVector.erase(playerBulletIter);
				}
				else ++playerBulletIter;
			}
		}
	}
}

