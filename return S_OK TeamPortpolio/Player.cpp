#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::Init()
{
	//player.playerHeadImage = IMAGEMANAGER->findImage(imageName);								//머리 이미지
	//player.playerBodyImage = IMAGEMANAGER->findImage(imageName);								//몸 이미지
	player.playerHeadRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 64, 62);					//머리 상자
	player.playerBodyRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 62, 64, 62);			//몸 상자
	player.playerSpeed = 6.0f;																	//이동속도
	player.playerSlideSpeed = 3.0f;																//슬라이딩 속도

	//플레이어 무브 변수 초기화
	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;
	//플레이어 슬라이딩 변수 초기화
	slideLeft = false;
	slideRight = false;
	slideUp = false;
	slideDown = false;
	//플레이어 대각 슬라이딩 변수 초기화
	slideLeftUp = false;
	slideLeftDown = false;
	slideRightUp = false;
	slideRightDown = false;

	return S_OK;
}

void Player::Release()
{
}

void Player::Update()
{
	PlayerMove();
	PlayerSilde();
}

void Player::Render(HDC hdc)
{
	Rectangle(hdc, player.playerHeadRect.left, player.playerHeadRect.top, player.playerHeadRect.right, player.playerHeadRect.bottom);
	Rectangle(hdc, player.playerBodyRect.left, player.playerBodyRect.top, player.playerBodyRect.right, player.playerBodyRect.bottom);
}

void Player::PlayerMove()
{
	//왼쪽
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		isLeft = true;
		player.playerHeadRect.left -= player.playerSpeed;
		player.playerHeadRect.right -= player.playerSpeed;
		player.playerBodyRect.left -= player.playerSpeed;
		player.playerBodyRect.right -= player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		if (isUp) slideLeftUp = true;
		else if (isDown) slideLeftDown = true;
		else slideLeft = true;
	}

	//오른쪽
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		isRight = true;
		player.playerHeadRect.left += player.playerSpeed;
		player.playerHeadRect.right += player.playerSpeed;
		player.playerBodyRect.left += player.playerSpeed;
		player.playerBodyRect.right += player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		if (isUp) slideRightUp = true;
		else if (isDown) slideRightDown = true;
		else slideRight = true;
	}

	//위
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		isUp = true;
		player.playerHeadRect.top -= player.playerSpeed;
		player.playerHeadRect.bottom -= player.playerSpeed;
		player.playerBodyRect.top -= player.playerSpeed;
		player.playerBodyRect.bottom -= player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		if (isLeft) slideLeftUp = true;
		else if (isRight) slideRightUp = true;
		else slideUp = true;
	}

	//아래
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		isDown = true;
		player.playerHeadRect.top += player.playerSpeed;
		player.playerHeadRect.bottom += player.playerSpeed;
		player.playerBodyRect.top += player.playerSpeed;
		player.playerBodyRect.bottom += player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		if (isLeft) slideLeftDown = true;
		else if (isRight) slideRightDown = true;
		else slideDown = true;
	}
}

void Player::PlayerSilde()
{
	//왼쪽 슬라이딩
	if (slideLeft)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;
		player.playerHeadRect.left -= player.playerSlideSpeed;
		player.playerHeadRect.right -= player.playerSlideSpeed;
		player.playerBodyRect.left -= player.playerSlideSpeed;
		player.playerBodyRect.right -= player.playerSlideSpeed;
		if (player.playerSlideSpeed < 1.2f)
		{
			player.playerSlideSpeed = 3.0f;
			isLeft = false;
			slideLeft = false;
		}
	}
	//오른쪽 슬라이딩
	if (slideRight)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;
		player.playerHeadRect.left += player.playerSlideSpeed;
		player.playerHeadRect.right += player.playerSlideSpeed;
		player.playerBodyRect.left += player.playerSlideSpeed;
		player.playerBodyRect.right += player.playerSlideSpeed;
		if (player.playerSlideSpeed < 1.2f)
		{
			player.playerSlideSpeed = 3.0f;
			isRight = false;
			slideRight = false;
		}
	}
	//위쪽 슬라이딩
	if (slideUp)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;
		player.playerHeadRect.top -= player.playerSlideSpeed;
		player.playerHeadRect.bottom -= player.playerSlideSpeed;
		player.playerBodyRect.top -= player.playerSlideSpeed;
		player.playerBodyRect.bottom -= player.playerSlideSpeed;
		if (player.playerSlideSpeed < 1.2f)
		{
			player.playerSlideSpeed = 3.0f;
			isUp = false;
			slideUp = false;
		}
	}
	//아래쪽 슬라이딩
	if (slideDown)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;
		player.playerHeadRect.top += player.playerSlideSpeed;
		player.playerHeadRect.bottom += player.playerSlideSpeed;
		player.playerBodyRect.top += player.playerSlideSpeed;
		player.playerBodyRect.bottom += player.playerSlideSpeed;
		if (player.playerSlideSpeed < 1.2f)
		{
			player.playerSlideSpeed = 3.0f;
			isDown = false;
			slideDown = false;
		}
	}

	//왼쪽위 슬라이딩
	if (slideLeftUp)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;
		player.playerHeadRect.left -= player.playerSlideSpeed;
		player.playerHeadRect.right -= player.playerSlideSpeed;
		player.playerBodyRect.left -= player.playerSlideSpeed;
		player.playerBodyRect.right -= player.playerSlideSpeed;
		player.playerHeadRect.top -= player.playerSlideSpeed;
		player.playerHeadRect.bottom -= player.playerSlideSpeed;
		player.playerBodyRect.top -= player.playerSlideSpeed;
		player.playerBodyRect.bottom -= player.playerSlideSpeed;
		if (player.playerSlideSpeed < 1.2f)
		{
			player.playerSlideSpeed = 3.0f;
			isLeft = false;
			isUp = false;
			slideLeftUp = false;
		}
	}
	//왼쪽아래 슬라이딩
	if (slideLeftDown)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;
		player.playerHeadRect.left -= player.playerSlideSpeed;
		player.playerHeadRect.right -= player.playerSlideSpeed;
		player.playerBodyRect.left -= player.playerSlideSpeed;
		player.playerBodyRect.right -= player.playerSlideSpeed;
		player.playerHeadRect.top += player.playerSlideSpeed;
		player.playerHeadRect.bottom += player.playerSlideSpeed;
		player.playerBodyRect.top += player.playerSlideSpeed;
		player.playerBodyRect.bottom += player.playerSlideSpeed;
		if (player.playerSlideSpeed < 1.2f)
		{
			player.playerSlideSpeed = 3.0f;
			isLeft = false;
			isDown = false;
			slideLeftDown = false;
		}
	}
	//오른쪽위 슬라이딩
	if (slideRightUp)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;
		player.playerHeadRect.left += player.playerSlideSpeed;
		player.playerHeadRect.right += player.playerSlideSpeed;
		player.playerBodyRect.left += player.playerSlideSpeed;
		player.playerBodyRect.right += player.playerSlideSpeed;
		player.playerHeadRect.top -= player.playerSlideSpeed;
		player.playerHeadRect.bottom -= player.playerSlideSpeed;
		player.playerBodyRect.top -= player.playerSlideSpeed;
		player.playerBodyRect.bottom -= player.playerSlideSpeed;
		if (player.playerSlideSpeed < 1.2f)
		{
			player.playerSlideSpeed = 3.0f;
			isRight = false;
			isUp = false;
			slideRightUp = false;
		}
	}
	//오른쪽아래 슬라이딩
	if (slideRightDown)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;
		player.playerHeadRect.left += player.playerSlideSpeed;
		player.playerHeadRect.right += player.playerSlideSpeed;
		player.playerBodyRect.left += player.playerSlideSpeed;
		player.playerBodyRect.right += player.playerSlideSpeed;
		player.playerHeadRect.top += player.playerSlideSpeed;
		player.playerHeadRect.bottom += player.playerSlideSpeed;
		player.playerBodyRect.top += player.playerSlideSpeed;
		player.playerBodyRect.bottom += player.playerSlideSpeed;
		if (player.playerSlideSpeed < 1.2f)
		{
			player.playerSlideSpeed = 3.0f;
			isRight = false;
			isDown = false;
			slideRightDown = false;
		}
	}
}
