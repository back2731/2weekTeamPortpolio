#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	// ���Ӿ����� �ʿ��� �Ŵ����� �ʱ�ȭ.
	OBJECTPOOL->Init();
	BULLETMANAGER->Init();

	PLAYERMANAGER->Init();
	ENEMYMANAGER->Init();

	return S_OK;
}

void GameScene::release()
{
}

void GameScene::update()
{
	PLAYERMANAGER->Update();
	ENEMYMANAGER->Update();

}

void GameScene::render()
{
	PLAYERMANAGER->Render(getMemDC());
	ENEMYMANAGER->Render(getMemDC());
}
