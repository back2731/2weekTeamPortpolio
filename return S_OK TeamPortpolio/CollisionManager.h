#pragma once
#include"singletonBase.h"
#define KNOCKBACK 3

class CollisionManager : public singletonBase<CollisionManager>
{
private:

public:
	CollisionManager();
	~CollisionManager();

	// �浹 ������Ʈ
	void UpdateCollision();

	// �÷��̾� �Ѿ� �浹
	void PlayerBulletCollision(vector<BulletInfo>& playerBulletVector, vector<BulletInfo>::iterator& playerBulletIter);
	
	// ���ʹ� �Ѿ� �浹
	void EnemyBulletCollision(vector<BulletInfo>& enemyBulletVector, vector<BulletInfo>::iterator& enemyBulletIter);
	
	// �÷��̾� -> ���ʹ� ��Ʈ �浹
	void PlayerToMinionCollision();

	// ���� ������ ���ʹ� �浹
	void SameVectorMinionCollision(vector<EnemyInfo>& enemyVector);

	// �ٸ� ������ ���ʹ� �浹
	void MinionToMinionCollision();

	// �÷��̾� -> ��ֹ� ��Ʈ �浹
	void PlayerToObstacleCollision(RECT obstacleRect);
	
	void EnemyToObstacleCollision(RECT obstacleRect);

	void test(RECT obstacleRect, int _startX, int _startY);
};
