#pragma once
#include "EnemyBase.h"

enum EenemyMotion
{
	ENEMY_IDLE,
	ENEMY_LEFT,
	ENEMY_RIGHT,
	ENEMY_UP,
	ENEMY_DOWN
};

class TestMinion : public EnemyBase
{
private:
	EenemyMotion motion;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;
	int enemyBulletInterval;

	RECT obstacle;
	RECT enemyRect;		//�� ����
	RECT fireRange;		//���� ���� ���� ����
	RECT temp;			//�浹�� ����
	int time;			//�ൿ�ð�
	int rnd;			//�ൿ����
	float speed;		//���� �̵��ӵ�
	float enemyX;		//���� x��ǥ
	float enemyY;		//���� y��ǥ
	float distance;		//�Ÿ�
	float vx, vy;		//���� �ӵ� ����

	float obstacleX;
	float obstacleY;

	bool areaCheck;
	bool collision;

public:
	TestMinion();
	~TestMinion();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyShot();
	void EnemyAiTime();

	RECT GetRect() { return enemyRect; }
	float GetRectX() { return (enemyRect.left + (enemyRect.right - enemyRect.left) / 2); }
	float GetRectY() { return (enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2); }
};