#include "stdafx.h"
#include "Shop.h"


Shop::Shop()
{
}


Shop::~Shop()
{
}

HRESULT Shop::Init()
{
	//IMAGEMANAGER->addImage("TestMap", "images/TestMap.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	vActiveItem = ITEMMANAGER->GetActiveItemInfo();
	vPassiveItem = ITEMMANAGER->GetPassiveItemInfo();
	vTrinkets = ITEMMANAGER->GetTrinketsInfo();

	vHeart = ITEMMANAGER->GetHeartInfo();

	vBomb = ITEMMANAGER->GetBombInfo();
	vKey = ITEMMANAGER->GetKeyInfo();

	vCard = ITEMMANAGER->GetCardInfo();
	vPill = ITEMMANAGER->GetPillInfo();


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
	//IMAGEMANAGER->render("TestMap", hdc);
}
