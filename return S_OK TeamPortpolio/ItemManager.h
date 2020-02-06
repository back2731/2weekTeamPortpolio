#pragma once
#include "singletonBase.h"
// 
enum ItemKind
{
	ITEM_ACTIVE,
	ITEM_PASSIVE,
	ITEM_TRINKETS,
	ITEM_HEART,
	ITEM_GOLD,
	ITEM_BOMB,
	ITEM_KEY,
	ITEM_CARD,
	ITEM_PILL,
	ITEM_END
};
struct ItemInfo
{
	ItemKind	itemKind;				// 아이템 종류
	image*		itemImage;				// 아이템 이미지
	image*		itemInfoImage;			// 아이템 UI이미지
	const char* itemName;				// 아이템 이름
	int			addShotDelay;			// 샷 딜레이 증감
	float		addShotRange;			// 샷 사정거리 증감
	float		addShotSpeed;			// 샷 스피드(공격주기) 증감
	float		addSpeed;				// 플레이어 속도 증감
	int			price;					// 아이템 가격
};

class ItemManager : public singletonBase<ItemManager>
{
private:	
	
	vector <ItemInfo> vActiveItem;		// 액티브 아이템 벡터
	vector <ItemInfo> vPassiveItem;		// 패시브 아이템 벡터
	vector <ItemInfo> vTrinkets;		// 장신구 아이템 벡터

	vector <ItemInfo> vHeart;			// 체력 아이템 벡터

	vector <ItemInfo> vGold;			// 골드 아이템 벡터
	vector <ItemInfo> vBomb;			// 폭탄 아이템 벡터
	vector <ItemInfo> vKey;				// 열쇠 아이템 벡터

	vector <ItemInfo> vCard;			// 카드 아이템 벡터
	vector <ItemInfo> vPill;			// 알약 아이템 벡터

public:
	ItemManager();
	~ItemManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

