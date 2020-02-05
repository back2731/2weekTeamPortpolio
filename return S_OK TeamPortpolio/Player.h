#pragma once

//캐릭터 방향 enum문
enum Direction
{
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_UP,
	PLAYER_DOWN
};

//캐릭터 속성 구조체
struct PlayerInfo
{
	image* playerHeadImage;		//플레이어 머리 이미지
	image* playerBodyImage;		//플레이어 몸 이미지
	RECT playerHeadRect;		//플레이어 머리 상자
	RECT playerBodyRect;		//플레이어 몸 상자
	float playerSpeed;			//이동속도
	float playerSlideSpeed;		//슬라이딩 속도
};

class Player
{
private:
	Direction direction;
	PlayerInfo player;

	RECT rect;

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

public:
	Player();
	~Player();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void PlayerMove();
	void PlayerSilde();
};