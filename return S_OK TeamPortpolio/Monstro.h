#pragma once
#include "EnemyBase.h"

class Monstro : public EnemyBase
{
private:
	vector<EnemyInfo> vMonstro;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

public:
	Monstro();
	~Monstro();

	HRESULT Init(POINT position);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void EnemyShot();

	// 에너미 벡터를 반환하는 함수
	vector<EnemyInfo> GetMinionVector() { return vMonstro; }

	// 에너미 벡터를 지우는 함수
	void DeleteEnemy(int num);
};
