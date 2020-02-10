#include "stdafx.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::Test(vector<BulletInfo>& unitBulletVector, vector<BulletInfo>::iterator& unitBulletIter)
{

	for (unitBulletIter = unitBulletVector.begin(); unitBulletIter != unitBulletVector.end();)
	{
		RECT temp;
		for (int i = 0; i < m_MinionTumor->GetEnemyVector().size(); i++)
		{
			if (IntersectRect(&temp, &m_MinionTumor->GetEnemyVector()[i].enemyRect, &unitBulletIter->rect))
			{
				OBJECTPOOL->SetBulletVector(unitBulletVector.front());
				unitBulletIter = unitBulletVector.erase(unitBulletIter);
			}
			else ++unitBulletIter;
		}
	}
}

