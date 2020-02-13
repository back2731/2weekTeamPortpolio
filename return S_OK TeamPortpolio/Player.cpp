#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::Init(string imageName)
{
	// 플레이어 IDLE
	player.playerHeadImage = IMAGEMANAGER->addFrameImage("playerHead", "images/player/player.bmp", 320 * 2, 124 * 2, 10, 4, true, RGB(255, 0, 255));
	int arrlen[] = { 0 };
	ANIMATIONMANAGER->addAnimation("headIdle", "playerHead", arrlen, 1, 15, true);
	aniHead = ANIMATIONMANAGER->findAnimation("headIdle");

	player.playerBodyImage = IMAGEMANAGER->addFrameImage("playerBody", "images/player/player.bmp", 320 * 2, 124 * 2, 10, 4, true, RGB(255, 0, 255));
	int arrlen2[] = { 22 };
	ANIMATIONMANAGER->addAnimation("bodyIdle", "playerBody", arrlen2, 1, 15, true);
	aniBody = ANIMATIONMANAGER->findAnimation("bodyIdle");

	// 플레이어 정보
	player.playerHeadRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 100, 32 * 2, 23 * 2);		// 머리 상자
	player.playerBodyRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 70, 32 * 2, 11 * 2);		// 몸 상자
	player.playerOffensePower = 5;																// 공격력
	player.playerShotSpeed = 8.0f;																// 공격속도
	player.playerShotRange = 450.0f;															// 공격사거리
	playerBulletCount = 0;																		// 불렛 카운트
	player.playerShotDelay = 25;																// 공격주기
	player.playerSpeed = 3.0f;																	// 이동속도
	player.playerSlideSpeed = 2.0f;																// 슬라이딩 속도

	// 플레이어 무브 변수 초기화
	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;
	// 플레이어 슬라이딩 변수 초기화
	slideLeft = false;
	slideRight = false;
	slideUp = false;
	slideDown = false;
	// 플레이어 슈팅 변수 초기화
	playerLeftShot = false;
	playerRightShot = false;
	playerUpShot = false;
	playerDownShot = false;

	// 플레이어 프레임
	direction = PLAYER_IDLE;

	return S_OK;
}

void Player::Release()
{
}

void Player::Update()
{
	PlayerAnimation();
	PlayerMove();
	PlayerShot();
	COLLISIONMANAGER->PlayerBulletCollision(vPlayerBullet, viPlayerBullet);
}

void Player::Render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		//Rectangle(hdc, player.playerHeadRect.left, player.playerHeadRect.top, player.playerHeadRect.right, player.playerHeadRect.bottom);
		//Rectangle(hdc, player.playerBodyRect.left, player.playerBodyRect.top, player.playerBodyRect.right, player.playerBodyRect.bottom);
		Rectangle(hdc, player.playerHitRect.left, player.playerHitRect.top, player.playerHitRect.right, player.playerHitRect.bottom);

		HBRUSH brush = CreateSolidBrush(RGB(255, 255, 153));
		FillRect(hdc, &player.playerHitRect, brush);
		DeleteObject(brush);
	}

	player.playerBodyImage->aniRender(hdc, player.playerBodyRect.left, player.playerBodyRect.top - 20, aniBody);
	player.playerHeadImage->aniRender(hdc, player.playerHeadRect.left, player.playerHeadRect.top - 5, aniHead);
	BULLETMANAGER->RenderBullet(hdc, vPlayerBullet, viPlayerBullet);
}

void Player::PlayerMove()
{
	//왼쪽
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		direction = PLAYER_LEFT;
		isLeft = true;

		player.playerHeadRect.left -= player.playerSpeed;
		player.playerHeadRect.right -= player.playerSpeed;

		player.playerBodyRect.left -= player.playerSpeed;
		player.playerBodyRect.right -= player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		direction = PLAYER_IDLE;
	}

	//오른쪽
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		direction = PLAYER_RIGHT;
		isRight = true;

		player.playerHeadRect.left += player.playerSpeed;
		player.playerHeadRect.right += player.playerSpeed;

		player.playerBodyRect.left += player.playerSpeed;
		player.playerBodyRect.right += player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		direction = PLAYER_IDLE;
	}

	//위
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		direction = PLAYER_UP;
		isUp = true;

		player.playerHeadRect.top -= player.playerSpeed;
		player.playerHeadRect.bottom -= player.playerSpeed;

		player.playerBodyRect.top -= player.playerSpeed;
		player.playerBodyRect.bottom -= player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		direction = PLAYER_IDLE;
	}

	//아래
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		direction = PLAYER_DOWN;
		isDown = true;

		player.playerHeadRect.top += player.playerSpeed;
		player.playerHeadRect.bottom += player.playerSpeed;

		player.playerBodyRect.top += player.playerSpeed;
		player.playerBodyRect.bottom += player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		direction = PLAYER_IDLE;
	}

	PlayerSilde();	//플레이어 슬라이딩

	//플레이어 피격 상자
	player.playerHitRect = RectMakeCenter(player.playerBodyRect.left + (player.playerBodyRect.right - player.playerBodyRect.left) / 2,
		player.playerBodyRect.top + (player.playerBodyRect.bottom - player.playerBodyRect.top) / 2, 40, 20);
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

		if (player.playerSlideSpeed < 0.4f)
		{
			player.playerSlideSpeed = 2.0f;
			isLeft = false;
			slideLeft = false;
		}
	}

	//오른쪽 슬라이딩
	else if (slideRight)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;

		player.playerHeadRect.left += int(player.playerSlideSpeed + 1);
		player.playerHeadRect.right += int(player.playerSlideSpeed + 1);

		player.playerBodyRect.left += int(player.playerSlideSpeed + 1);
		player.playerBodyRect.right += int(player.playerSlideSpeed + 1);

		if (player.playerSlideSpeed < 0.4f)
		{
			player.playerSlideSpeed = 2.0f;
			isRight = false;
			slideRight = false;
		}
	}

	//위쪽 슬라이딩
	else if (slideUp)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;

		player.playerHeadRect.top -= player.playerSlideSpeed;
		player.playerHeadRect.bottom -= player.playerSlideSpeed;

		player.playerBodyRect.top -= player.playerSlideSpeed;
		player.playerBodyRect.bottom -= player.playerSlideSpeed;

		if (player.playerSlideSpeed < 0.4f)
		{
			player.playerSlideSpeed = 2.0f;
			isUp = false;
			slideUp = false;
		}
	}

	//아래쪽 슬라이딩
	else if (slideDown)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;

		player.playerHeadRect.top += int(player.playerSlideSpeed + 1);
		player.playerHeadRect.bottom += int(player.playerSlideSpeed + 1);

		player.playerBodyRect.top += int(player.playerSlideSpeed + 1);
		player.playerBodyRect.bottom += int(player.playerSlideSpeed + 1);

		if (player.playerSlideSpeed < 0.4f)
		{
			player.playerSlideSpeed = 2.0f;
			isDown = false;
			slideDown = false;
		}
	}
}

void Player::PlayerShot()
{
	//왼쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//애니메이션 프레임
		ANIMATIONMANAGER->addAnimation("headLeft", "playerHead", 6, 7, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headLeft");
		ANIMATIONMANAGER->resume("headLeft");

		playerLeftShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		//애니메이션 프레임
		aniHead = ANIMATIONMANAGER->findAnimation("headLeft");
		ANIMATIONMANAGER->stop("headLeft");

		playerLeftShot = false;
	}

	//오른쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//애니메이션 프레임
		ANIMATIONMANAGER->addAnimation("headRight", "playerHead", 2, 3, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headRight");
		ANIMATIONMANAGER->resume("headRight");

		playerRightShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		//애니메이션 프레임
		aniHead = ANIMATIONMANAGER->findAnimation("headRight");
		ANIMATIONMANAGER->stop("headRight");

		playerRightShot = false;
	}

	//위쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//애니메이션 프레임
		ANIMATIONMANAGER->addAnimation("headUp", "playerHead", 4, 5, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headUp");
		ANIMATIONMANAGER->resume("headUp");

		playerUpShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		//애니메이션 프레임
		aniHead = ANIMATIONMANAGER->findAnimation("headUp");
		ANIMATIONMANAGER->stop("headUp");

		playerUpShot = false;
	}

	//아래쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//애니메이션 프레임
		ANIMATIONMANAGER->addAnimation("headDown", "playerHead", 0, 1, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headDown");
		ANIMATIONMANAGER->resume("headDown");

		playerDownShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		//애니메이션 프레임
		aniHead = ANIMATIONMANAGER->findAnimation("headDown");
		ANIMATIONMANAGER->stop("headDown");

		playerDownShot = false;
	}

	PlayerShotMove();	//플레이어 공격 방향
}

void Player::PlayerShotMove()
{
	//불렛 방향
	if (playerLeftShot)
	{
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2,
			ANGLE_180, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);

	}
	else if (playerRightShot)
	{
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2,
			ANGLE_0, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);
	}
	else if (playerUpShot)
	{
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2 - 20,
			ANGLE_90, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);
	}
	else if (playerDownShot)
	{
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2 + 20,
			ANGLE_270, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);
	}

	//불렛 무브
	BULLETMANAGER->MoveBullet(vPlayerBullet, viPlayerBullet);
}

void Player::PlayerAnimation()
{
	switch (direction)
	{
	case PLAYER_IDLE:
		//애니메이션 프레임
		aniHead = ANIMATIONMANAGER->findAnimation("headIdle");
		ANIMATIONMANAGER->stop("headIdle");
		aniBody = ANIMATIONMANAGER->findAnimation("bodyIdle");
		ANIMATIONMANAGER->stop("bodyIdle");
		break;
	case PLAYER_LEFT:
		//애니메이션 프레임
		ANIMATIONMANAGER->addAnimation("bodyLeft", "playerBody", 10, 19, 15, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyLeft");
		ANIMATIONMANAGER->resume("bodyLeft");
		break;
	case PLAYER_RIGHT:
		//애니메이션 프레임
		ANIMATIONMANAGER->addAnimation("bodyRight", "playerBody", 30, 39, 15, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyRight");
		ANIMATIONMANAGER->resume("bodyRight");
		break;
	case PLAYER_UP:
		//애니메이션 프레임
		ANIMATIONMANAGER->addAnimation("bodyUp", "playerBody", 20, 29, 15, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyUp");
		ANIMATIONMANAGER->resume("bodyUp");
		break;
	case PLAYER_DOWN:
		//애니메이션 프레임
		ANIMATIONMANAGER->addAnimation("bodyDown", "playerBody", 20, 29, 15, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyDown");
		ANIMATIONMANAGER->resume("bodyDown");
		break;
	}
}

void Player::SetPlayerRectX(int num)
{
	player.playerHeadRect.left += num;
	player.playerHeadRect.right += num;

	player.playerBodyRect.left += num;
	player.playerBodyRect.right += num;

	player.playerHitRect.left += num;
	player.playerHitRect.right += num;
}

void Player::SetPlayerRectY(int num)
{
	player.playerHeadRect.top += num;
	player.playerHeadRect.bottom += num;

	player.playerBodyRect.top += num;
	player.playerBodyRect.bottom += num;

	player.playerHitRect.top += num;
	player.playerHitRect.bottom += num;
}
