#pragma once
#include "EnemyBase.h"

class Monstro : public EnemyBase
{
private:
	vector<EnemyInfo> vMonstro;

	vector<BulletInfo> vEnemyBullet;
	vector<BulletInfo>::iterator viEnemyBullet;

	int teleportCount;	// �ڷ���Ʈ ī��Ʈ
	int shotCount;		// ���� ī��Ʈ
	int jumpCount;		// ���� ī��Ʈ
	float rndX;			// �ڷ���Ʈ �� ���� x��ǥ
	float rndY;			// �ڷ���Ʈ �� ���� y��ǥ
	float jumpPower;	// ���� �Ŀ�
	float gravity;		// �߷°�

	bool teleport;		// �ڷ���Ʈ
	bool jump;			// �������� �� ���� üũ
	bool snowPattern;	// ���� ����
	bool teleportImage; // �ڷ���Ʈ ǥ���� �̹���

public:
	Monstro();
	~Monstro();

	HRESULT Init(POINT position);
	void Release();
	void Update();
	void Render(HDC hdc);

	void EnemyAiTime();
	void EnemyAi();
	void EnemySnowShot();	// ���� ����
	void EnemyAllShot();	// ������ ����

	// ���ʹ� ���͸� ��ȯ�ϴ� �Լ�
	vector<EnemyInfo> GetMinionVector() { return vMonstro; }

	// ���ʹ� ���͸� ����� �Լ�
	void DeleteEnemy(int num);

	// �浹�� ��ġ ���� �����ִ� �Լ�
	void SetEnemyRectX(int enemyNum, int move);
	void SetEnemyRectY(int enemyNum, int move);

	// ���ʹ� Hp�� �������ִ� �Լ�
	int GetEnemyHp(int enemyNum) { return vMonstro[enemyNum].enemyHp; }
	void SetEnemyHp(int enemyNum, int hp) { vMonstro[enemyNum].enemyHp = hp; }

};
