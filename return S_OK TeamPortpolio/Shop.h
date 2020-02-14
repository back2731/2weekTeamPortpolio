#pragma once
//SHOP 초기좌표
#define INIT_X -1768
#define INIT_Y -1716
class Shop 
{
private:

	vector <ItemInfo> vActiveItem;				// 액티브 아이템 벡터
	vector <ItemInfo>::iterator viActiveItem;	// 액티브 아이템 벡터
	vector <ItemInfo> vPassiveItem;				// 패시브 아이템 벡터
	vector <ItemInfo>::iterator viPassiveItem;	// 패시브 아이템 벡터
	vector <ItemInfo> vTrinkets;				// 장신구 아이템 벡터
	vector <ItemInfo>::iterator viTrinkets;		// 장신구 아이템 벡터

	vector <ItemInfo> vHeart;					// 체력 아이템 벡터
	vector <ItemInfo>::iterator viHeart;		// 체력 아이템 벡터

	vector <ItemInfo> vGold;					// 골드 아이템 벡터
	vector <ItemInfo>::iterator viGold;			// 골드 아이템 벡터
	vector <ItemInfo> vBomb;					// 폭탄 아이템 벡터
	vector <ItemInfo>::iterator viBomb;			// 폭탄 아이템 벡터
	vector <ItemInfo> vKey;						// 열쇠 아이템 벡터
	vector <ItemInfo>::iterator viKey;			// 열쇠 아이템 벡터

	vector <ItemInfo> vCard;					// 카드 아이템 벡터
	vector <ItemInfo>::iterator viCard;			// 카드 아이템 벡터
	vector <ItemInfo> vPill;					// 알약 아이템 벡터
	vector <ItemInfo>::iterator viPill;			// 알약 아이템 벡터

public:
	Shop();
	~Shop();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

