#pragma once
//SHOP �ʱ���ǥ
#define INIT_X -1768
#define INIT_Y -1716
class Shop 
{
private:

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

public:
	Shop();
	~Shop();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

