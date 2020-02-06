#pragma once
#include "EnemyBase.h"
class TestMinion : public EnemyBase
{
private:

	RECT enemyRect;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;
	int enemyBulletInterval;

public:
	TestMinion();
	~TestMinion();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	RECT GetRect() { return enemyRect; }
	float GetRectX() { return (enemyRect.left + (enemyRect.right - enemyRect.left) / 2); }
	float GetRectY() { return (enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2); }

};

