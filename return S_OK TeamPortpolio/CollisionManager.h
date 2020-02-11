#pragma once
#include"singletonBase.h"

class CollisionManager : public singletonBase<CollisionManager>
{
private:

public:
	CollisionManager();
	~CollisionManager();

	// 충돌 업데이트
	void UpdateCollision();

	// 플레이어 총알 충돌
	void PlayerBulletCollision(vector<BulletInfo>& playerBulletVector, vector<BulletInfo>::iterator& playerBulletIter);
	
	// 에너미 총알 충돌
	void EnemyBulletCollision(vector<BulletInfo>& enemyBulletVector, vector<BulletInfo>::iterator& enemyBulletIter);
	
	// 플레이어 -> 미니언 렉트 충돌
	void PlayerToMinionCollision();

	// 같은 벡터의 미니언 충돌
	void SameVectorMinionCollision();

	// 다른 벡터의 미니언 충돌
	void MinionToMinionCollision();
};
