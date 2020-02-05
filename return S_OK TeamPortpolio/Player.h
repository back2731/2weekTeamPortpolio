#pragma once

//ĳ���� ���� enum��
enum Direction
{
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_UP,
	PLAYER_DOWN
};

//ĳ���� �Ӽ� ����ü
struct PlayerInfo
{
	image* playerHeadImage;		//�÷��̾� �Ӹ� �̹���
	image* playerBodyImage;		//�÷��̾� �� �̹���
	RECT playerHeadRect;		//�÷��̾� �Ӹ� ����
	RECT playerBodyRect;		//�÷��̾� �� ����
	float playerSpeed;			//�̵��ӵ�
	float playerSlideSpeed;		//�����̵� �ӵ�
};

class Player
{
private:
	Direction direction;
	PlayerInfo player;

	RECT rect;

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