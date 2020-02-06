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
	ItemKind	itemKind;				// ������ ����
	image*		itemImage;				// ������ �̹���
	image*		itemInfoImage;			// ������ UI�̹���
	const char* itemName;				// ������ �̸�
	int			addShotDelay;			// �� ������ ����
	float		addShotRange;			// �� �����Ÿ� ����
	float		addShotSpeed;			// �� ���ǵ�(�����ֱ�) ����
	float		addSpeed;				// �÷��̾� �ӵ� ����
	int			price;					// ������ ����
};

class ItemManager : public singletonBase<ItemManager>
{
private:	
	
	vector <ItemInfo> vActiveItem;		// ��Ƽ�� ������ ����
	vector <ItemInfo> vPassiveItem;		// �нú� ������ ����
	vector <ItemInfo> vTrinkets;		// ��ű� ������ ����

	vector <ItemInfo> vHeart;			// ü�� ������ ����

	vector <ItemInfo> vGold;			// ��� ������ ����
	vector <ItemInfo> vBomb;			// ��ź ������ ����
	vector <ItemInfo> vKey;				// ���� ������ ����

	vector <ItemInfo> vCard;			// ī�� ������ ����
	vector <ItemInfo> vPill;			// �˾� ������ ����

public:
	ItemManager();
	~ItemManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

