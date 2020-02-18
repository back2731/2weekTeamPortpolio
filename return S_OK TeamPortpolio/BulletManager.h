#pragma once
#include "singletonBase.h"

class BulletManager : public singletonBase<BulletManager>
{
private:

public:
	BulletManager();
	~BulletManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	// �Ѿ� �̹��� �̸�, �Ѿ��� ��� ����, �÷��̾�&�Ѿ� x, y, ����, �Ѿ� �ӵ�, �Ѿ� �����Ÿ�, ���͹� ������ ����, ���͹��� �󸶳� �ٰ������� ���� ����
	void ShootBullet(string imageName, vector<BulletInfo>& bulletVector, float x, float y, float angle, float speed, float range, int count, int interval);
	// ��ź �̹��� �̸�, ��ź�� ��� ����, �÷��̾�&��ź x, y, ������, �����Ÿ�, �����ð��� ���� ����
	void ShootBomb(string imageName, vector<BombInfo>& bombVector, int x, int y, int damage, int range, int delayTime);

	// �Ѿ��� ���� ���Ϳ� ���ͷ����͸� �־��ش�.
	void MoveBullet(vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator& bulletIter);
	void RenderBullet(HDC hdc, vector<BulletInfo>& bulletVector, vector<BulletInfo>::iterator& bulletIter);
};

