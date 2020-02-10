#include "stdafx.h"
#include "MinionHorf.h"

MinionHorf::MinionHorf()
{
}

MinionHorf::~MinionHorf()
{
}

HRESULT MinionHorf::Init(POINT position, int EnemyNumber)
{
	//����ü ���� ����
	EnemyInfo MinionHorf;
	MinionHorf.enemyNumber = EnemyNumber;
	MinionHorf.enemyRect = RectMakeCenter(position.x, position.y, 30, 30);
	MinionHorf.enemyHp = 10;
	MinionHorf.enemyShotSpeed = 5.0f;
	MinionHorf.enemyShotRange = 500.0f;
	MinionHorf.enemyShotDelay = 50;
	vMinionHorf.push_back(MinionHorf);

	enemyAreaCheck = false;
	enemyCollision = false;

	return S_OK;
}

void MinionHorf::Release()
{
}

void MinionHorf::Update()
{
	EnemyAi();
}

void MinionHorf::Render(HDC hdc)
{
	for (i = 0; i < vMinionHorf.size(); i++)
	{
		//Rectangle(hdc, vMinionHorf[i].enemyFireRange.left, vMinionHorf[i].enemyFireRange.top, vMinionHorf[i].enemyFireRange.right, vMinionHorf[i].enemyFireRange.bottom);
		Rectangle(hdc, vMinionHorf[i].enemyRect.left, vMinionHorf[i].enemyRect.top, vMinionHorf[i].enemyRect.right, vMinionHorf[i].enemyRect.bottom);
	}

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}

void MinionHorf::EnemyAi()
{
	for (i = 0; i < vMinionHorf.size(); i++)
	{
		RECT temp;

		// �� x��, y�� ��ǥ
		vMinionHorf[i].enemyX = vMinionHorf[i].enemyRect.left + (vMinionHorf[i].enemyRect.right - vMinionHorf[i].enemyRect.left) / 2;
		vMinionHorf[i].enemyY = vMinionHorf[i].enemyRect.top + (vMinionHorf[i].enemyRect.bottom - vMinionHorf[i].enemyRect.top) / 2;

		// �÷��̾�� ���� ������ �浹��
		if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vMinionHorf[i].enemyFireRange))
		{
			EnemyShot();
		}

		// ���� ������ �׻� ���� ��ǥ�� �Ѿƴٴ�
		vMinionHorf[i].enemyFireRange = RectMakeCenter(vMinionHorf[i].enemyX, vMinionHorf[i].enemyY, 400, 400);
	}

	// ���� ��� �ҷ��� ������
	BULLETMANAGER->EnemyMoveBullet(vEnemyBullet, viEnemyBullet);

	// ���� ��� �ҷ� �浹
	COLLISIONMANAGER->EnemyBulletCollision(vEnemyBullet, viEnemyBullet);
}

void MinionHorf::EnemyShot()
{
	switch (vMinionHorf[i].enemyNumber)
	{
	case 0:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionHorf[i].enemyX, vMinionHorf[i].enemyY,
			getAngle(vMinionHorf[i].enemyX, vMinionHorf[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionHorf[i].enemyShotSpeed, vMinionHorf[i].enemyShotRange, firstEnemyBulletCount, vMinionHorf[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetFirstEnemyBulletCount();
		break;
	case 1:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionHorf[i].enemyX, vMinionHorf[i].enemyY,
			getAngle(vMinionHorf[i].enemyX, vMinionHorf[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionHorf[i].enemyShotSpeed, vMinionHorf[i].enemyShotRange, secondEnemyBulletCount, vMinionHorf[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetSecondEnemyBulletCount();
		break;
	case 2:
		BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, vMinionHorf[i].enemyX, vMinionHorf[i].enemyY,
			getAngle(vMinionHorf[i].enemyX, vMinionHorf[i].enemyY,
				PLAYERMANAGER->GetPlayerHitRectX(), PLAYERMANAGER->GetPlayerHitRectY()),
			vMinionHorf[i].enemyShotSpeed, vMinionHorf[i].enemyShotRange, thirdEnemyBulletCount, vMinionHorf[i].enemyShotDelay);

		// ���� �ҷ� ī��Ʈ�� �� ���� �÷���
		SetThirdEnemyBulletCount();
		break;
	}
}

void MinionHorf::DeleteEnemy(int num)
{
	vMinionHorf.erase(vMinionHorf.begin() + num);
}
