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
	mainMap = new MainMap;
	mainMap->init();

	// ���Ӿ����� �ʿ��� �Ŵ����� �ʱ�ȭ.
	BULLETMANAGER->Init();
	ITEMMANAGER->Init();

	// ��Ŭ����� �͵� �ʱ�ȭ
	m_shop = new Shop;
	m_shop->Init();

	// �÷��̾�, ���׹� �޴��� �ʱ�ȭ.
	PLAYERMANAGER->Init();
	ENEMYMANAGER->Init();

	// ����
	//SOUNDMANAGER->addSound("BGM", "sound/Sacrificial.mp3", true, true);

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
	m_shop->Update();

	//SOUNDMANAGER->play("BGM", 1.0f);
	COLLISIONMANAGER->UpdateCollision();
	ANIMATIONMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("MainMenu");
	}
}

void GameScene::render()
{
	mainMap->render();
	//m_shop->Render(getMemDC());
	ENEMYMANAGER->Render(getMemDC());
	PLAYERMANAGER->Render(getMemDC());
	OBJECTPOOL->Render(getMemDC());
}
