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

	// ���ʹ� ���͸� ��ȯ�ϴ� �Լ�
	vector<EnemyInfo> GetMinionVector() { return vMinionMulligan; }

	// ���ʹ� ���͸� ����� �Լ�
	void DeleteEnemy(int num);
};

