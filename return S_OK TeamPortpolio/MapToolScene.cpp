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
	_isoX = 0;
	_isoY = 0;
	_center = 0;
	memset(_tileMap, 0, sizeof(_tileMap));

	_startX = INIT_X;
	_startY = INIT_Y;

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
	if (KEYMANAGER->isStayKeyDown('W')) { _startY += 5; }
	if (KEYMANAGER->isStayKeyDown('S')) { _startY -= 5; }
	if (KEYMANAGER->isStayKeyDown('A')) { _startX += 5; }
	if (KEYMANAGER->isStayKeyDown('D')) { _startX -= 5; }

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_isDebug = !_isDebug;
	}

	if (!SUBWIN->GetIsActive() && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		float cellX = (float)(m_ptMouse.x - _startX);

		if (cellX < 0)
		{
			cellX = (cellX) / (float)CELL_WIDTH;
		}
		else
		{
			//��ŭ �������� Ŭ���ߴ°��� ��ġȭ(�������� ����)
			cellX = cellX / (float)CELL_WIDTH;
		}
		int cellY = abs(m_ptMouse.y - _startY) / CELL_HEIGHT;
		cellY = (m_ptMouse.y < _startY) ? cellY * -1 : cellY;
		int isoX = (int)cellX;
		int isoY = (int)cellY;
		/*
		//���� x��ǥ�� 0���� ũ�� �ִ�Ÿ�ϼ� ���� �۰�
		//Y��ǥ 0���� ũ��, �ִ�Ÿ�ϼ����� ������ ������ �������
		*/
		if (isoX >= 0 && isoX < TILE_COUNT_X && isoY >= 0 && isoY < TILE_COUNT_Y)
		{
			setMap(isoX, isoY, true); // �Ÿ������ �� isoX, isoY ��ŭ 
			_isoX = isoX;
			_isoY = isoY;
		}
	}
}

void MapToolScene::render()
{
	//��ǥ ���.
	sprintf_s(str, "isoX : %d, isoY : %d",
		_isoX + 1, _isoY + 1);
	TextOut(getMemDC(), WINSIZEX - 130, 0, str, strlen(str));

	DrawTileMap();
}

// render ���ִ� �κ�
void MapToolScene::DrawTileMap() // render ���ִ� �κ�
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			int left = _startX + (i * CELL_WIDTH);
			int top = _startY + (j * CELL_HEIGHT);

			_tileMap[i][j].left = left;
			_tileMap[i][j].top = top;

			for (int z = 0; z <= _tileMap[i][j].index; z++)
			{
				if (_tileMap[i][j].tileKind[z] != TILEKIND_NONE)
				{
					switch (_tileMap[i][j].tileNum[z])
					{
					case 0:
						IMAGEMANAGER->frameRender("blocks", getMemDC(),
							_tileMap[i][j].left,
							_tileMap[i][j].top - _tileMap[i][j].height*z,
							_tileMap[i][j].tilePos[z].x,
							_tileMap[i][j].tilePos[z].y);
						break;
					case 1:
						IMAGEMANAGER->frameRender("mapTile", getMemDC(),
							_tileMap[i][j].left,
							_tileMap[i][j].top - _tileMap[i][j].height * z,
							_tileMap[i][j].tilePos[z].x,
							_tileMap[i][j].tilePos[z].y);
						break;
					case 2:
						IMAGEMANAGER->frameRender("door", getMemDC(),
							_tileMap[i][j].left,
							_tileMap[i][j].top - _tileMap[i][j].height * z,
							_tileMap[i][j].tilePos[z].x,
							_tileMap[i][j].tilePos[z].y);
						break;
					}
				}
			}

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
				//SetTextColor(getMemDC(), RGB(0, 0, 0));
				//sprintf_s(str, "(%d,%d)", i + 1, j + 1);
				//TextOut(getMemDC(),
				//	left + CELL_WIDTH / 2 - 14,
				//	top + CELL_HEIGHT / 2 - 10, str, strlen(str));
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

bool MapToolScene::IsInRhombus(int isoX, int isoY)
{
	int left = _startX + (isoX * CELL_WIDTH - CELL_WIDTH);
	int top = _startY + (isoY * CELL_HEIGHT - CELL_HEIGHT);

	float dx = (float)(m_ptMouse.x - left) / CELL_WIDTH;
	float dy = (float)(m_ptMouse.y - top) / CELL_HEIGHT;

	if (dx < CELL_WIDTH && dy < CELL_HEIGHT) return true;

	else return false;
	return false;
}

//�� �ʱ�ȭ.
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

//������Ʈ ���ִ� �κ�.
void MapToolScene::setMap(int isoX, int isoY, bool isAdd)
{
	int index = SUBWIN->GetFrameIndex();

	switch (SUBWIN->GetFrameIndex())
	{
	case 0:
	case 1:
	case 2:
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
			//	&& _tileMap[isoX][isoY].index == -1)
			//	break;

			_tileMap[isoX][isoY].index++;

			if (_tileMap[isoX][isoY].index >= TILE_MAX)
			{
				_tileMap[isoX][isoY].index = TILE_MAX - 1;
			}
			_tileMap[isoX][isoY].tileNum[_tileMap[isoX][isoY].index] = index;
			_tileMap[isoX][isoY].tileKind[_tileMap[isoX][isoY].index] = kindSelect(imageFrame.x, imageFrame.y);
			_tileMap[isoX][isoY].tilePos[_tileMap[isoX][isoY].index] = imageFrame;
		}
		else
		{
			//if (kindSelect(imageFrame.x, imageFrame.y) == TILEKIND_OBJECT)break;

			if (_tileMap[isoX][isoY].index == -1)
			{
				_tileMap[isoX][isoY].index++;

				if (_tileMap[isoX][isoY].index >= TILE_MAX)
				{
					_tileMap[isoX][isoY].index = TILE_MAX - 1;
				}
				_tileMap[isoX][isoY].tileNum[_tileMap[isoX][isoY].index] = index;
				_tileMap[isoX][isoY].tileKind[_tileMap[isoX][isoY].index] = kindSelect(imageFrame.x, imageFrame.y);
				_tileMap[isoX][isoY].tilePos[_tileMap[isoX][isoY].index] = imageFrame;
			}
		}
		break;
	case CTRL_ERASER:
		if (_tileMap[isoX][isoY].index > -1)
		{
			_tileMap[isoX][isoY].index--;
		}
		break;
	}
}

// �Ӽ����� ������
TILEKIND MapToolScene::kindSelect(int frameX, int frameY) 
{
	if (frameX == -1 && frameY == -1)return TILEKIND_NONE;

	if (SUBWIN->GetFrameIndex() == 0)
	{
		return TILEKIND_OBJECT;
	}
	if (SUBWIN->GetFrameIndex() == 1)
	{
		return TILEKIND_TERRAIN;
	}
	if (SUBWIN->GetFrameIndex() == 2)
	{
		if (frameX >= 21)return TILEKIND_NONE;
	}
	return TILEKIND_TERRAIN;
}

//�ʱ� �ε��� ���� // ������ ����.
void MapToolScene::TlieInit() // ��� �ε����� -1�� ó��
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			_tileMap[i][j].index = -1;
		}
	}
}
//�ε�
void MapToolScene::Load(int loadCount)
{
	file = CreateFile(fileName[loadCount], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileMap, sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);
	CloseHandle(file);
}
//���̺�
void MapToolScene::Save(int saveCount)
{
		file = CreateFile(fileName[saveCount], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tileMap, sizeof(TagTile) * TILE_COUNT_X * TILE_COUNT_Y, &write, NULL);
		CloseHandle(file);
}
