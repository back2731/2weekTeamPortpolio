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

	//타일맵 그리자.
	void DrawTileMap();

	//라인 그려주기
	void Draw_Line_X(int left, int top);
	void Draw_Line_Y(int left, int top);

	//마름모 안에 있음?
	bool IsInRhombus(int isoX, int isoY);

	void MapToolSetup();
	void setMap(int isoX, int isoY, bool isAdd);
	TILEKIND kindSelect(int frameX, int frameY);


	void TlieInit();
	void Load();
	void Save();
};

