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
	RECT	enemyFireRange;		// ���� ���� ���� ����
	int		enemyNumber;		// ���� �ѹ�
	int		enemyShotDelay;		// ���� �ֱ�
	float	enemyHp;			// �� ü��
	float	enemyShotSpeed;		// ���ݼӵ�
	float	enemyShotRange;		// ���� ��Ÿ�
	float	enemySpeed;			// �̵��ӵ�
	float	enemyX;				// �� x��ǥ
	float	enemyY;				// �� y��ǥ
};

class EnemyBase
{
private:

protected:
	EnemyInfo enemy;

	int firstEnemyAiTime;		// ù��° �� AI �ൿ�ð�
	int firstEnemyAiPattern;	// ù��° �� AI �ൿ����
	int firstEnemyBulletCount;	// ù��° �� �ҷ� ���͹� ī��Ʈ
	int secondEnemyAiTime;		// �ι�° �� AI �ൿ�ð�
	int secondEnemyAiPattern;	// �ι�° �� AI �ൿ����
	int secondEnemyBulletCount;	// �ι�° �� �ҷ� ���͹� ī��Ʈ
	int thirdEnemyAiTime;		// ����° �� AI �ൿ�ð�
	int thirdEnemyAiPattern;	// ����° �� AI �ൿ����
	int thirdEnemyBulletCount;	// ����° �� �ҷ� ���͹� ī��Ʈ
	int i;						// for���� ����

	float distance;				// ���� �÷��̾��� �Ÿ�
	float vx, vy;				// ���� �ӵ� ����

	bool enemyAreaCheck;		// ���� ���� ������ �÷��̾��� �浹�� üũ�ϴ� ����
	bool enemyCollision;		// ���� ��ֹ��� �浹�� üũ�ϴ� ����

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

	// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
	int SetFirstEnemyBulletCount() { firstEnemyBulletCount++; return firstEnemyBulletCount; }
	int SetSecondEnemyBulletCount() { secondEnemyBulletCount++; return secondEnemyBulletCount; }
	int SetThirdEnemyBulletCount() { thirdEnemyBulletCount++; return thirdEnemyBulletCount; }
};