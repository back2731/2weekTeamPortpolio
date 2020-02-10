#pragma once
#include "EnemyBase.h"

class MinionBlackFly : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionBlackFly;

	bool enemyMove;			// 자동 AI
	bool enemyLeftBoost;	// 서로의 x축이 같은 선상이라면 왼쪽 부스트
	bool enemyRightBoost;	// 서로의 x축이 같은 선상이라면 오른쪽 부스트
	bool enemyUpBoost;		// 서로의 y축이 같은 선상이라면 위쪽 부스트
	bool enemyDownBoost;	// 서로의 y축이 같은 선상이라면 아래쪽 부스트

public:
	MinionBlackFly();
	~MinionBlackFly();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
};