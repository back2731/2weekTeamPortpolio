#pragma once
<<<<<<< HEAD
//SHOP �ʱ���ǥ
#define INIT_X -1768
#define INIT_Y -1716
=======
//class Player;
>>>>>>> dev
class Shop 
{
private:

<<<<<<< HEAD
	vector <ItemInfo> vActiveItem;				// ��Ƽ�� ������ ����
	vector <ItemInfo>::iterator viActiveItem;	// ��Ƽ�� ������ ����
	vector <ItemInfo> vPassiveItem;				// �нú� ������ ����
	vector <ItemInfo>::iterator viPassiveItem;	// �нú� ������ ����
	vector <ItemInfo> vTrinkets;				// ��ű� ������ ����
	vector <ItemInfo>::iterator viTrinkets;		// ��ű� ������ ����

	vector <ItemInfo> vHeart;					// ü�� ������ ����
	vector <ItemInfo>::iterator viHeart;		// ü�� ������ ����

	vector <ItemInfo> vGold;					// ��� ������ ����
	vector <ItemInfo>::iterator viGold;			// ��� ������ ����
	vector <ItemInfo> vBomb;					// ��ź ������ ����
	vector <ItemInfo>::iterator viBomb;			// ��ź ������ ����
	vector <ItemInfo> vKey;						// ���� ������ ����
	vector <ItemInfo>::iterator viKey;			// ���� ������ ����

	vector <ItemInfo> vCard;					// ī�� ������ ����
	vector <ItemInfo>::iterator viCard;			// ī�� ������ ����
	vector <ItemInfo> vPill;					// �˾� ������ ����
	vector <ItemInfo>::iterator viPill;			// �˾� ������ ����
=======
	vector <ItemInfo> vShopActiveItem;				// ��Ƽ�� ������ ����
	vector <ItemInfo>::iterator viShopActiveItem;	// ��Ƽ�� ������ ����
	vector <ItemInfo> vShopPassiveItem;				// �нú� ������ ����
	vector <ItemInfo>::iterator viShopPassiveItem;	// �нú� ������ ����
	vector <ItemInfo> vShopTrinkets;				// ��ű� ������ ����
	vector <ItemInfo>::iterator viShopTrinkets;		// ��ű� ������ ����

	vector <ItemInfo> vShopHeart;					// ü�� ������ ����
	vector <ItemInfo>::iterator viShopHeart;		// ü�� ������ ����

	vector <ItemInfo> vShopGold;					// ��� ������ ����
	vector <ItemInfo>::iterator viShopGold;			// ��� ������ ����
	vector <ItemInfo> vShopBomb;					// ��ź ������ ����
	vector <ItemInfo>::iterator viShopBomb;			// ��ź ������ ����
	vector <ItemInfo> vShopKey;						// ���� ������ ����
	vector <ItemInfo>::iterator viShopKey;			// ���� ������ ����

	vector <ItemInfo> vShopCard;					// ī�� ������ ����
	vector <ItemInfo>::iterator viShopCard;			// ī�� ������ ����
	vector <ItemInfo> vShopPill;					// �˾� ������ ����
	vector <ItemInfo>::iterator viShopPill;			// �˾� ������ ����

	vector <ItemInfo> vShopAllItem;					// ��� ������ ����
	vector <ItemInfo>::iterator viShopAllItem;		// ��� ������ ����

	ItemInfo AllItem[10];							// ��� ������ �迭
	ItemInfo Temp[1];								// ���ÿ� �迭

	int sour, dest;

	RECT rc[10];
>>>>>>> dev

public:
	Shop();
	~Shop();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	RECT GetShopItemRect(int x) { return rc[x]; }

	vector<ItemInfo> GetShopActiveItemInfo() { return vShopActiveItem; }
	vector<ItemInfo> GetShopPassiveItemInfo() { return vShopPassiveItem; }
	vector<ItemInfo> GetShopTrinketsInfo() { return vShopTrinkets; }
	vector<ItemInfo> GetShopHeartInfo() { return vShopHeart; }
	vector<ItemInfo> GetShopBombInfo() { return vShopBomb; }
	vector<ItemInfo> GetShopKeyInfo() { return vShopKey; }
	vector<ItemInfo> GetShopCardInfo() { return vShopCard; }
	vector<ItemInfo> GetShopPillInfo() { return vShopPill; }
	vector<ItemInfo> GetShopGoldInfo() { return vShopGold; }

};

