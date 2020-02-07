#pragma once

//캐릭터 속성 구조체
struct EnemyInfo
{
	image*	enemyHeadImage;		// 적 머리 이미지
	image*	enemyBodyImage;		// 적 몸 이미지
	image*	enemyImage;			// 적 전체 이미지
	RECT	enemyHeadRect;		// 적 머리 상자
	RECT	enemyBodyRect;		// 적 몸 상자
	RECT	enemyRect;			// 적 전체 렉트
	RECT	enemyFireRange;		// 적의 판정 범위 상자
	int		enemyShotDelay;		// 공격 주기
	float	enemyHp;			// 적 체력
	float	enemyShotSpeed;		// 공격속도
	float	enemyShotRange;		// 공격 사거리
	float	enemySpeed;			// 이동속도
	float	enemyX;				// 적 x좌표
	float	enemyY;				// 적 y좌표
};

class EnemyBase
{
private:

protected:
	EnemyInfo enemy;

	int enemyAiTime;			// 적 AI 행동시간
	int enemyAiPattern;			// 적 AI 행동패턴
	int enemyBulletCount;		// 적 불렛 인터벌 카운트

	float distance;				// 적과 플레이어의 거리
	float vx, vy;				// 접근 속도 변수

	bool enemyAreaCheck;		// 적의 판정 범위와 플레이어의 충돌을 체크하는 변수
	bool enemyCollision;		// 적과 장애물의 충돌을 체크하는 변수

public:
	EnemyBase();
	~EnemyBase();

	// 생성할 때 포지션으로 자리를 잡아준다. position에 들어갈 변수는 PointMake(x, y)
	virtual HRESULT Init(POINT position);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	// 적 머리 부분 렉트 정보 가져오기
	RECT GetEnemyHeadRect() { return enemy.enemyHeadRect; }
	float GetEnemyHeadRectX() { return (enemy.enemyHeadRect.left + (enemy.enemyHeadRect.right - enemy.enemyHeadRect.left) / 2); }
	float GetEnemyHeadRectY() { return (enemy.enemyHeadRect.top + (enemy.enemyHeadRect.bottom - enemy.enemyHeadRect.top) / 2); }

	// 적 몸체 부분 렉트 정보 가져오기
	RECT GetEnemyBodyRect() { return enemy.enemyBodyRect; }
	float GetEnemyBodyRectX() { return (enemy.enemyBodyRect.left + (enemy.enemyBodyRect.right - enemy.enemyBodyRect.left) / 2); }
	float GetEnemyBodyRectY() { return (enemy.enemyBodyRect.top + (enemy.enemyBodyRect.bottom - enemy.enemyBodyRect.top) / 2); }

	// 통으로 된 적 렉트 정보 가져오기
	RECT GetEnemyRect() { return enemy.enemyRect; }
	float GetEnemyRectX() { return (enemy.enemyRect.left + (enemy.enemyRect.right - enemy.enemyRect.left) / 2); }
	float GetEnemyRectY() { return (enemy.enemyRect.top + (enemy.enemyRect.bottom - enemy.enemyRect.top) / 2); }

	// HP 가져오기, 설정하기
	int GetHp() { return enemy.enemyHp; }
	void SetHp(int num) { enemy.enemyHp = num; }

	// 적의 불렛 카운트를 한 번에 플러스
	int SetEnemyBulletCount() { enemyBulletCount++; return enemyBulletCount; }
};