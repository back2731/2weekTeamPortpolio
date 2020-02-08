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

	RECT obstacle;		// ��ֹ� ����
	RECT enemyRect;		// �� ����
	RECT fireRange;		// ���� ���� ���� ����
	RECT temp;			// �浹�� ����
	float speed;		// ���� �̵��ӵ�
	float enemyX;		// ���� x��ǥ
	float enemyY;		// ���� y��ǥ

	float obstacleX;	// ��ֹ� x��ǥ
	float obstacleY;	// ��ֹ� y��ǥ

public:
	TestMinion();
	~TestMinion();

	HRESULT Init(POINT position);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyShot();	// ���� �߻��ϴ� �Ѿ� �Լ�
	void EnemyAiTime();	// �� ������ ���ϴ� �ð� �Լ�

	RECT GetRect() { return enemyRect; }
	float GetRectX() { return (enemyRect.left + (enemyRect.right - enemyRect.left) / 2); }
	float GetRectY() { return (enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2); }
};