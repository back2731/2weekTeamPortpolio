#pragma once

//캐릭터 방향 enum문
enum pDirection
{
	PLAYER_IDLE,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_UP,
	PLAYER_DOWN
};

//캐릭터 속성 구조체
struct PlayerInfo
{
	image*	playerHeadImage;		// 플레이어 머리 이미지
	image*	playerBodyImage;		// 플레이어 몸 이미지
	RECT	playerHeadRect;			// 플레이어 머리 상자
	RECT	playerBodyRect;			// 플레이어 몸 상자
	RECT	playerHitRect;			// 플레이어 피격용 상자
	int     playerOffensePower;		// 플레이어 공격력
	int     playerShotDelay;		// 공격주기
	float   playerShotSpeed;		// 공격속도
	float   playerShotRange;		// 공격사거리
	float   playerSpeed;			// 이동속도
	float   playerSlideSpeed;		// 슬라이딩 속도
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
	int playerBulletCount;         // 플레이어 불렛 카운트

	// 애니메이션을 돌리기 위한 배열
	int arrHeadIdle[1] = { 0 };
	int arrHeadRight[1] = { 2 };
	int arrHeadUp[1] = { 4 };
	int arrHeadLeft[1] = { 7 };
	int arrBodyIdle[1] = { 22 };

private:
	// 플레이어 무브 변수
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	// 플레이어 슬라이딩 변수
	bool slideLeft;
	bool slideRight;
	bool slideUp;
	bool slideDown;
	// 플레이어 슈팅 변수
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

	vector <ItemInfo> vPlayerActiveItem;				// 액티브 아이템 벡터
	vector <ItemInfo>::iterator viPlayerActiveItem;		// 액티브 아이템 벡터
	vector <ItemInfo> vPlayerPassiveItem;				// 패시브 아이템 벡터
	vector <ItemInfo>::iterator viPlayerPassiveItem;	// 패시브 아이템 벡터
	vector <ItemInfo> vPlayerTrinkets;					// 장신구 아이템 벡터
	vector <ItemInfo>::iterator viPlayerTrinkets;		// 장신구 아이템 벡터

	vector <ItemInfo> vPlayerHeart;						// 체력 아이템 벡터
	vector <ItemInfo>::iterator viPlayerHeart;			// 체력 아이템 벡터

	vector <ItemInfo> vPlayerGold;						// 골드 아이템 벡터
	vector <ItemInfo>::iterator viPlayerGold;			// 골드 아이템 벡터
	vector <ItemInfo> vPlayerBomb;						// 폭탄 아이템 벡터
	vector <ItemInfo>::iterator viPlayerBomb;			// 폭탄 아이템 벡터
	vector <ItemInfo> vPlayerKey;						// 열쇠 아이템 벡터
	vector <ItemInfo>::iterator viPlayerKey;			// 열쇠 아이템 벡터

	vector <ItemInfo> vPlayerCard;						// 카드 아이템 벡터
	vector <ItemInfo>::iterator viPlayerCard;			// 카드 아이템 벡터
	vector <ItemInfo> vPlayerPill;						// 알약 아이템 벡터
	vector <ItemInfo>::iterator viPlayerPill;			// 알약 아이템 벡터

	vector <ItemInfo> vPlayerAllItem;						// 모든 아이템 벡터
	vector <ItemInfo>::iterator viPlayerAllItem;			// 모든 아이템 벡터

public:
	Player();
	~Player();

	HRESULT Init(string imageName);
	void Release();
	void Update();
	void Render(HDC hdc);

	void PlayerMove();            // 플레이어 이동키 함수
	void PlayerSilde();           // 플레이어 이동시 슬라이딩 함수
	void PlayerShot();            // 플레이어 공격키 함수
	void PlayerShotMove();        // 플레이어 공격시 방향 함수
	void PlayerAnimation();       // 플레이어 애니메이션

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
