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

	// ���Ӿ����� �ʿ��� �Ŵ����� �ʱ�ȭ.
	BULLETMANAGER->Init();
	ITEMMANAGER->Init();

	// ��Ŭ����� �͵� �ʱ�ȭ
	m_shop = new Shop;
	m_shop->Init();

	// �÷��̾�, ���׹� �޴��� �ʱ�ȭ.
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