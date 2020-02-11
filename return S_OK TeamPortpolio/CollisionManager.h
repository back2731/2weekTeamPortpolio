#pragma once
#include"singletonBase.h"
#define PUSH 1
class CollisionManager : public singletonBase<CollisionManager>
{
private:

public:
	CollisionManager();
	~CollisionManager();

	void UpdateCollision();

	void PlayerBulletCollision(vector<BulletInfo>& playerBulletVector, vector<BulletInfo>::iterator& playerBulletIter);
	void EnemyBulletCollision(vector<BulletInfo>& enemyBulletVector, vector<BulletInfo>::iterator& enemyBulletIter);
	void PlayerToMinionCollision();
};
