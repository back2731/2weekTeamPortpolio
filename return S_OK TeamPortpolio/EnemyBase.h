#pragma once

//ĳ���� �Ӽ� ����ü
struct EnemyInfo 
{
	image*	enemyHeadImage;		// �� �Ӹ� �̹���
	image*	enemyBodyImage;		// �� �� �̹���
	image*	enemyImage;			// �� ��ü �̹���
	RECT	enemyHeadRect;		// �� �Ӹ� ����
	RECT	enemyBodyRect;		// �� �� ����
	RECT	enemyRect;			// �� ��ü ��Ʈ
	int		enemyShotDelay;		// �����ֱ�
	float	enemyShotRange;		// ���ݻ�Ÿ�
	float	enemyShotSpeed;		// ���ݼӵ�
	float	enemySpeed;			// �̵��ӵ�
	float	enemyHp;			// �� ü��
};

class EnemyBase
{
private:

protected:

	EnemyInfo enemy;

public:
	EnemyBase();
	~EnemyBase();

	// ������ �� ���������� �ڸ��� ����ش�. position�� �� ������ PointMake(x, y)
	virtual HRESULT Init(POINT position);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);	

	// �� �Ӹ� �κ� ��Ʈ ���� ��������
	RECT GetEnemyHeadRect() { return enemy.enemyHeadRect; }
	float GetEnemyHeadRectX() { return (enemy.enemyHeadRect.left + (enemy.enemyHeadRect.right - enemy.enemyHeadRect.left) / 2); }
	float GetEnemyHeadRectY() { return (enemy.enemyHeadRect.top + (enemy.enemyHeadRect.bottom - enemy.enemyHeadRect.top) / 2); }

	// �� ��ü �κ� ��Ʈ ���� ��������
	RECT GetEnemyBodyRect() { return enemy.enemyBodyRect; }
	float GetEnemyBodyRectX() { return (enemy.enemyBodyRect.left + (enemy.enemyBodyRect.right - enemy.enemyBodyRect.left) / 2); }
	float GetEnemyBodyRectY() { return (enemy.enemyBodyRect.top + (enemy.enemyBodyRect.bottom - enemy.enemyBodyRect.top) / 2); }

	// ������ �� �� ��Ʈ ���� ��������
	RECT GetEnemyRect() { return enemy.enemyRect; }
	float GetEnemyRectX() { return (enemy.enemyRect.left + (enemy.enemyRect.right - enemy.enemyRect.left) / 2); }
	float GetEnemyRectY() { return (enemy.enemyRect.top + (enemy.enemyRect.bottom - enemy.enemyRect.top) / 2); }

	// HP ��������, �����ϱ�
	int GetHp() { return enemy.enemyHp; }
	void SetHp(int num) { enemy.enemyHp = num; }

};

