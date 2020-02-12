#pragma once
#include "EnemyBase.h"

class Monstro : public EnemyBase
{
private:
	vector<EnemyInfo> vMonstro;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

	int teleportCount;	// 텔레포트 카운트
	int shotCount;		// 공격 카운트
	int jumpCount;		// 점프 카운트
	float rndX;			// 텔레포트 될 랜덤 x좌표
	float rndY;			// 텔레포트 될 랜덤 y좌표
	float jumpPower;	// 점프 파워
	float gravity;		// 중력값

	bool teleport;		// 텔레포트
	bool jump;			// 점프할지 안 할지 체크
	bool snowPattern;	// 눈꽃 패턴
	bool teleportImage; // 텔레포트 표시할 이미지

public:
	Monstro();
	~Monstro();

	HRESULT Init(POINT position);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void EnemySnowShot();	// 눈꽃 공격
	void EnemyAllShot();	// 전방위 공격

	// 에너미 벡터를 반환하는 함수
	vector<EnemyInfo> GetMinionVector() { return vMonstro; }

	// 에너미 벡터를 지우는 함수
	void DeleteEnemy(int num);

	// 충돌시 위치 변경 시켜주는 함수
	void SetEnemyRectX(int enemyNum, int move);
	void SetEnemyRectY(int enemyNum, int move);

	// 에너미 Hp를 세팅해주는 함수
	int GetEnemyHp(int enemyNum) { return vMonstro[enemyNum].enemyHp; }
	void SetEnemyHp(int enemyNum, int hp) { vMonstro[enemyNum].enemyHp = hp; }

};
