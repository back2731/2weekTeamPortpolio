#pragma once

//캐릭터 방향 enum문
enum Direction
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
	image*   playerHeadImage;      // 플레이어 머리 이미지
	image*   playerBodyImage;      // 플레이어 몸 이미지
	RECT   playerHeadRect;         // 플레이어 머리 상자
	RECT   playerBodyRect;         // 플레이어 몸 상자
	RECT   playerHitRect;         // 플레이어 피격용 상자
	int      playerOffensePower;      // 플레이어 공격력
	int      playerShotDelay;      // 공격주기
	float   playerShotSpeed;      // 공격속도
	float   playerShotRange;      // 공격사거리
	float   playerSpeed;         // 이동속도
	float   playerSlideSpeed;      // 슬라이딩 속도
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
	int playerBulletCount;         // 플레이어 불렛 카운트
	int headNum;
	int bodyNum;

private:
	//플레이어 무브 변수
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	//플레이어 슬라이딩 변수
	bool slideLeft;
	bool slideRight;
	bool slideUp;
	bool slideDown;
	//플레이어 대각 슬라이딩 변수
	bool slideLeftUp;
	bool slideLeftDown;
	bool slideRightUp;
	bool slideRightDown;
	//플레이어 슈팅 변수
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

	void PlayerMove();            //플레이어 이동키 함수
	void PlayerSilde();            //플레이어 이동시 슬라이딩 함수
	void PlayerShot();            //플레이어 공격키 함수
	void PlayerShotMove();         //플레이어 공격시 방향 함수
	void PlayerAnimation();         //플레이어 애니메이션

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