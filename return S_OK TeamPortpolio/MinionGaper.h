#pragma once
#include "EnemyBase.h"

class MinionGaper : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionGaper;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

public:
	MinionGaper();
	~MinionGaper();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
};