#pragma once
#include "EnemyBase.h"

class MinionMaw : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionMaw;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

public:
	MinionMaw();
	~MinionMaw();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void EnemyShot();

	// 에너미 벡터를 반환하는 함수
	vector<EnemyInfo> GetMinionVector() { return vMinionMaw; }

	// 에너미 벡터를 지우는 함수
	void DeleteEnemy(int num);
};