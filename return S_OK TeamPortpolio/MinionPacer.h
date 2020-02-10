#pragma once
#include "EnemyBase.h"

class MinionPacer : public EnemyBase
{
private:
	vector<EnemyInfo> vMinionPacer;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

public:
	MinionPacer();
	~MinionPacer();

	HRESULT Init(POINT position, int EnemyNumber);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();

	// ���ʹ� ���͸� ��ȯ�ϴ� �Լ�
	vector<EnemyInfo> GetMinionVector() { return vMinionPacer; }

	// ���ʹ� ���͸� ����� �Լ�
	void DeleteEnemy(int num);
};