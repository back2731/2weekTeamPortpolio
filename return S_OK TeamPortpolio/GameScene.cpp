#include "stdafx.h"
#include "GameScene.h"
#include"MapToolTile.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
<<<<<<< HEAD
	mainMap = new MainMap;
	mainMap->init();
=======
	IMAGEMANAGER->addImage("TestMap", "images/TestMap.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//mainMap = new MainMap;
	//mainMap->init();
>>>>>>> dev

	// 게임씬에서 필요한 매니저들 초기화.
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
	//SAFE_DELETE(mainMap);
}

void GameScene::update()
{
	//mainMap->update();
	m_shop->Update();
	PLAYERMANAGER->Update();
	ENEMYMANAGER->Update();
	COLLISIONMANAGER->UpdateCollision();
	ANIMATIONMANAGER->update();
}

void GameScene::render()
{
<<<<<<< HEAD
	mainMap->render();
=======
	//mainMap->render();
>>>>>>> dev
	m_shop->Render(getMemDC());
	ENEMYMANAGER->Render(getMemDC());
	PLAYERMANAGER->Render(getMemDC());
	OBJECTPOOL->Render(getMemDC());
}