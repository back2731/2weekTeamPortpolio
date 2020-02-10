#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

HRESULT MainMenu::init()
{
	IMAGEMANAGER->addImage("MainMenu", "images/MainMenu.bmp", WINSIZEX / 2, WINSIZEY / 2, 960, 540, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MainMenuArrow", "images/MainMenuArrow.bmp", WINSIZEY / 2, WINSIZEY / 2, 24, 30, true, RGB(255, 0, 255));

	newRunRect = RectMake(320, 160, 24, 30);
	mapToolRect = RectMake(340, 270, 24, 30);
	optionRect = RectMake(360, 360, 24, 30);
	cursorRect = RectMake(320, 160, 24, 30);

	return S_OK;
}

void MainMenu::release()
{
}

void MainMenu::update()
{
	CursorMove();
}

void MainMenu::render()
{
	IMAGEMANAGER->render("MainMenu", getMemDC());
	//Rectangle(getMemDC(), newRunRect.left, newRunRect.top, newRunRect.right, newRunRect.bottom);
	//Rectangle(getMemDC(), mapToolRect.left, mapToolRect.top, mapToolRect.right, mapToolRect.bottom);
	//Rectangle(getMemDC(), optionRect.left, optionRect.top, optionRect.right, optionRect.bottom);
	IMAGEMANAGER->render("MainMenuArrow", getMemDC(), cursorRect.left, cursorRect.top);

	sprintf_s((str), "x : %d", m_ptMouse.x);
	TextOut(getMemDC(), 10, 10, str, strlen(str));

	sprintf_s((str), "y : %d", m_ptMouse.y);
	TextOut(getMemDC(), 10, 30, str, strlen(str));
}

void MainMenu::CursorMove()
{
	// 새 게임 선택시 게임 화면으로 전환한다.
	if (IntersectRect(&temp, &newRunRect, &cursorRect))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			cursorRect = RectMake(340, 270, 24, 30);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SCENEMANAGER->changeScene("GameScene");
		}
	}
	// 맵툴 선택시 맵툴 화면으로 전환한다.
	if (IntersectRect(&temp, &mapToolRect, &cursorRect))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			cursorRect = RectMake(320, 160, 24, 30);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			cursorRect = RectMake(360, 360, 24, 30);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SCENEMANAGER->changeScene("GameScene");
		}
	}
	// 옵션 선택시 옵션 화면으로 전환한다.
	if (IntersectRect(&temp, &optionRect, &cursorRect))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			cursorRect = RectMake(340, 270, 24, 30);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SCENEMANAGER->changeScene("GameScene");
		}
	}
}