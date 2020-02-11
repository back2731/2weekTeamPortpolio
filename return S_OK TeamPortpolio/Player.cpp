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

	player.playerHeadRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 32 * 2, 23 * 2);			//�Ӹ� ����
	player.playerBodyRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 30, 32 * 2, 11 * 2);	//�� ����
	player.playerShotSpeed = 8.0f;																//���ݼӵ�
	player.playerShotRange = 450.0f;															//���ݻ�Ÿ�
	player.playerShotDelay = 25;																//�����ֱ�
	player.playerSpeed = 5.0f;																	//�̵��ӵ�
	player.playerSlideSpeed = 3.0f;																//�����̵� �ӵ�
	playerBulletInterval = 0;

	//�÷��̾� ���� ���� �ʱ�ȭ
	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;
	//�÷��̾� �����̵� ���� �ʱ�ȭ
	slideLeft = false;
	slideRight = false;
	slideUp = false;
	slideDown = false;
	//�÷��̾� �밢 �����̵� ���� �ʱ�ȭ
	slideLeftUp = false;
	slideLeftDown = false;
	slideRightUp = false;
	slideRightDown = false;
	//�÷��̾� ���� ���� �ʱ�ȭ
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

	//�ִϸ��̼� ������
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
	//����
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
	//������
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
	//��
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
	//�Ʒ�
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

	PlayerSilde();	//�÷��̾� �����̵�

	//�÷��̾� �ǰ� ����
	player.playerHitRect = RectMakeCenter(player.playerBodyRect.left + (player.playerBodyRect.right - player.playerBodyRect.left) / 2,
		player.playerBodyRect.top - 10, 60, 65);
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

		if (player.playerSlideSpeed < 1.2f)
		{
			player.playerSlideSpeed = 3.0f;
			isLeft = false;
			slideLeft = false;
		}
	}

	//������ �����̵�
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

	//���� �����̵�
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

	//�Ʒ��� �����̵�
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

	//������ �����̵�
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

	//���ʾƷ� �����̵�
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

	//�������� �����̵�
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

	//�����ʾƷ� �����̵�
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
	//���� �Ѿ� �߻�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		playerLeftShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		playerLeftShot = false;
	}

	//������ �Ѿ� �߻�
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		playerRightShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		playerRightShot = false;
	}

	//���� �Ѿ� �߻�
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		playerUpShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		playerUpShot = false;
	}

	//�Ʒ��� �Ѿ� �߻�
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		playerDownShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		playerDownShot = false;
	}

	PlayerShotMove();	//�÷��̾� ���� ����
}

void Player::PlayerShotMove()
{
	//�ҷ� ����
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

	//�ҷ� ����
	BULLETMANAGER->PlayerMoveBullet(vPlayerBullet, viPlayerBullet);
}