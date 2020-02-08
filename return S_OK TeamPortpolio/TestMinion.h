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

	RECT obstacle;		// 장애물 상자
	RECT enemyRect;		// 적 상자
	RECT fireRange;		// 적의 판정 범위 상자
	RECT temp;			// 충돌용 상자
	float speed;		// 적의 이동속도
	float enemyX;		// 적의 x좌표
	float enemyY;		// 적의 y좌표

	float obstacleX;	// 장애물 x좌표
	float obstacleY;	// 장애물 y좌표

public:
	TestMinion();
	~TestMinion();

	HRESULT Init(POINT position);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyShot();	// 적이 발사하는 총알 함수
	void EnemyAiTime();	// 적 패턴을 정하는 시간 함수

	RECT GetRect() { return enemyRect; }
	float GetRectX() { return (enemyRect.left + (enemyRect.right - enemyRect.left) / 2); }
	float GetRectY() { return (enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2); }
};