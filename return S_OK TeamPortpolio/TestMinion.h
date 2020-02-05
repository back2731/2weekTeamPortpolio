#pragma once
class TestMinion
{
private:

	RECT enemy;

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

	RECT GetRect() { return enemy; }
	float GetRectX() { return (enemy.left + (enemy.right - enemy.left) / 2); }
	float GetRectY() { return (enemy.top + (enemy.bottom - enemy.top) / 2); }

};

