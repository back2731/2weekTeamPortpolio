#pragma once
#include "EnemyBase.h"

class MinionAttackFly : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionAttackFly;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

public:
	MinionAttackFly();
	~MinionAttackFly();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();

	// ���ʹ� ���͸� ��ȯ�ϴ� �Լ�
	vector<EnemyInfo> GetMinionVector() { return vMinionAttackFly; }

	// ���ʹ� ���͸� ����� �Լ�
	void DeleteEnemy(int num);
};