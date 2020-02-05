#include "stdafx.h"
#include "TestMinion.h"


TestMinion::TestMinion()
{
}


TestMinion::~TestMinion()
{
}

HRESULT TestMinion::Init()
{
	//테스트용 에네미 렉트
	enemy = RectMakeCenter(WINSIZEX / 2 + 300, WINSIZEY / 2, 50, 50);
	enemyBulletInterval = 0;

	return S_OK;
}

void TestMinion::Release()
{
}

void TestMinion::Update()
{
	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, enemy.left + (enemy.right - enemy.left) / 2, enemy.top + (enemy.bottom - enemy.top) / 2,
		getAngle(enemy.left + (enemy.right - enemy.left) / 2, enemy.top + (enemy.bottom - enemy.top) / 2, PLAYERMANAGER->GetRectX(), PLAYERMANAGER->GetRectY()),
		5.0f, 500, enemyBulletInterval++, 30);
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);
}

void TestMinion::Render(HDC hdc)
{
	Rectangle(hdc, enemy.left, enemy.top, enemy.right, enemy.bottom);

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}
