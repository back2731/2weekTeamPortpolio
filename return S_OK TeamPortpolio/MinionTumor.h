#pragma once
#include "EnemyBase.h"

class MinionTumor : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionTumor;
	vector<EnemyInfo>::iterator viMinionTumor;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

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

	vector<EnemyInfo>& GetEnemyVector() { return vMinionTumor; }
	vector<EnemyInfo>::iterator& GetEnemyIter() { return viMinionTumor; }
};