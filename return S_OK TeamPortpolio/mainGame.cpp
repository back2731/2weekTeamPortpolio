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
	PLAYERMANAGER->Init();
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
}

void mainGame::update()
{
	gameNode::update();
	PLAYERMANAGER->Update();
}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================

	PLAYERMANAGER->Render(getMemDC());
	TIMEMANAGER->render(getMemDC());

	//===================================================
	//백버퍼의 내용을 HDC에 그린다.(건드리지말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}