#include "stdafx.h"
#include "Interface.h"

Interface::Interface()
{
}

Interface::~Interface()
{
}

HRESULT Interface::init()
{

	IMAGEMANAGER->addImage("MainMenu", "images/MainMenu.bmp", WINSIZEX / 2, WINSIZEY / 2, 480, 270, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MainMenuArrow", "images/MainMenuArrow.bmp", WINSIZEY / 2, WINSIZEY /2, 12, 15, true, RGB(255, 0, 255));
	
	NewRunRect = RectMakeCenter(WINSIZEX/2, WINSIZEY, 115, 37);
	MapToolRect = RectMakeCenter(WINSIZEX/2, WINSIZEY/2, 115, 37);
	OptionRect = RectMakeCenter(WINSIZEX/2, WINSIZEY/3, 115, 37);
	
	
	return S_OK;
}

void Interface::release()
{
}

void Interface::update()
{
	if (NewRunRect, PtInRect)
	{
		if (WM_MBUTTONDOWN)
		{
			SCENEMANAGER->changeScene("GameScene");
		}
	}
}

void Interface::render(HDC hdc)
{
	IMAGEMANAGER->render("MainMenu", hdc);
	IMAGEMANAGER->render("MainMenuArrow", hdc);
}

