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
	player.playerHeadImage = IMAGEMANAGER->addFrameImage("playerHead", "images/player/issac.bmp", 512 * 2, 512 * 2, 16, 16, true, RGB(255, 0, 255));
	int arrlen[] = { 0 };
	ANIMATIONMANAGER->addAnimation("head", "playerHead", arrlen, 1, 10, true);
	aniHead = ANIMATIONMANAGER->findAnimation("head");

	player.playerBodyImage = IMAGEMANAGER->addFrameImage("playerBody", "images/player/issac.bmp", 512 * 2, 512 * 2, 16, 16, true, RGB(255, 0, 255));
	int arrlen2[] = { 16 };
	ANIMATIONMANAGER->addAnimation("body", "playerBody", arrlen2, 1, 10, true);
	aniBody = ANIMATIONMANAGER->findAnimation("body");

	player.playerHeadRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 32 * 2, 23 * 2);			//머리 상자
	player.playerBodyRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 30, 32 * 2, 11 * 2);	//몸 상자
	player.playerShotSpeed = 8.0f;																//공격속도
	player.playerShotRange = 450.0f;															//공격사거리
	player.playerShotDelay = 25;																//공격주기
	player.playerSpeed = 5.0f;																	//이동속도
	player.playerSlideSpeed = 3.0f;																//슬라이딩 속도
	playerBulletInterval = 0;

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
	//플레이어 슈팅 변수 초기화
	playerLeftShot = false;
	playerRightShot = false;
	playerUpShot = false;
	playerDownShot = false;

	return S_OK;
}

void Player::Release()
{
}

void Player::Update()
{
	PlayerMove();
	PlayerShot();
	COLLISIONMANAGER->PlayerBulletCollision(vPlayerBullet, viPlayerBullet);

	//애니메이션 프레임
	aniHead = ANIMATIONMANAGER->findAnimation("head");
	ANIMATIONMANAGER->start("head");
	aniBody = ANIMATIONMANAGER->findAnimation("body");
	ANIMATIONMANAGER->start("body");
}

void Player::Render(HDC hdc)
{
	//Rectangle(hdc, player.playerHeadRect.left, player.playerHeadRect.top, player.playerHeadRect.right, player.playerHeadRect.bottom);
	//Rectangle(hdc, player.playerBodyRect.left, player.playerBodyRect.top, player.playerBodyRect.right, player.playerBodyRect.bottom);
	//Rectangle(hdc, player.playerHitRect.left, player.playerHitRect.top, player.playerHitRect.right, player.playerHitRect.bottom);
	player.playerBodyImage->aniRender(hdc, player.playerBodyRect.left, player.playerBodyRect.top - 25, aniBody);
	player.playerBodyImage->aniRender(hdc, player.playerHeadRect.left, player.playerHeadRect.top - 5, aniHead);
	BULLETMANAGER->RenderBullet(hdc, vPlayerBullet, viPlayerBullet);
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

	PlayerSilde();	//플레이어 슬라이딩

	//플레이어 피격 상자
	player.playerHitRect = RectMakeCenter(player.playerBodyRect.left + (player.playerBodyRect.right - player.playerBodyRect.left) / 2,
		player.playerBodyRect.top - 10, 60, 65);
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
	else if (slideRight)
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
	else if (slideUp)
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
	else if (slideDown)
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
	else if (slideLeftUp)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;

		player.playerHeadRect.left -= player.playerSlideSpeed;
		player.playerHeadRect.right -= player.playerSlideSpeed;
		player.playerHeadRect.top -= player.playerSlideSpeed;
		player.playerHeadRect.bottom -= player.playerSlideSpeed;

		player.playerBodyRect.left -= player.playerSlideSpeed;
		player.playerBodyRect.right -= player.playerSlideSpeed;
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
	else if (slideLeftDown)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;

		player.playerHeadRect.left -= player.playerSlideSpeed;
		player.playerHeadRect.right -= player.playerSlideSpeed;
		player.playerHeadRect.top += player.playerSlideSpeed;
		player.playerHeadRect.bottom += player.playerSlideSpeed;

		player.playerBodyRect.left -= player.playerSlideSpeed;
		player.playerBodyRect.right -= player.playerSlideSpeed;
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
	else if (slideRightUp)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;

		player.playerHeadRect.left += player.playerSlideSpeed;
		player.playerHeadRect.right += player.playerSlideSpeed;
		player.playerHeadRect.top -= player.playerSlideSpeed;
		player.playerHeadRect.bottom -= player.playerSlideSpeed;

		player.playerBodyRect.left += player.playerSlideSpeed;
		player.playerBodyRect.right += player.playerSlideSpeed;
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
	else if (slideRightDown)
	{
		player.playerSlideSpeed = player.playerSlideSpeed * 0.9f;

		player.playerHeadRect.left += player.playerSlideSpeed;
		player.playerHeadRect.right += player.playerSlideSpeed;
		player.playerHeadRect.top += player.playerSlideSpeed;
		player.playerHeadRect.bottom += player.playerSlideSpeed;

		player.playerBodyRect.left += player.playerSlideSpeed;
		player.playerBodyRect.right += player.playerSlideSpeed;
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
	}

	//오른쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		playerRightShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		playerRightShot = false;
	}

	//위쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		playerUpShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		playerUpShot = false;
	}

	//아래쪽 총알 발사
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		playerDownShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
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
			ANGLE_180, player.playerShotSpeed, player.playerShotRange, playerBulletInterval++, player.playerShotDelay);

	}
	else if (playerRightShot)
	{
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2,
			ANGLE_0, player.playerShotSpeed, player.playerShotRange, playerBulletInterval++, player.playerShotDelay);
	}
	else if (playerUpShot)
	{
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2,
			ANGLE_90, player.playerShotSpeed, player.playerShotRange, playerBulletInterval++, player.playerShotDelay);
	}
	else if (playerDownShot)
	{
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2,
			ANGLE_270, player.playerShotSpeed, player.playerShotRange, playerBulletInterval++, player.playerShotDelay);
	}

	//불렛 무브
	BULLETMANAGER->PlayerMoveBullet(vPlayerBullet, viPlayerBullet);
}