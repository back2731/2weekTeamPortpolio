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
	IMAGEMANAGER->addImage("TestMap", "images/TestMap.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

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
}

void GameScene::update()
{
	PLAYERMANAGER->Update();
	ENEMYMANAGER->Update();
	ANIMATIONMANAGER->update();
}

void GameScene::render()
{
	IMAGEMANAGER->render("TestMap", getMemDC());
	PLAYERMANAGER->Render(getMemDC());
	ENEMYMANAGER->Render(getMemDC());
	OBJECTPOOL->Render(getMemDC());
}