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
	// �÷��̾� IDLE (�Ӹ�)
	player.playerHeadImage = IMAGEMANAGER->addFrameImage("playerHead", "images/player/player.bmp", 320 * 2, 124 * 2, 10, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("headIdle", "playerHead", arrHeadIdle, 1, 1, true);
	aniHead = ANIMATIONMANAGER->findAnimation("headIdle");
	// �÷��̾� IDLE (��)
	player.playerBodyImage = IMAGEMANAGER->addFrameImage("playerBody", "images/player/player.bmp", 320 * 2, 124 * 2, 10, 4, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addAnimation("bodyIdle", "playerBody", arrBodyIdle, 1, 1, true);
	aniBody = ANIMATIONMANAGER->findAnimation("bodyIdle");

	// �÷��̾� ����

	player.playerHeadRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 100, 32 * 2, 23 * 2);	// �Ӹ� ����
	player.playerBodyRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 70, 32 * 2, 11 * 2);	// �� ����

	player.playerOffensePower = 5;																// ���ݷ�
	player.playerShotSpeed = 8.0f;																// ���ݼӵ�
	player.playerShotRange = 450.0f;															// ���ݻ�Ÿ�
	playerBulletCount = 0;																		// �ҷ� ī��Ʈ
	player.playerShotDelay = 25;																// �����ֱ�
	player.playerSpeed = 3.0f;																	// �̵��ӵ�
	player.playerSlideSpeed = 2.0f;																// �����̵� �ӵ�

	// �÷��̾� ���� ���� �ʱ�ȭ
	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;
	// �÷��̾� �����̵� ���� �ʱ�ȭ
	slideLeft = false;
	slideRight = false;
	slideUp = false;
	slideDown = false;
	// �÷��̾� ���� ���� �ʱ�ȭ
	playerLeftShot = false;
	playerRightShot = false;
	playerUpShot = false;
	playerDownShot = false;

	// �÷��̾� ������
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
	//����
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

	//������
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

	//��
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

	//�Ʒ�
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

	PlayerSilde();	//�÷��̾� �����̵�

	//�÷��̾� �ǰ� ����
	player.playerHitRect = RectMakeCenter(player.playerBodyRect.left + (player.playerBodyRect.right - player.playerBodyRect.left) / 2,
		player.playerBodyRect.top + (player.playerBodyRect.bottom - player.playerBodyRect.top) / 2, 40, 20);
}

void Player::PlayerSilde()
{
	//���� �����̵�
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

	//������ �����̵�
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

	//���� �����̵�
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

	//�Ʒ��� �����̵�
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
	//���� �Ѿ� �߻�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		playerLeftShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		playerLeftShot = false;
		
		//�ִϸ��̼� ������
		aniHead = ANIMATIONMANAGER->findAnimation("shotLeft");
		ANIMATIONMANAGER->stop("shotLeft");
	}

	//������ �Ѿ� �߻�
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		playerRightShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		playerRightShot = false;
	
		//�ִϸ��̼� ������
		aniHead = ANIMATIONMANAGER->findAnimation("shotRight");
		ANIMATIONMANAGER->stop("shotRight");
	}

	//���� �Ѿ� �߻�
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		playerUpShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		playerUpShot = false;

		//�ִϸ��̼� ������
		aniHead = ANIMATIONMANAGER->findAnimation("shotUp");
		ANIMATIONMANAGER->stop("shotUp");
	}

	//�Ʒ��� �Ѿ� �߻�
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		playerDownShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		playerDownShot = false;
		
		//�ִϸ��̼� ������
		aniHead = ANIMATIONMANAGER->findAnimation("shotDown");
		ANIMATIONMANAGER->stop("shotDown");
	}

	PlayerShotMove();	//�÷��̾� ���� ����
}

void Player::PlayerShotMove()
{
	//�ҷ� ����
	if (playerLeftShot)
	{
		//�ִϸ��̼� ������
		ANIMATIONMANAGER->addAnimation("shotLeft", "playerHead", 6, 7, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("shotLeft");
		ANIMATIONMANAGER->resume("shotLeft");

		//�ҷ� ����
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2,
			ANGLE_180, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);

	}
	else if (playerRightShot)
	{
		//�ִϸ��̼� ������
		ANIMATIONMANAGER->addAnimation("shotRight", "playerHead", 2, 3, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("shotRight");
		ANIMATIONMANAGER->resume("shotRight");

		//�ҷ� ����
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2,
			ANGLE_0, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);
	}
	else if (playerUpShot)
	{
		//�ִϸ��̼� ������
		ANIMATIONMANAGER->addAnimation("shotUp", "playerHead", 4, 5, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("shotUp");
		ANIMATIONMANAGER->resume("shotUp");

		//�ҷ� ����
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2 - 20,
			ANGLE_90, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);
	}
	else if (playerDownShot)
	{
		//�ִϸ��̼� ������
		ANIMATIONMANAGER->addAnimation("shotDown", "playerHead", 0, 1, 4, false, true);
		aniHead = ANIMATIONMANAGER->findAnimation("shotDown");
		ANIMATIONMANAGER->resume("shotDown");

		//�ҷ� ����
		BULLETMANAGER->ShootBullet("playerBullet", vPlayerBullet,
			player.playerHeadRect.left + (player.playerHeadRect.right - player.playerHeadRect.left) / 2,
			player.playerHeadRect.top + (player.playerHeadRect.bottom - player.playerHeadRect.top) / 2 + 20,
			ANGLE_270, player.playerShotSpeed, player.playerShotRange, playerBulletCount++, player.playerShotDelay);
	}

	//�ҷ� ����
	BULLETMANAGER->MoveBullet(vPlayerBullet, viPlayerBullet);
}

void Player::PlayerAnimation()
{
	switch (direction)
	{
	case PLAYER_IDLE:
		//�ִϸ��̼� ������
		aniHead = ANIMATIONMANAGER->findAnimation("headIdle");
		ANIMATIONMANAGER->stop("headIdle");
		aniBody = ANIMATIONMANAGER->findAnimation("bodyIdle");
		ANIMATIONMANAGER->stop("bodyIdle");
		break;
	case PLAYER_LEFT:
		//�ִϸ��̼� ������
		ANIMATIONMANAGER->addAnimation("headLeft", "playerHead", arrHeadLeft, 1, 1, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headLeft");
		ANIMATIONMANAGER->stop("headLeft");
		ANIMATIONMANAGER->addAnimation("bodyLeft", "playerBody", 10, 19, 12, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyLeft");
		ANIMATIONMANAGER->resume("bodyLeft");
		break;
	case PLAYER_RIGHT:
		//�ִϸ��̼� ������
		ANIMATIONMANAGER->addAnimation("headRight", "playerHead", arrHeadRight, 1, 1, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headRight");
		ANIMATIONMANAGER->stop("headRight");
		ANIMATIONMANAGER->addAnimation("bodyRight", "playerBody", 30, 39, 12, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyRight");
		ANIMATIONMANAGER->resume("bodyRight");
		break;
	case PLAYER_UP:
		//�ִϸ��̼� ������
		ANIMATIONMANAGER->addAnimation("headUp", "playerHead", arrHeadUp, 1, 1, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headUp");
		ANIMATIONMANAGER->stop("headUp");
		ANIMATIONMANAGER->addAnimation("bodyUp", "playerBody", 20, 29, 12, false, true);
		aniBody = ANIMATIONMANAGER->findAnimation("bodyUp");
		ANIMATIONMANAGER->resume("bodyUp");
		break;
	case PLAYER_DOWN:
		//�ִϸ��̼� ������
		ANIMATIONMANAGER->addAnimation("headIdle", "playerHead", arrHeadIdle, 1, 1, true);
		aniHead = ANIMATIONMANAGER->findAnimation("headIdle");
		ANIMATIONMANAGER->stop("headIdle");
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
