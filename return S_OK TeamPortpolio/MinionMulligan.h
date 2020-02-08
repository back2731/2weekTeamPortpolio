#pragma once
#include "EnemyBase.h"

class MinionMulligan : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionMulligan;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

	bool check;

public:
	MinionMulligan();
	~MinionMulligan();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void EnemyErase();
	void EnemyShot();
};

