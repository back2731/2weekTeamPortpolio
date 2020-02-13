#pragma once
#include"gameNode.h"
#include"MapToolTile.h"
class MainMap : public gameNode
{
private:
	TagTile _tileMap[TILE_COUNT_X][TILE_COUNT_Y];

	int _locationX, _locationY;
	int _center;
	char str[128];

	int count = 0;

	int _startX;
	int _startY;

	POINT imageFrame;
	CTRL _currentCTRL;
	RECT cameraRect = { 0,0,WINSIZEX,WINSIZEY };
	RECT temp;

	bool _isDebug;

	//
	const char* fileName[10] = { "map1.map","map2.map","map3.map","map4.map","map5.map","map6.map","map7.map","map8.map","map9.map","map10.map" };
	HANDLE file;
	DWORD write;
	DWORD read;

public:
	MainMap();
	~MainMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void DrawTileMap();
	void load(int loadCount);

	void Draw_Line_X(int left, int top);
	void Draw_Line_Y(int left, int top);

	//DWORD* getAttribute() { return _attribute; }
	//tagTile* getMap() { return _map; }
	//int getPosFirst() { return _pos[0]; }
	//int getPosSecond() { return _pos[1]; }
	//void attackBlock(int tileN);
};

