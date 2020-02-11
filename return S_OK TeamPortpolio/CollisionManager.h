#pragma once
#include"singletonBase.h"

class CollisionManager : public singletonBase<CollisionManager>
{
private:

public:
	CollisionManager();
	~CollisionManager();

	void PlayerBulletCollision(vector<BulletInfo>& playerBulletVector, vector<BulletInfo>::iterator& playerBulletIter);
	void EnemyBulletCollision(vector<BulletInfo>& enemyBulletVector, vector<BulletInfo>::iterator& enemyBulletIter);
};