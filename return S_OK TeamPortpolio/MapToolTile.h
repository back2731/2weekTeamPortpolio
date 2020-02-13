#pragma once
//ũ��
#define CELL_WIDTH 52
#define CELL_HEIGHT 52

//�ʱ���ǥ
#define INIT_X -1768
#define INIT_Y -1144
//Ÿ�� ����
#define TILE_COUNT_X 85
#define TILE_COUNT_Y 55

//Ÿ�� �̹���
#define TILE_SIZE_X 8
#define TILE_SIZE_Y 10


#define TILE_MAX 3

enum TILEKIND
{
	TILEKIND_TERRAIN = 5,
	TILEKIND_OBJECT,
	TILEKIND_OBJECT_BUMB,
	TILEKIND_OBJECT_BULLET,
	TILEKIND_OPEN_DOOR,
	TILEKIND_CLOSE_DOOR,
	TILEKIND_ITEM_POINT,
	TILEKIND_ROOM_INFO,
	TILEKIND_NONE
};

struct TagTile
{
	int left, top, right, bottom; // x, y ��(rect�� left, top)

	RECT rect;

	int index; // ���ΰ�. tileNum, tileKind, tilePos ���� ���.

	int tileNum[TILE_MAX]; // ����Ÿ�� �ε���(���õ� â) index�� �����ͼ� ����.
	TILEKIND tileKind[TILE_MAX]; // ������Ʈ, Ÿ�� ����.
	POINT tilePos[TILE_MAX]; // ����Ÿ�Ͽ��� ������༮(frameX, frameY)


	int height; // ���ϼ��� Ŀ���� ����
};
