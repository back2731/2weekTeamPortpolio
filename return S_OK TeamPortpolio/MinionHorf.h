#pragma once
#include "EnemyBase.h"

class MinionHorf : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionHorf;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

public:
	MinionHorf();
	~MinionHorf();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAi();
	void EnemyShot();
};