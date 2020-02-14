#pragma once

//ĳ���� ���� enum��
enum pDirection
{
	PLAYER_IDLE,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_UP,
	PLAYER_DOWN
};

//ĳ���� �Ӽ� ����ü
struct PlayerInfo
{
	image*	playerHeadImage;		// �÷��̾� �Ӹ� �̹���
	image*	playerBodyImage;		// �÷��̾� �� �̹���
	RECT	playerHeadRect;			// �÷��̾� �Ӹ� ����
	RECT	playerBodyRect;			// �÷��̾� �� ����
	RECT	playerHitRect;			// �÷��̾� �ǰݿ� ����
	int     playerOffensePower;		// �÷��̾� ���ݷ�
	int     playerShotDelay;		// �����ֱ�
	float   playerShotSpeed;		// ���ݼӵ�
	float   playerShotRange;		// ���ݻ�Ÿ�
	float   playerSpeed;			// �̵��ӵ�
	float   playerSlideSpeed;		// �����̵� �ӵ�
};

class Shop;
class Player
{
private:
	image* shadow;
	animation* aniHead;
	animation* aniBody;

private:
	pDirection direction;
	PlayerInfo player;

	vector<BulletInfo> vPlayerBullet;
	vector<BulletInfo>::iterator viPlayerBullet;
	int playerBulletCount;         // �÷��̾� �ҷ� ī��Ʈ

	// �ִϸ��̼��� ������ ���� �迭
	int arrHeadIdle[1] = { 0 };
	int arrHeadRight[1] = { 2 };
	int arrHeadUp[1] = { 4 };
	int arrHeadLeft[1] = { 7 };
	int arrBodyIdle[1] = { 22 };

private:
	// �÷��̾� ���� ����
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	// �÷��̾� �����̵� ����
	bool slideLeft;
	bool slideRight;
	bool slideUp;
	bool slideDown;
	// �÷��̾� ���� ����
	bool playerLeftShot;
	bool playerRightShot;
	bool playerUpShot;
	bool playerDownShot;

private:
	Shop* m_Shop;
	RECT temp;
	RECT test1{ 10,10,20,20 };
	RECT test2{ 30,10,40,20 };
	RECT test3{ 50,10,60,20 };

	vector <ItemInfo> vPlayerActiveItem;				// ��Ƽ�� ������ ����
	vector <ItemInfo>::iterator viPlayerActiveItem;		// ��Ƽ�� ������ ����
	vector <ItemInfo> vPlayerPassiveItem;				// �нú� ������ ����
	vector <ItemInfo>::iterator viPlayerPassiveItem;	// �нú� ������ ����
	vector <ItemInfo> vPlayerTrinkets;					// ��ű� ������ ����
	vector <ItemInfo>::iterator viPlayerTrinkets;		// ��ű� ������ ����

	vector <ItemInfo> vPlayerHeart;						// ü�� ������ ����
	vector <ItemInfo>::iterator viPlayerHeart;			// ü�� ������ ����

	vector <ItemInfo> vPlayerGold;						// ��� ������ ����
	vector <ItemInfo>::iterator viPlayerGold;			// ��� ������ ����
	vector <ItemInfo> vPlayerBomb;						// ��ź ������ ����
	vector <ItemInfo>::iterator viPlayerBomb;			// ��ź ������ ����
	vector <ItemInfo> vPlayerKey;						// ���� ������ ����
	vector <ItemInfo>::iterator viPlayerKey;			// ���� ������ ����

	vector <ItemInfo> vPlayerCard;						// ī�� ������ ����
	vector <ItemInfo>::iterator viPlayerCard;			// ī�� ������ ����
	vector <ItemInfo> vPlayerPill;						// �˾� ������ ����
	vector <ItemInfo>::iterator viPlayerPill;			// �˾� ������ ����

	vector <ItemInfo> vPlayerAllItem;						// ��� ������ ����
	vector <ItemInfo>::iterator viPlayerAllItem;			// ��� ������ ����

public:
	Player();
	~Player();

	HRESULT Init(string imageName);
	void Release();
	void Update();
	void Render(HDC hdc);

	void PlayerMove();            // �÷��̾� �̵�Ű �Լ�
	void PlayerSilde();           // �÷��̾� �̵��� �����̵� �Լ�
	void PlayerShot();            // �÷��̾� ����Ű �Լ�
	void PlayerShotMove();        // �÷��̾� ���ݽ� ���� �Լ�
	void PlayerAnimation();       // �÷��̾� �ִϸ��̼�

	RECT GetPlayerHeadRect() { return player.playerHeadRect; }
	float GetPlayerHeadRectX() { return (player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2); }
	float GetPlayerHeadRectY() { return (player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2); }

	RECT GetPlayerHitRect() { return player.playerHitRect; }
	float GetPlayerHitRectX() { return (player.playerHitRect.left + (player.playerHitRect.right - player.playerHitRect.left) / 2); }
	float GetPlayerHitRectY() { return (player.playerHitRect.top + (player.playerHitRect.bottom - player.playerHitRect.top) / 2); }

	void SetPlayerRectX(int num);
	void SetPlayerRectY(int num);

	vector<BulletInfo> GetPlayerBulletVector() { return vPlayerBullet; }

	int GetPlayerOffensePower() { return player.playerOffensePower; }
	void SetPlayerOffensePower(int addPower) { player.playerOffensePower = addPower; }
};
