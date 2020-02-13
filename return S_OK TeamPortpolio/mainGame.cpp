#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	gameNode::init(true);

	// 메뉴
	SCENEMANAGER->addScene("MainMenu", new MainMenu);

	// 실제 게임 Scene
	SCENEMANAGER->addScene("GameScene", new GameScene);
	
	// 맵툴용 이미지들
	IMAGEMANAGER->addFrameImage("blocks", "images/maptool/blocks.bmp",
		0, 0, 52 * 8, 52 * 9, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapTile", "images/maptool/SampleMap.bmp",
		0, 0, 52 * 17 * 4, 52 * 11 * 4, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("door", "images/maptool/doorSprite.bmp",
		0, 0, 52 * 2.5 * 8, 52 * 2 * 10, 8, 10, true, RGB(255, 0, 255));

	SubMap* sub = new SubMap;
	SCENEMANAGER->addScene("SubMap", sub);

	MapToolScene* map = new MapToolScene;
	SCENEMANAGER->addScene("MapTool", map);
	SUBWIN->SetIsoMap(map);

#ifdef SUBWINOPEN
	SUBWIN->init();
#endif // SUBWINOPEN

#ifdef SUBWINOPEN
	SUBWIN->SetScene(sub);
#endif // SUBWINOPEN


	// 게임씬에서 필요한 매니저들 초기화.
	OBJECTPOOL->Init();
	BULLETMANAGER->Init();
	ITEMMANAGER->Init();

	SCENEMANAGER->changeScene("MainMenu");

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
}

void mainGame::update()
{
	gameNode::update();

	SCENEMANAGER->update();

#ifdef SUBWINOPEN

	SUBWIN->update();
#endif // SUBWINOPEN

}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================

	SCENEMANAGER->render();
#ifdef SUBWINOPEN
	SUBWIN->render();
#endif // SUBWINOPEN
	TIMEMANAGER->render(getMemDC());

	//===================================================
	//백버퍼의 내용을 HDC에 그린다.(건드리지말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}