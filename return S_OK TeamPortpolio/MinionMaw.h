#pragma once
#include "EnemyBase.h"

class MinionMaw : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionMaw;
	vector<EnemyInfo>::iterator viMinionMaw;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

public:
	MinionMaw();
	~MinionMaw();

	HRESULT Init(POINT position);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void EnemyShot();
};