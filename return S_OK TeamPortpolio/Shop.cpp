#include "stdafx.h"
#include "Shop.h"
#include<time.h>




Shop::Shop()
{
}


Shop::~Shop()
{
}

HRESULT Shop::Init()
{
<<<<<<< HEAD
	//IMAGEMANAGER->addImage("TestMap", "images/TestMap.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	vActiveItem = ITEMMANAGER->GetActiveItemInfo();
	vPassiveItem = ITEMMANAGER->GetPassiveItemInfo();
	vTrinkets = ITEMMANAGER->GetTrinketsInfo();
=======
	IMAGEMANAGER->addImage("TestMap", "images/item/TestMap.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	vShopActiveItem = ITEMMANAGER->GetActiveItemInfo();
	vShopPassiveItem = ITEMMANAGER->GetPassiveItemInfo();
	vShopTrinkets = ITEMMANAGER->GetTrinketsInfo();

	vShopGold = ITEMMANAGER->GetGoldInfo();
	vShopHeart = ITEMMANAGER->GetHeartInfo();

	vShopBomb = ITEMMANAGER->GetBombInfo();
	vShopKey = ITEMMANAGER->GetKeyInfo();

	vShopCard = ITEMMANAGER->GetCardInfo();
	vShopPill = ITEMMANAGER->GetPillInfo();
>>>>>>> dev

	vShopAllItem = ITEMMANAGER->GetAllItemInfo();

	for (int i = 0; i < 10; i++)
	{
		AllItem[i] = vShopAllItem[i];
	}

	for (int i = 0; i < 100; i++)
	{
		dest = RND->getInt(10);
		sour = RND->getInt(10);

		Temp[0] = AllItem[dest];
		AllItem[dest] = AllItem[sour];
		AllItem[sour] = Temp[0];
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			rc[i * 5 + j] = { 100 + 60 * j, 300 + 60 * i, 150 + 60 * j, 350 + 60 * i };
		}
	}


	return S_OK;
}

void Shop::Release()
{
}

void Shop::Update()
{	
}

void Shop::Render(HDC hdc)
{
<<<<<<< HEAD
	//IMAGEMANAGER->render("TestMap", hdc);
=======
	IMAGEMANAGER->render("TestMap", hdc, 0, 0);

	for (int i = 0; i < 10; i++)
	{
		AllItem[i].itemImage->render(hdc, rc[i].left, rc[i].top);
		//Rectangle(hdc, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom );
	}
>>>>>>> dev
}
