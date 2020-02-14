#include "stdafx.h"
#include "MapToolScene.h"


MapToolScene::MapToolScene()
{
}


MapToolScene::~MapToolScene()
{
}

HRESULT MapToolScene::init()
{
	// 서브윈도우 선언, 씬 추가
	SCENEMANAGER->addScene("SubMap", sub);

	// 서브윈도우 초기화
	#ifdef SUBWINOPEN
		SUBWIN->init();
	#endif // SUBWINOPEN

	// 서브윈도우 세팅
	#ifdef SUBWINOPEN
		SUBWIN->SetScene(sub);
	#endif // SUBWINOPEN

	_locationX = 0;
	_locationY = 0;
	_center = 0;
	memset(_tileMap, 0, sizeof(_tileMap));

	currentX = INIT_X;
	currentY = INIT_Y;

	_isDebug = true;
	_currentCTRL = CTRL_DRAW;

	MapToolSetup();

	return S_OK;
}

void MapToolScene::release()
{
}

void MapToolScene::update()
{
	// 서브윈도우 업데이트
	#ifdef SUBWINOPEN
		SUBWIN->update();
	#endif // SUBWINOPEN

	if (KEYMANAGER->isStayKeyDown('W')) { currentY += 5; }
	if (KEYMANAGER->isStayKeyDown('S')) { currentY -= 5; }
	if (KEYMANAGER->isStayKeyDown('A')) { currentX += 5; }
	if (KEYMANAGER->isStayKeyDown('D')) { currentX -= 5; }

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_isDebug = !_isDebug;
	}

	if (!SUBWIN->GetIsActive() && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		float cellX = (float)(m_ptMouse.x - currentX);

		if (cellX < 0)
		{
			cellX = cellX / (float)CELL_WIDTH;
		}
		else
		{
			//얼만큼 떨어져서 클릭했는가를 수치화(가로지름 기준)
			cellX = cellX / (float)CELL_WIDTH;
		}
		int cellY = abs(m_ptMouse.y - currentY) / CELL_HEIGHT;
		cellY = (m_ptMouse.y < currentY) ? cellY * -1 : cellY;
		int locationX = (int)cellX;
		int locationY = (int)cellY;
		/*
		//만약 x좌표가 0보다 크고 최대타일수 보다 작고
		//Y좌표 0보다 크고, 최대타일수보다 작으면 검출대상에 집어넣자
		*/
		if (locationX >= 0 && locationX < TILE_COUNT_X && locationY >= 0 && locationY < TILE_COUNT_Y)
		{
			setMap(locationX, locationY, true); // 거리계산이 된 locationX, locationY 만큼 
			_locationX = locationX;
			_locationY = locationY;
		}
	}
}

void MapToolScene::render()
{
	// 서브윈도우 랜더링
	#ifdef SUBWINOPEN
		SUBWIN->render();
	#endif // SUBWINOPEN

	//좌표 출력.
	sprintf_s(str, "X : %d, Y : %d",
		_locationX + 1, _locationY + 1);
	TextOut(getMemDC(), WINSIZEX - 100, 0, str, strlen(str));

	DrawTileMap();
}

void MapToolScene::SetSubWindow()
{	
	MapToolSetup();
}

// render 해주는 부분
void MapToolScene::DrawTileMap() 
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
					case TILEKIND_OBJECT_NEXTROOM:
						IMAGEMANAGER->frameRender("blocks", getMemDC(),
							_tileMap[i][j].left,
							_tileMap[i][j].top - _tileMap[i][j].height*z,
							_tileMap[i][j].tilePos[z].x,
							_tileMap[i][j].tilePos[z].y);
						break;
					case TILEKIND_OPEN_DOOR:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
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
						break;
					case TILEKIND_CLOSE_DOOR:
						if (IntersectRect(&temp, &cameraRect, &_tileMap[i][j].rect))
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

void MapToolScene::Draw_Line_X(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(getMemDC(), centerX, centerY, centerX + CELL_WIDTH, centerY);
}
void MapToolScene::Draw_Line_Y(int left, int top)
{
	int centerX = left;
	int centerY = top;

	LineMake(getMemDC(), centerX, centerY, centerX, centerY + CELL_HEIGHT);
}

//맵 초기화.
void MapToolScene::MapToolSetup()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			_tileMap[i][j].index = -1;
			_tileMap[i][j].height = 0;
		}
	}
}

//업데이트 해주는 부분.
void MapToolScene::setMap(int locationX, int locationY, bool isAdd)
{
	int index = SUBWIN->GetFrameIndex();

	switch (SUBWIN->GetFrameIndex())
	{
	case TILEKIND_NONE:
	case TILEKIND_TERRAIN:
	case TILEKIND_OBJECT:
	case TILEKIND_OBJECT_NEXTROOM:
	case TILEKIND_OPEN_DOOR:
	case TILEKIND_CLOSE_DOOR:
		imageFrame = SUBWIN->GetFramePoint();
		break;
	}
	_currentCTRL = SUBWIN->GetCTRL();

	switch (_currentCTRL)
	{
	case CTRL_DRAW:
		if (isAdd)
		{
			//if (kindSelect(imageFrame.x, imageFrame.y) == TILEKIND_OBJECT
			//	&& _tileMap[locationX][locationY].index == -1)
			//	break;

			_tileMap[locationX][locationY].index++;

			if (_tileMap[locationX][locationY].index >= TILE_MAX)
			{
				_tileMap[locationX][locationY].index = TILE_MAX - 1;
			}
			_tileMap[locationX][locationY].tileNum[_tileMap[locationX][locationY].index] = index;
			_tileMap[locationX][locationY].tileKind[_tileMap[locationX][locationY].index] = kindSelect(imageFrame.x, imageFrame.y);
			_tileMap[locationX][locationY].tilePos[_tileMap[locationX][locationY].index] = imageFrame;
		}
		else
		{
			//if (kindSelect(imageFrame.x, imageFrame.y) == TILEKIND_OBJECT)break;

			if (_tileMap[locationX][locationY].index == -1)
			{
				//_tileMap[locationX][locationY].index++;

				if (_tileMap[locationX][locationY].index >= TILE_MAX)
				{
					_tileMap[locationX][locationY].index = TILE_MAX - 1;
				}
				_tileMap[locationX][locationY].tileNum[_tileMap[locationX][locationY].index] = index;
				_tileMap[locationX][locationY].tileKind[_tileMap[locationX][locationY].index] = kindSelect(imageFrame.x, imageFrame.y);
				_tileMap[locationX][locationY].tilePos[_tileMap[locationX][locationY].index] = imageFrame;
			}
		}
		break;
	case CTRL_ERASER:
		if (_tileMap[locationX][locationY].index > -1)
		{
			_tileMap[locationX][locationY].tileNum[_tileMap[locationX][locationY].index] = { 0, };
			_tileMap[locationX][locationY].tileKind[_tileMap[locationX][locationY].index] = kindSelect(-1, -1);
			_tileMap[locationX][locationY].tilePos[_tileMap[locationX][locationY].index] = imageFrame;
		}
		break;
	}
}

// 속성종류 정해줌
TILEKIND MapToolScene::kindSelect(int frameX, int frameY)
{
	if (frameX == -1 && frameY == -1)
	{
		return TILEKIND_NONE;
	}

	if (SUBWIN->GetFrameIndex() == CTRL_NUM1)
	{
		return TILEKIND_TERRAIN;
	}
	if (SUBWIN->GetFrameIndex() == CTRL_NUM2)
	{
		if (frameY >= 0 && frameY <= 3)
		{
			return TILEKIND_OBJECT;
		}
		if (frameY == 4)
		{
			return TILEKIND_OBJECT_NEXTROOM;
		}
	}
	if (SUBWIN->GetFrameIndex() == CTRL_NUM3)
	{
		if (frameX == 0 || frameX == 1 || frameX == 4 || frameX == 5)
		{
			return TILEKIND_OPEN_DOOR;
		}
		else if (frameX == 2 || frameX == 3 || frameX == 6 || frameX == 7)
		{
			return TILEKIND_CLOSE_DOOR;
		}
	}
	return TILEKIND_NONE;

}

//초기 인덱스 지정 // 사용되지 않음.
void MapToolScene::TlieInit() // 모든 인덱스를 -1로 처리
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			_tileMap[i][j].index = -1;
		}
	}
}
//로드
void MapToolScene::Load(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);
	CloseHandle(file);
}
//세이브
void MapToolScene::Save(int saveCount)
{
	file = CreateFile(fileName[saveCount], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tileMap, sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y, &write, NULL);
	CloseHandle(file);
}
