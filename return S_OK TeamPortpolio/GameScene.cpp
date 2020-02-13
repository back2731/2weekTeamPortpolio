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
	//IMAGEMANAGER->addImage("TestMap", "images/TestMap.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	mainMap = new MainMap;
	mainMap->init();

	// ���Ӿ����� �ʿ��� �Ŵ����� �ʱ�ȭ.
	OBJECTPOOL->Init();
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
	SAFE_DELETE(mainMap);
}

void GameScene::update()
{
	mainMap->update();
	PLAYERMANAGER->Update();
	ENEMYMANAGER->Update();
	COLLISIONMANAGER->UpdateCollision();
	ANIMATIONMANAGER->update();
}

void GameScene::render()
{
	mainMap->render();
	IMAGEMANAGER->render("TestMap", getMemDC());
	ENEMYMANAGER->Render(getMemDC());
	PLAYERMANAGER->Render(getMemDC());
	OBJECTPOOL->Render(getMemDC());
}