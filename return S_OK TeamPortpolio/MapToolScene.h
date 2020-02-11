#pragma once
#include"gameNode.h"
#include"MapToolTile.h"
class MapToolScene : public gameNode
{
private:

	TagTile _tileMap[TILE_COUNT_X][TILE_COUNT_Y];

	int _isoX, _isoY;
	int _center;
	char str[128];


	int _startX;
	int _startY;

	POINT imageFrame;
	CTRL _currentCTRL;

	bool _isDebug;

	//
	const char* fileName;
	HANDLE file;
	DWORD write;
	DWORD read;
	
public:
	MapToolScene();
	~MapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();

	//Ÿ�ϸ� �׸���.
	void DrawTileMap();

	//���� �׷��ֱ�
	void Draw_Line_X(int left, int top);
	void Draw_Line_Y(int left, int top);

	//������ �ȿ� ����?
	bool IsInRhombus(int isoX, int isoY);

	void MapToolSetup();
	void setMap(int isoX, int isoY, bool isAdd);
	TILEKIND kindSelect(int frameX, int frameY);


	void TlieInit();
	void Load();
	void Save();
};

