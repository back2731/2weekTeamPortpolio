#pragma once

//ĳ���� ���� enum��
enum Direction
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
	image*   playerHeadImage;      // �÷��̾� �Ӹ� �̹���
	image*   playerBodyImage;      // �÷��̾� �� �̹���
	RECT   playerHeadRect;         // �÷��̾� �Ӹ� ����
	RECT   playerBodyRect;         // �÷��̾� �� ����
	RECT   playerHitRect;         // �÷��̾� �ǰݿ� ����
	int      playerOffensePower;      // �÷��̾� ���ݷ�
	int      playerShotDelay;      // �����ֱ�
	float   playerShotSpeed;      // ���ݼӵ�
	float   playerShotRange;      // ���ݻ�Ÿ�
	float   playerSpeed;         // �̵��ӵ�
	float   playerSlideSpeed;      // �����̵� �ӵ�
};

class Player
{
private:
	animation* aniHead;
	animation* aniBody;

private:
	Direction direction;
	PlayerInfo player;

	vector<BulletInfo> vPlayerBullet;
	vector<BulletInfo>::iterator viPlayerBullet;
	int playerBulletCount;         // �÷��̾� �ҷ� ī��Ʈ
	int headNum;
	int bodyNum;

private:
	//�÷��̾� ���� ����
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	//�÷��̾� �����̵� ����
	bool slideLeft;
	bool slideRight;
	bool slideUp;
	bool slideDown;
	//�÷��̾� �밢 �����̵� ����
	bool slideLeftUp;
	bool slideLeftDown;
	bool slideRightUp;
	bool slideRightDown;
	//�÷��̾� ���� ����
	bool playerLeftShot;
	bool playerRightShot;
	bool playerUpShot;
	bool playerDownShot;

public:
	Player();
	~Player();

	HRESULT Init(string imageName);
	void Release();
	void Update();
	void Render(HDC hdc);

	void PlayerMove();            //�÷��̾� �̵�Ű �Լ�
	void PlayerSilde();            //�÷��̾� �̵��� �����̵� �Լ�
	void PlayerShot();            //�÷��̾� ����Ű �Լ�
	void PlayerShotMove();         //�÷��̾� ���ݽ� ���� �Լ�
	void PlayerAnimation();         //�÷��̾� �ִϸ��̼�

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