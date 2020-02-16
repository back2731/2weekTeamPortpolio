#include "stdafx.h"
#include "MainMap.h"

MainMap::MainMap()
{
}

MainMap::~MainMap()
{
}

HRESULT MainMap::init()
{
	_locationX = 0;
	_locationY = 0;
	_center = 0;
	memset(_tileMap, 0, sizeof(_tileMap));
	
	currentX = INIT_X;
	currentY = INIT_Y;

	openDoor = true;

	moveUp = false;
	moveDown = false;
	moveRight = false;
	moveLeft = false;

	stopCamera = true;

	savePositionX = currentX;
	savePositionY = currentY;

	loadData = 0;
	load(loadData);

	// 맵 데이터에 따라서 각 방의 위치의 bool 값을 지정해준다.
	switch (loadData)
	{
	case 0:
	{
		for (int i = 0; i < ROOM_MAX_X; i++)
		{
			for (int j = 0; j < ROOM_MAX_Y; j++)
			{
				isCheckClear[i][j] = false;
				isSummonEnemy[i][j] = false;

				isBoss[i][j] = false;
				isShop[i][j] = false;
				isGoldRoom[i][j] = false;
			}
		}
		isBoss[1][2] = true;
		isShop[2][1] = true;
		isGoldRoom[2][3] = true;

		// 초기시작위치에서 적이 소환되지 않게 해주는 부분
		isSummonEnemy[2][2] = true;
	}
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}

	return S_OK;
}

void MainMap::release()
{
}

void MainMap::update()
{
	if (KEYMANAGER->isStayKeyDown('U'))
	{
		count++;
		if (count == 60)
		{
			resetData = RND->getInt(10);
			loadData = resetData;
			ENEMYMANAGER->Init();
			PLAYERMANAGER->Init();
			load(loadData);
			count = 0;
		}
	}

	ENEMYMANAGER->GetLoadData(loadData);

	// 해당 방에 입장 했을 때
	for (int i = 0; i < ROOM_MAX_X; i++)
	{
		for (int j = 0; j < ROOM_MAX_Y; j++)
		{
			if (isSummonEnemy[i][j] == false)
			{
				if (savePositionX == (j * -884) && savePositionY == (i * -572))
				{
					isCheckClear[i][j] = true;
					ENEMYMANAGER->GetCheckClear(isCheckClear[i][j]);
				}
			}
		}
	}

	// 보스방에 입장 했을 때
	switch (loadData)
	{
		case 0:
		{	
			// 보스방에 입장 했을 시의 bool값
			if (isCheckClear[1][2] == true && isBoss[1][2] == true && isSummonEnemy[1][2] == false)
			{
				isBoss[1][2] = false;
				isSummonEnemy[1][2] = true;
				ENEMYMANAGER->GetBoss(isBoss[1][2]);
				ENEMYMANAGER->GetSummonEnemy(isSummonEnemy[1][2]);
			}
		}
			break;
	}

	// 일반방에 입장 했을 때
	switch (loadData)
	{
		case 0:
		{
			for (int i = 0; i < ROOM_MAX_X; i++)
			{
				for (int j = 0; j < ROOM_MAX_Y; j++)
				{
					// isCheckClear -> 방에 입장했다면 true / isSummonEnemy -> 몬스터를 소환한 적이 없다면 false / 보스방이아니라면 false / 상점이 아니라면 false / 황금방이 아니라면 false
					if (isCheckClear[i][j] == true && isSummonEnemy[i][j] == false && isBoss[i][j] == false && isShop[i][j] == false && isGoldRoom[i][j] == false)
					{
						// 몬스터를 소환했다면 true
						isSummonEnemy[i][j] = true;
						ENEMYMANAGER->GetSummonEnemy(isSummonEnemy[i][j]);
					}
				}
			}
		}
			break;
	}

	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			for (int z = 0; z < TILE_MAX; z++)
			{
				if (_tileMap[i][j].tileKind[z] == TILEKIND_OBJECT)
				{
					if (stopCamera)
					{
						COLLISIONMANAGER->PlayerToObstacleCollision(_tileMap[i][j].rect);
						COLLISIONMANAGER->EnemyToObstacleCollision(_tileMap[i][j].rect);
					}
				}

				if (ENEMYMANAGER->SetOpenDoor())
				{
					if (_tileMap[i][j].tileKind[z] == TILEKIND_OPEN_DOOR)
					{
						if (stopCamera)
						{
							if (COLLISIONMANAGER->PlayerCollisionNextDoor(_tileMap[i][j].rect) == 3)
							{
								PLAYERMANAGER->SetPlayerRectY(340);
								moveUp = true;
								stopCamera = false;
							}

							else if (COLLISIONMANAGER->PlayerCollisionNextDoor(_tileMap[i][j].rect) == 4)
							{
								PLAYERMANAGER->SetPlayerRectY(-340);
								moveDown = true;
								stopCamera = false;
							}

							else if (COLLISIONMANAGER->PlayerCollisionNextDoor(_tileMap[i][j].rect) == 1)
							{
								PLAYERMANAGER->SetPlayerRectX(620);
								moveLeft = true;
								stopCamera = false;
							}
							else if (COLLISIONMANAGER->PlayerCollisionNextDoor(_tileMap[i][j].rect) == 2)
							{
								PLAYERMANAGER->SetPlayerRectX(-620);
								moveRight = true;
								stopCamera = false;
							}
						}
					}
				}				
				else
				{
					if (_tileMap[i][j].tileKind[z] == TILEKIND_CLOSE_DOOR)
					{
						COLLISIONMANAGER->PlayerToObstacleCollision(_tileMap[i][j].rect);
						COLLISIONMANAGER->EnemyToObstacleCollision(_tileMap[i][j].rect);
					}
				}

				if (_tileMap[i][j].tileKind[z] == TILEKIND_INVISIBLE_BLOCK)
				{
					COLLISIONMANAGER->PlayerToObstacleCollision(_tileMap[i][j].rect);
					//COLLISIONMANAGER->EnemyToObstacleCollision(_tileMap[i][j].rect);
				}

				if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMHEART)
				{
					if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &_tileMap[i][j].rect))
					{
						PLAYERMANAGER->SetPlayerHp(1.0f);
						_tileMap[i][j].tileNum[z] = 0;
						_tileMap[i][j].tileKind[z] = TILEKIND_NONE;
						_tileMap[i][j].tilePos[z] = { 0 };
					}
				}

				if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMGOLD)
				{
					if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &_tileMap[i][j].rect))
					{
						PLAYERMANAGER->SetPlayerGold(1);
						_tileMap[i][j].tileNum[z] = 0;
						_tileMap[i][j].tileKind[z] = TILEKIND_NONE;
						_tileMap[i][j].tilePos[z] = { 0 };
					}
				}

				if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMBOMB)
				{
					if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &_tileMap[i][j].rect))
					{
						PLAYERMANAGER->SetPlayerBomb(1);
						_tileMap[i][j].tileNum[z] = 0;
						_tileMap[i][j].tileKind[z] = TILEKIND_NONE;
						_tileMap[i][j].tilePos[z] = { 0 };
					}
				}

				if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMKEY)
				{
					if (IntersectRect(&temp, &PLAYERMANAGER->GetPlayerHitRect(), &_tileMap[i][j].rect))
					{
						PLAYERMANAGER->SetPlayerKey(1);
						_tileMap[i][j].tileNum[z] = 0;
						_tileMap[i][j].tileKind[z] = TILEKIND_NONE;
						_tileMap[i][j].tilePos[z] = { 0 };
					}
				}
			}
		}
	}

	if (!stopCamera)
	{
		if (moveUp)
		{
			currentY += 60;

			if (currentY >= savePositionY + WINSIZEY)
			{
				currentY = savePositionY + WINSIZEY;
				savePositionY = currentY;
				moveUp = false;								
				stopCamera = true;
			}
		}
		if (moveDown)
		{
			currentY -= 60;

			if (currentY <= savePositionY - WINSIZEY)
			{
				currentY = savePositionY - WINSIZEY;
				savePositionY = currentY;
				moveDown = false;
				stopCamera = true;
			}
		}
		else if (moveLeft)
		{
			currentX += 100;
			
			if (currentX >= savePositionX + WINSIZEX)
			{
				currentX = savePositionX + WINSIZEX;
				savePositionX = currentX;
				moveLeft = false;
				stopCamera = true;
			}
		}
		else if (moveRight)
		{
			currentX -= 100;

			if (currentX <= savePositionX - WINSIZEX)
			{
				currentX = savePositionX - WINSIZEX;
				savePositionX = currentX;
				moveRight = false;
				stopCamera = true;
			}
		}
	}
}

void MainMap::render()
{
	DrawTileMap();

	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			for (int z = 0; z < TILE_MAX; z++)
			{
				if (KEYMANAGER->isToggleKey(VK_TAB))
				{
					if (_tileMap[i][j].tileKind[z] == TILEKIND_OBJECT)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);

						HBRUSH brush = CreateSolidBrush(RGB(204, 0, 102));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (ENEMYMANAGER->SetOpenDoor())
					{
						if (_tileMap[i][j].tileKind[z] == TILEKIND_OPEN_DOOR)
						{
							Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
							HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
							FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
							DeleteObject(brush);
						}
					}
					else	
					{
						if (_tileMap[i][j].tileKind[z] == TILEKIND_CLOSE_DOOR)
						{
							Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
							HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
							FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
							DeleteObject(brush);
						}
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_INVISIBLE_BLOCK)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMPOINT)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(51, 0, 51));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMHEART)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(204, 204, 102));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMGOLD)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(51, 102, 0));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMBOMB)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(204, 255, 204));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMATTACKBOMB)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(204, 100, 204));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMKEY)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMPILL)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(0, 102, 153));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_ITEMCARD)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(0, 51, 102));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_BLACKITEMBOXOPEN)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(153, 255, 203));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_BLACKITEMBOXCLOSE)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(0, 102, 0));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_GOLDITEMBOXOPEN)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(153, 51, 102));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_GOLDITEMBOXCLOSE)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(153, 153, 204));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_REDITEMBOXOPEN)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(153, 0, 102));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_REDITEMBOXCLOSE)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(255, 204, 153));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_CRACKEDITEMBOXOPEN)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(51, 0, 255));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}

					if (_tileMap[i][j].tileKind[z] == TILEKIND_CRACKEDITEMBOXCLOSE)
					{
						Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
						HBRUSH brush = CreateSolidBrush(RGB(204, 204, 204));
						FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
						DeleteObject(brush);
					}
				}
			}
		}
	}
	sprintf_s((str), "x : %d", savePositionX);
	TextOut(getMemDC(), 100, 100, str, strlen(str));

	sprintf_s((str), "y : %d", savePositionY);
	TextOut(getMemDC(), 100, 120, str, strlen(str));
}

void MainMap::DrawTileMap()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			int left = currentX + (i * CELL_WIDTH);
			int top = currentY + (j * CELL_HEIGHT);
			int right = currentX + (i * CELL_WIDTH) + CELL_WIDTH;
			int bottom = currentY + (j * CELL_HEIGHT) + CELL_HEIGHT;

			_tileMap[i][j].left = left;
			_tileMap[i][j].top = top;
			_tileMap[i][j].right = right;
			_tileMap[i][j].bottom = bottom;

			_tileMap[i][j].rect = { _tileMap[i][j].left , _tileMap[i][j].top , _tileMap[i][j].right , _tileMap[i][j].bottom };


			for (int z = 0; z <= _tileMap[i][j].index; z++)
			{
				if (_tileMap[i][j].tileKind[z] != TILEKIND_NONE)
				{
					switch (_tileMap[i][j].tileKind[z])
					{
					case TILEKIND_TERRAIN:
						IMAGEMANAGER->frameRender("mapTile", getMemDC(),
							_tileMap[i][j].left,
							_tileMap[i][j].top - _tileMap[i][j].height*z,
							_tileMap[i][j].tilePos[z].x,
							_tileMap[i][j].tilePos[z].y);
						break;
					case TILEKIND_OBJECT:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_OPEN_DOOR:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							if (ENEMYMANAGER->SetOpenDoor())
							{
								if (_tileMap[i][j].tilePos[z].x % 2 == 1 && _tileMap[i][j].tilePos[z].y % 2 == 0)
								{
									IMAGEMANAGER->frameRender("door", getMemDC(),
										_tileMap[i][j].left - 50,
										_tileMap[i][j].top - _tileMap[i][j].height * z - 26,
										_tileMap[i][j].tilePos[z].x,
										_tileMap[i][j].tilePos[z].y);
									break;
								}
								IMAGEMANAGER->frameRender("door", getMemDC(),
									_tileMap[i][j].left - 26,
									_tileMap[i][j].top - _tileMap[i][j].height * z - 26,
									_tileMap[i][j].tilePos[z].x,
									_tileMap[i][j].tilePos[z].y);
								break;
							}
						}
						break;
					case TILEKIND_CLOSE_DOOR:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							if (!ENEMYMANAGER->SetOpenDoor())
							{
								if (_tileMap[i][j].tilePos[z].x % 2 == 1 && _tileMap[i][j].tilePos[z].y % 2 == 0)
								{
									IMAGEMANAGER->frameRender("door", getMemDC(),
										_tileMap[i][j].left - 50,
										_tileMap[i][j].top - _tileMap[i][j].height * z - 26,
										_tileMap[i][j].tilePos[z].x,
										_tileMap[i][j].tilePos[z].y);
									break;
								}
								IMAGEMANAGER->frameRender("door", getMemDC(),
									_tileMap[i][j].left - 26,
									_tileMap[i][j].top - _tileMap[i][j].height * z - 26,
									_tileMap[i][j].tilePos[z].x,
									_tileMap[i][j].tilePos[z].y);
								break;
							}
						}
						break;
					case TILEKIND_ITEMPOINT:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_ITEMHEART:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_ITEMGOLD:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_ITEMBOMB:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_ITEMATTACKBOMB:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_ITEMKEY:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_ITEMPILL:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_ITEMCARD:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_BLACKITEMBOXOPEN:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_BLACKITEMBOXCLOSE:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_GOLDITEMBOXOPEN:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_GOLDITEMBOXCLOSE:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_REDITEMBOXOPEN:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_REDITEMBOXCLOSE:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_CRACKEDITEMBOXOPEN:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					case TILEKIND_CRACKEDITEMBOXCLOSE:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
						{
							IMAGEMANAGER->frameRender("blocks", getMemDC(),
								_tileMap[i][j].left,
								_tileMap[i][j].top - _tileMap[i][j].height * z,
								_tileMap[i][j].tilePos[z].x,
								_tileMap[i][j].tilePos[z].y);
							break;
						}
						break;
					}

				}
			}

			if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
			{

				if (KEYMANAGER->isToggleKey(VK_TAB))
				{
					if (j % 11 == 0)
					{
						Draw_Line_X(left, top);
					}
					if (i % 17 == 0)
					{
						Draw_Line_Y(left, top);
					}

					if (j % 1 == 0)
					{
						Draw_Line_X(left, top);
					}
					if (i % 1 == 0)
					{
						Draw_Line_Y(left, top);
					}
					SetTextColor(getMemDC(), RGB(255, 0, 0));
					sprintf_s(str, "(%d,%d)", i, j);
					TextOut(getMemDC(),
						left + CELL_WIDTH / 2 - 20,
						top + CELL_HEIGHT / 2 - 10, str, strlen(str));
				}
			}
		}
	}
}

void MainMap::load(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}

void MainMap::Draw_Line_X(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(getMemDC(), centerX, centerY, centerX + CELL_WIDTH, centerY);
}

void MainMap::Draw_Line_Y(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(getMemDC(), centerX, centerY, centerX, centerY + CELL_HEIGHT);
}
