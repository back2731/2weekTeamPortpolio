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
	// 게임씬에서 필요한 매니저들 초기화.
	OBJECTPOOL->Init();
	BULLETMANAGER->Init();
	ITEMMANAGER->Init();

	// 인클루드한 것들 초기화
	m_shop = new Shop;
	m_shop->Init();

	// 플레이어, 에네미 메니저 초기화.
	PLAYERMANAGER->Init();
	ENEMYMANAGER->Init();

	return S_OK;
}

void GameScene::release()
{
	SAFE_DELETE(m_shop);
}

void GameScene::update()
{
	PLAYERMANAGER->Update();
	ENEMYMANAGER->Update();
}

void GameScene::render()
{
	ENEMYMANAGER->Render(getMemDC());
	PLAYERMANAGER->Render(getMemDC());
}
