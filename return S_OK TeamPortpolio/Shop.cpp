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
}
