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
	enemyRect = RectMakeCenter(WINSIZEX / 2 + 300, WINSIZEY / 2, 50, 50);
	enemyBulletInterval = 0;

	return S_OK;
}

void TestMinion::Release()
{
}

void TestMinion::Update()
{
	BULLETMANAGER->ShootBullet("enemyBullet", vEnemyBullet, enemyRect.left + (enemyRect.right - enemyRect.left) / 2, enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2,
		getAngle(enemyRect.left + (enemyRect.right - enemyRect.left) / 2, enemyRect.top + (enemyRect.bottom - enemyRect.top) / 2, PLAYERMANAGER->GetRectX(), PLAYERMANAGER->GetRectY()),
		5.0f, 500, enemyBulletInterval++, 50);
	BULLETMANAGER->MoveBullet(vEnemyBullet, viEnemyBullet);
}

void TestMinion::Render(HDC hdc)
{
	Rectangle(hdc, enemyRect.left, enemyRect.top, enemyRect.right, enemyRect.bottom);

	BULLETMANAGER->RenderBullet(hdc, vEnemyBullet, viEnemyBullet);
}
