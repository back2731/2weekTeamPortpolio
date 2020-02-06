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
	RECT enemyRect;		//적 상자
	RECT fireRange;		//적의 판정 범위 상자
	RECT temp;			//충돌용 상자
	int time;			//행동시간
	int rnd;			//행동패턴
	float speed;		//적의 이동속도
	float enemyX;		//적의 x좌표
	float enemyY;		//적의 y좌표
	float distance;		//거리
	float vx, vy;		//접근 속도 변수

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