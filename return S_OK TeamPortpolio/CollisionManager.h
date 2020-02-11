#pragma once
#include"singletonBase.h"

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
	
	// �÷��̾� -> �̴Ͼ� ��Ʈ �浹
	void PlayerToMinionCollision();

	// ���� ������ �̴Ͼ� �浹
	void SameVectorMinionCollision();

	// �ٸ� ������ �̴Ͼ� �浹
	void MinionToMinionCollision();
};
