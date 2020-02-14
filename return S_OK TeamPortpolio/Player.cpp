#include "stdafx.h"
#include "Player.h"
#include "Shop.h"

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::Init(string imageName)
{
	// 플레이어 그림자
	shadow = IMAGEMANAGER->addImage("shadow", "images/player/playerShadow.bmp", 120 / 3, 49 / 3, true, RGB(255, 0, 255));
	// 플레이어 HeadIdle
	player.playerHeadImage = IMAGEMANAGER->addFrameImage("playerHead", "images/player/player.bmp", 320 * 2, 124 * 2, 10, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("headIdle", "playerHead", arrHeadIdle, 1, 1, true);
	aniHead = ANIMATIONMANAGER->findAnimation("headIdle");
	// 플레이어 BodyIdle
	player.playerBodyImage = IMAGEMANAGER->addFrameImage("playerBody", "images/player/player.bmp", 320 * 2, 124 * 2, 10, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("bodyIdle", "playerBody", arrBodyIdle, 1, 1, true);
	aniBody = ANIMATIONMANAGER->findAnimation("bodyIdle");

	// 플레이어 정보
	player.playerHeadRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 32 * 2, 23 * 2);			// 머리 상자
	player.playerBodyRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 30, 32 * 2, 11 * 2);	// 몸 상자
	player.playerOffensePower = 2;																// 공격력
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

	//아이템 정보
	m_Shop = new Shop;
	vPlayerActiveItem = ITEMMANAGER->GetActiveItemInfo();
	vPlayerPassiveItem = ITEMMANAGER->GetPassiveItemInfo();
	vPlayerTrinkets = ITEMMANAGER->GetTrinketsInfo();

	vPlayerHeart = ITEMMANAGER->GetHeartInfo();

	vPlayerBomb = ITEMMANAGER->GetBombInfo();
	vPlayerKey = ITEMMANAGER->GetKeyInfo();

	vPlayerCard = ITEMMANAGER->GetCardInfo();
	vPlayerPill = ITEMMANAGER->GetPillInfo();
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
		Rectangle(hdc, player.playerHeadRect.left, player.playerHeadRect.top, player.playerHeadRect.right, player.playerHeadRect.bottom);
		Rectangle(hdc, player.playerBodyRect.left, player.playerBodyRect.top, player.playerBodyRect.right, player.playerBodyRect.bottom);
		Rectangle(hdc, player.playerHitRect.left, player.playerHitRect.top, player.playerHitRect.right, player.playerHitRect.bottom);

		HBRUSH brush = CreateSolidBrush(RGB(255, 255, 153));
		FillRect(hdc, &player.playerHitRect, brush);
		DeleteObject(brush);
	}

	shadow->alphaRender(hdc, player.playerBodyRect.left + 12, player.playerBodyRect.top + 12, 70);
	player.playerBodyImage->aniRender(hdc, player.playerBodyRect.left, player.playerBodyRect.top - 20, aniBody);
	player.playerHeadImage->aniRender(hdc, player.playerHeadRect.left, player.playerHeadRect.top - 5, aniHead);
	BULLETMANAGER->RenderBullet(hdc, vPlayerBullet, viPlayerBullet);

	if (IntersectRect(&temp, &GetPlayerHitRect(), &m_Shop->GetShopItemRect(0)))
	{
		Rectangle(hdc, test1.left, test1.top, test1.right, test1.bottom );

	}
	if (IntersectRect(&temp, &GetPlayerHitRect(), &m_Shop->GetShopItemRect(1)))
	{
		Rectangle(hdc, test2.left, test2.top, test2.right, test2.bottom);
	}
	if (IntersectRect(&temp, &GetPlayerHitRect(), &m_Shop->GetShopItemRect(2)))
	{
		Rectangle(hdc, test3.left, test3.top, test3.right, test3.bottom);
	}
}

void Player::PlayerMove()
{
	//왼쪽
	if (KEYMANAGER->isStayKeyDown('F'))
	{
		direction = PLAYER_LEFT;
		isLeft = true;

		player.playerHeadRect.left -= player.playerSpeed;
		player.playerHeadRect.right -= player.playerSpeed;

		player.playerBodyRect.left -= player.playerSpeed;
		player.playerBodyRect.right -= player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('F'))
	{
		direction = PLAYER_IDLE;
		slideLeft = true;
	}

	//오른쪽
	if (KEYMANAGER->isStayKeyDown('H'))
	{
		direction = PLAYER_RIGHT;
		isRight = true;

		player.playerHeadRect.left += player.playerSpeed;
		player.playerHeadRect.right += player.playerSpeed;

		player.playerBodyRect.left += player.playerSpeed;
		player.playerBodyRect.right += player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('H'))
	{
		direction = PLAYER_IDLE;
		slideRight = true;
	}

	//위
	if (KEYMANAGER->isStayKeyDown('T'))
	{
		direction = PLAYER_UP;
		isUp = true;

		player.playerHeadRect.top -= player.playerSpeed;
		player.playerHeadRect.bottom -= player.playerSpeed;

		player.playerBodyRect.top -= player.playerSpeed;
		player.playerBodyRect.bottom -= player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('T'))
	{
		direction = PLAYER_IDLE;
		slideUp = true;
	}

	//아래
	if (KEYMANAGER->isStayKeyDown('G'))
	{
		direction = PLAYER_DOWN;
		isDown = true;

		player.playerHeadRect.top += player.playerSpeed;
		player.playerHeadRect.bottom += player.playerSpeed;

		player.playerBodyRect.top += player.playerSpeed;
		player.playerBodyRect.bottom += player.playerSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp('G'))
	{
		direction = PLAYER_IDLE;
		slideDown = true;
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

		if (player.playerSlideSpeed < 0.8f)
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

		if (player.playerSlideSpeed < 0.8f)
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

		if (player.playerSlideSpeed < 0.8f)
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

		if (player.playerSlideSpeed < 0.8f)
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
		playerLeftShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		playerLeftShot = false;
		
		//애니메이션 프레임
		aniHead = ANIMATIONMANAGER->findAnimation("shotLeft");
		ANIMATIONMANAGER->stop("shotLeft");
	}

	//오른쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		playerRightShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		playerRightShot = false;
	
		//애니메이션 프레임
		aniHead = ANIMATIONMANAGER->findAnimation("shotRight");
		ANIMATIONMANAGER->stop("shotRight");
	}

	//위쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		playerUpShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		playerUpShot = false;

		//애니메이션 프레임
		aniHead = ANIMATIONMANAGER->findAnimation("shotUp");
		ANIMATIONMANAGER->stop("shotUp");
	}

	//아래쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		playerDownShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		playerDownShot = false;
		
		//애니메이션 프레임
		aniHead = ANIMATIONMANAGER->findAnimation("shotDown");
		ANIMATIONMANAGER->stop("shotDown");
	}

	PlayerShotMove();	//플레이어 공격 방향
}

void Player::PlayerShotMove()
{
	//불렛 방향
	if (playerLeftShot)
	{
		//왼쪽 공격 애니메이션
		ANIMATIONMANAGER->addAnimation("shotLeft", "playerHead", 6, 7, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("shotLeft");
		ANIMATIONMANAGER->resume("shotLeft");

		//불렛 조준
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2,
			ANGLE_180, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);

	}
	else if (playerRightShot)
	{
		//오른쪽 공격 애니메이션
		ANIMATIONMANAGER->addAnimation("shotRight", "playerHead", 2, 3, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("shotRight");
		ANIMATIONMANAGER->resume("shotRight");

		//불렛 조준
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2,
			ANGLE_0, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);
	}
	else if (playerUpShot)
	{
		//위쪽 공격 애니메이션
		ANIMATIONMANAGER->addAnimation("shotUp", "playerHead", 4, 5, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("shotUp");
		ANIMATIONMANAGER->resume("shotUp");

		//불렛 조준
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2 - 20,
			ANGLE_90, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);
	}
	else if (playerDownShot)
	{
		//아래쪽 공격 애니메이션
		ANIMATIONMANAGER->addAnimation("shotDown", "playerHead", 0, 1, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("shotDown");
		ANIMATIONMANAGER->resume("shotDown");

		//불렛 조준
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
		// 플레이어 HeadIdle
		aniHead = ANIMATIONMANAGER->findAnimation("headIdle");
		ANIMATIONMANAGER->stop("headIdle");
		// 플레이어 BodyIdle
		aniBody = ANIMATIONMANAGER->findAnimation("bodyIdle");
		ANIMATIONMANAGER->stop("bodyIdle");
		break;
	case PLAYER_LEFT:
		// 플레이어 HeadLeft
		ANIMATIONMANAGER->addAnimation("headLeft", "playerHead", arrHeadLeft, 1, 1, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headLeft");
		ANIMATIONMANAGER->stop("headLeft");
		// 플레이어 BodyLeft
		ANIMATIONMANAGER->addAnimation("bodyLeft", "playerBody", 10, 19, 12, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyLeft");
		ANIMATIONMANAGER->resume("bodyLeft");
		break;
	case PLAYER_RIGHT:
		// 플레이어 HeadRight
		ANIMATIONMANAGER->addAnimation("headRight", "playerHead", arrHeadRight, 1, 1, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headRight");
		ANIMATIONMANAGER->stop("headRight");
		// 플레이어 BodyRight
		ANIMATIONMANAGER->addAnimation("bodyRight", "playerBody", 30, 39, 12, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyRight");
		ANIMATIONMANAGER->resume("bodyRight");
		break;
	case PLAYER_UP:
		// 플레이어 HeadUp
		ANIMATIONMANAGER->addAnimation("headUp", "playerHead", arrHeadUp, 1, 1, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headUp");
		ANIMATIONMANAGER->stop("headUp");
		// 플레이어 BodyUp
		ANIMATIONMANAGER->addAnimation("bodyUp", "playerBody", 20, 29, 12, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyUp");
		ANIMATIONMANAGER->resume("bodyUp");
		break;
	case PLAYER_DOWN:
		// 플레이어 HeadDown
		ANIMATIONMANAGER->addAnimation("headIdle", "playerHead", arrHeadIdle, 1, 1, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headIdle");
		ANIMATIONMANAGER->stop("headIdle");
		// 플레이어 BodyDown
		ANIMATIONMANAGER->addAnimation("bodyDown", "playerBody", 20, 29, 12, false, true);
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

