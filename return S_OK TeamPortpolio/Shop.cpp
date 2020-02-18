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

	//   vShopAllItem = ITEMMANAGER->GetAllItemInfo();


	for (int i = 0; i < 3; i++)
	{
		vShopAllItem.push_back(ITEMMANAGER->GetAllItemInfo(i));
	}

	for (int i = 0; i < 3; i++)
	{
		itemRect[i] = { 316 + i * 100, 380, 368 + i * 100, 432 };
		vShopAllItem[i].itemRect = itemRect[i];
	}

	return S_OK;
}

void Shop::Release()
{
}

void Shop::Update()
{
	if (!ITEMMANAGER->GetShop())
	{
		for (int i = 0; i < vShopAllItem.size(); i++)
		{
			if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &vShopAllItem[i].itemRect))
			{
				if (PLAYERMANAGER->GetPlayerGold() >= vShopAllItem[i].price)
				{
					PLAYERMANAGER->SetPlayerAllItem(vShopAllItem[i]);
					PLAYERMANAGER->SetPlayerOffensePower(vShopAllItem[i].addPower);
					PLAYERMANAGER->SetPlayerShotSpeed(vShopAllItem[i].addShotSpeed);
					PLAYERMANAGER->SetPlayerShotRange(vShopAllItem[i].addShotRange);
					PLAYERMANAGER->SetPlayerSpeed(vShopAllItem[i].addSpeed);
					PLAYERMANAGER->SetPlayerMaxHp(vShopAllItem[i].addMaxHeart);
					PLAYERMANAGER->SetPlayerHp(vShopAllItem[i].addHeart);
					PLAYERMANAGER->SetPlayerGold(-vShopAllItem[i].price);
					PLAYERMANAGER->SetPlayerGold(vShopAllItem[i].addGold);
					PLAYERMANAGER->SetPlayerBomb(vShopAllItem[i].addBomb);
					PLAYERMANAGER->SetPlayerKey(vShopAllItem[i].addKey);
					vShopAllItem.erase(vShopAllItem.begin() + i);
					break;
				}
				break;
			}
		}
	}
}

void Shop::Render(HDC hdc)
{
	if (!ITEMMANAGER->GetShop())
	{
		for (int i = 0; i < vShopAllItem.size(); i++)
		{
			//IMAGEMANAGER->render(ITEMMANAGER->GetAllItemInfo(i).itemName, hdc, itemRect[i].left, itemRect[i].top);
			vShopAllItem[i].itemImage->render(hdc, vShopAllItem[i].itemRect.left, vShopAllItem[i].itemRect.top);
			//IMAGEMANAGER->render(vShopAllItem[i].itemName, hdc, itemRect[i].left, itemRect[i].top);

			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				Rectangle(hdc, itemRect[i].left, itemRect[i].top, itemRect[i].right, itemRect[i].bottom);
			}
		}
	}
}