#pragma once
#include "singletonBase.h"
#define BULLETMAX 10000

// �Ѿ� ����ü ����
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

	// �Ѿ� ����ü ����, ���ͷ�����
	vector<BulletInfo> vBulletRepository;
	vector<BulletInfo>::iterator viBulletRepository;

	// �׽�Ʈ�� 
	char str[128];

public:
	ObjectPool();
	~ObjectPool();

	void Init();
	void Render(HDC hdc);

	// �Ѿ� ���� ���� �Լ�
	void SetBulletVector(BulletInfo vSpentBullet);

	// �� �� �Ѿ��� �������� �Լ�
	BulletInfo GetBullet();
	vector<BulletInfo>::iterator GetBulletVectorIterator() { return viBulletRepository; }
};

