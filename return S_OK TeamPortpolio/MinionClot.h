#pragma once
#include "EnemyBase.h"

class MinionClot : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionClot;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

public:
	MinionClot();
	~MinionClot();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void EnemyShot();	
	
	// 에너미 벡터를 반환하는 함수
	vector<EnemyInfo> GetMinionVector() { return vMinionClot; }

	// 에너미 벡터를 지우는 함수
	void DeleteEnemy(int num);
};