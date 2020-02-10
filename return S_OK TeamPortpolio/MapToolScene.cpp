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

	if (!SUBWIN->GetIsActive() && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		float cellX = (float)(m_ptMouse.x - _startX);

		if (cellX < 0)
		{
			cellX = (cellX) / (float)CELL_WIDTH;
		}
		else
		{
			//얼만큼 떨어져서 클릭했는가를 수치화(가로지름 기준)
			cellX = cellX / (float)CELL_WIDTH;
		}
		int cellY = abs(m_ptMouse.y - _startY) / CELL_HEIGHT;
		cellY = (m_ptMouse.y < _startY) ? cellY * -1 : cellY;
		int isoX = (int)cellX;
		int isoY = (int)cellY;
		/*
		//만약 x좌표가 0보다 크고 최대타일수 보다 작고
		//Y좌표 0보다 크고, 최대타일수보다 작으면 검출대상에 집어넣자
		*/
		if (isoX >= 0 && isoX < TILE_COUNT_X && isoY >= 0 && isoY < TILE_COUNT_Y)
		{

			setMap(isoX, isoY, false);
			_isoX = isoX;
			_isoY = isoY;
		}
	}


}

void MapToolScene::render()
{
	sprintf_s(str, "isoX : %d, isoY : %d",
		_isoX + 1, _isoY + 1);
	TextOut(getMemDC(), WINSIZEX - 130, 0, str, strlen(str));

	DrawTileMap();
}

void MapToolScene::DrawTileMap()
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
						IMAGEMANAGER->frameRender("tile", getMemDC(),
							_tileMap[i][j].left,
							_tileMap[i][j].top - _tileMap[i][j].height*z,
							_tileMap[i][j].tilePos[z].x,
							_tileMap[i][j].tilePos[z].y);
						break;
					case 1:
					case 2:
						IMAGEMANAGER->frameRender("tile2", getMemDC(),
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
	// lefttop
	int left = _startX + (isoX * CELL_WIDTH - CELL_WIDTH);
	int top = _startY + (isoY * CELL_HEIGHT - CELL_HEIGHT);

	//left 에서 마우스값을 뺀값(left에서 이동거리)를
	//left와 중점폭으로 top과 중점을 길이로 하는 작은 사각형으로 
	//비례하기 위해 dx와 dy를 구한다.
	float dx = (float)(m_ptMouse.x - left) / CELL_WIDTH;
	float dy = (float)(m_ptMouse.y - top) / CELL_HEIGHT;

	//만약 전체 비례즁에서 정삼각형 안에 들어가야 하기 때문에
	//무조건 dy가 dx보다 같거나 작을 수 밖에 없다.
	//정삼각형 안에 들어가 잇는 점은 무조건 y가 x보다 작거나 
	//같을 수 밖에 없다.

	//1뺴주는 이유는 top에서부터 차이를 계산 했기 떄무에
	//바텀에서부터의 값을 구하기 위함
	if (dx < CELL_WIDTH && dy < CELL_HEIGHT) return true;
	//정삼각형 밖에 있다면 
	else return false;
	// righttop
	return false;
}

void MapToolScene::MapToolSetup()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			_tileMap[i][j].index = -1;
			_tileMap[i][j].height = 5;
		}
	}
}

void MapToolScene::setMap(int isoX, int isoY, bool isAdd)
{
	int index = SUBWIN->GetFrameIndex();

	switch (SUBWIN->GetFrameIndex())
	{
	case 0:
		imageFrame = SUBWIN->GetFramePoint();
		break;
	case 1:
		imageFrame.x = SUBWIN->GetFramePoint().y;
		imageFrame.y = SUBWIN->GetFramePoint().x;
		break;
	case 2:
		if (SUBWIN->GetFramePoint().y < 5)
		{
			imageFrame.x = SUBWIN->GetFramePoint().x + 10;
			imageFrame.y = SUBWIN->GetFramePoint().y;
		}
		else
		{
			imageFrame.x = SUBWIN->GetFramePoint().x + 16;
			imageFrame.y = SUBWIN->GetFramePoint().y - 5;
		}
		break;
	}
	_currentCTRL = SUBWIN->GetCTRL();

	switch (_currentCTRL)
	{
	case CTRL_DRAW:
		if (isAdd)
		{
			if (kindSelect(imageFrame.x, imageFrame.y) == TILEKIND_OBJECT
				&& _tileMap[isoX][isoY].index == -1)
				break;

			_tileMap[isoX][isoY].index++;
			if (_tileMap[isoX][isoY].index >= TILE_MAX) _tileMap[isoX][isoY].index = TILE_MAX - 1;
			_tileMap[isoX][isoY].tileNum[_tileMap[isoX][isoY].index] = index;
			_tileMap[isoX][isoY].tileKind[_tileMap[isoX][isoY].index] = kindSelect(imageFrame.x, imageFrame.y);
			_tileMap[isoX][isoY].tilePos[_tileMap[isoX][isoY].index] = imageFrame;
		}
		else
		{
			if (kindSelect(imageFrame.x, imageFrame.y) == TILEKIND_OBJECT)break;

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

TILEKIND MapToolScene::kindSelect(int frameX, int frameY)
{
	if (frameX == -1 && frameY == -1)return TILEKIND_NONE;


	if (SUBWIN->GetFrameIndex() == 0)
	{
		//if (frameY >= 7)return TILEKIND_NONE;
		if (frameY <= 9)return TILEKIND_TERRAIN;
		else return TILEKIND_OBJECT;
	}
	if (SUBWIN->GetFrameIndex() == 2)
	{
		if (frameX >= 21)return TILEKIND_NONE;
	}
	return TILEKIND_TERRAIN;
}

void MapToolScene::TlieInit()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			_tileMap[i][j].index = -1;
		}
	}
}

void MapToolScene::Load()
{

}

void MapToolScene::Save()
{

}
