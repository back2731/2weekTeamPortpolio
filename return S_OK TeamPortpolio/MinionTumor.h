#pragma once
#include "EnemyBase.h"

class MinionTumor : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionTumor;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

	bool check;

public:
	MinionTumor();
	~MinionTumor();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void EnemyShot();
};