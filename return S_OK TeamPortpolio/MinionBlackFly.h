#pragma once
#include "EnemyBase.h"

class MinionBlackFly : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionBlackFly;

	bool enemyMove;			// �ڵ� AI
	bool enemyLeftBoost;	// ������ x���� ���� �����̶�� ���� �ν�Ʈ
	bool enemyRightBoost;	// ������ x���� ���� �����̶�� ������ �ν�Ʈ
	bool enemyUpBoost;		// ������ y���� ���� �����̶�� ���� �ν�Ʈ
	bool enemyDownBoost;	// ������ y���� ���� �����̶�� �Ʒ��� �ν�Ʈ

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