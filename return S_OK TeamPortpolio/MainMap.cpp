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
	IMAGEMANAGER->addFrameImage("blocks", "images/maptool/blocks.bmp",
		0, 0, 52 * 8, 52 * 9, 8, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mapTile", "images/maptool/SampleMap.bmp",
		0, 0, 52 * 17 * 4, 52 * 11 * 4, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("door", "images/maptool/doorSprite.bmp",
		0, 0, 52 * 2.5 * 8, 52 * 3 * 10, 8, 10, true, RGB(255, 0, 255));

	_locationX = 0;
	_locationY = 0;
	_center = 0;
	memset(_tileMap, 0, sizeof(_tileMap));
	
	currentX = INIT_X;
	currentY = INIT_Y;

	openDoor = false;

	moveUp = false;
	moveDown = false;
	moveRight = false;
	moveLeft = false;

	stopCamera = true;

	savePositionX = currentX;
	savePositionY = currentY;

	load(RND->getInt(10));

	return E_NOTIMPL;
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
			load(RND->getInt(10));
			count = 0;
		}
	}

	//if (KEYMANAGER->isStayKeyDown('W')) { currentY += 5; }
	//if (KEYMANAGER->isStayKeyDown('S')) { currentY -= 5; }
	//if (KEYMANAGER->isStayKeyDown('A')) { currentX += 5; }
	//if (KEYMANAGER->isStayKeyDown('D')) { currentX -= 5; }
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		openDoor = true;
	}
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		openDoor = false;
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

				if (!openDoor)
				{
					if (_tileMap[i][j].tileKind[z] == TILEKIND_CLOSE_DOOR)
					{
						COLLISIONMANAGER->PlayerToObstacleCollision(_tileMap[i][j].rect);
						COLLISIONMANAGER->EnemyToObstacleCollision(_tileMap[i][j].rect);
					}
				}
				else
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

				if (_tileMap[i][j].tileKind[z] == TILEKIND_INVISIBLE_BLOCK)
				{
					COLLISIONMANAGER->PlayerToObstacleCollision(_tileMap[i][j].rect);
					COLLISIONMANAGER->EnemyToObstacleCollision(_tileMap[i][j].rect);
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
	//ÁÂÇ¥ Ãâ·Â.
	sprintf_s(str, "locationX : %d, locationY : %d", _locationX + 1, _locationY + 1);
	TextOut(getMemDC(), WINSIZEX - 130, 0, str, strlen(str));

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
		
					if (!openDoor)
					{
						if (_tileMap[i][j].tileKind[z] == TILEKIND_CLOSE_DOOR)
						{
							Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
							HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
							FillRect(getMemDC(), &_tileMap[i][j].rect, brush);
							DeleteObject(brush);
						}
					}
					else
					{
						if (_tileMap[i][j].tileKind[z] == TILEKIND_OPEN_DOOR)
						{
							Rectangle(getMemDC(), _tileMap[i][j].rect.left, _tileMap[i][j].rect.top, _tileMap[i][j].rect.right, _tileMap[i][j].rect.bottom);
							HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
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
				}
			}
		}
	}

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
							if (openDoor)
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
							if (!openDoor)
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
					}					
				}
			}

			if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
			{

				if (_isDebug)
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
					sprintf_s(str, "(%d,%d)", i + 1, j + 1);
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
