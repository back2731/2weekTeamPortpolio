#pragma once
#include "EnemyBase.h"

class MinionClotty : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionClotty;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

	bool check;

public:
	MinionClotty();
	~MinionClotty();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void EnemyShot();
};