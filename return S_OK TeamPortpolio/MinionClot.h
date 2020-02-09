#pragma once
#include "EnemyBase.h"

class MinionClot : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionClot;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

	bool check;

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
};