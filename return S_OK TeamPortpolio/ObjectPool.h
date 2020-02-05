#pragma once
#include "singletonBase.h"
#define BULLETMAX 10000

// 총알 구조체 정보
struct BulletInfo
{
	image* bulletImage;
	RECT rect;
	float bulletX, bulletY;
	float unitX, unitY;
	float radius;
	float angle;
	float speed;
	float range;
	bool fire;
	int count;
};

class ObjectPool : public singletonBase<ObjectPool>
{
private:

	// 총알 구조체 벡터, 이터레이터
	vector<BulletInfo> vBulletRepository;
	vector<BulletInfo>::iterator viBulletRepository;

	// 테스트용 
	char str[128];

public:
	ObjectPool();
	~ObjectPool();

	void Init();
	void Render(HDC hdc);

	// 총알 정보 세팅 함수
	void SetBulletVector(BulletInfo vSpentBullet);

	// 다 쓴 총알을 가져오는 함수
	BulletInfo GetBullet();
	vector<BulletInfo>::iterator GetBulletVectorIterator() { return viBulletRepository; }
};

