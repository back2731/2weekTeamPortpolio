#pragma once
#include "EnemyBase.h"

class MinionMulligan : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionMulligan;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

	bool collisionCheck;

public:
	MinionMulligan();
	~MinionMulligan();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void DeleteEnemy();
	void EnemyShot();

	// 에너미 벡터를 반환하는 함수
	vector<EnemyInfo> GetMinionVector() { return vMinionMulligan; }

	// 에너미 벡터를 지우는 함수
	void DeleteEnemy(int num);
};

