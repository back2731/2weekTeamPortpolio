#pragma once
#include "EnemyBase.h"

class MinionPacer : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionPacer;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

public:
	MinionPacer();
	~MinionPacer();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();

	// 에너미 벡터를 반환하는 함수
	vector<EnemyInfo> GetMinionVector() { return vMinionPacer; }

	// 에너미 벡터를 지우는 함수
	void DeleteEnemy(int num);
};