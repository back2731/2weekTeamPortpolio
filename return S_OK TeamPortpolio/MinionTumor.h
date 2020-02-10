#pragma once
#include "EnemyBase.h"

class MinionTumor : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionTumor;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

	bool enemyMove;			// 자동 AI
	bool enemyLeftBoost;	// 서로의 x축이 같은 선상이라면 왼쪽 부스트
	bool enemyRightBoost;	// 서로의 x축이 같은 선상이라면 오른쪽 부스트
	bool enemyUpBoost;		// 서로의 y축이 같은 선상이라면 위쪽 부스트
	bool enemyDownBoost;	// 서로의 y축이 같은 선상이라면 아래쪽 부스트

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

	// 에너미 벡터를 반환하는 함수
	vector<EnemyInfo> GetMinionVector() { return vMinionTumor; }

	// 에너미 벡터를 지우는 함수
	void DeleteEnemy(int num);
};