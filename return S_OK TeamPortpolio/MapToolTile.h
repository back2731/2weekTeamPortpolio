#pragma once
//ũ��
#define CELL_WIDTH 52
#define CELL_HEIGHT 52

//�ʱ���ǥ
#define INIT_X 50
#define INIT_Y 50
//Ÿ�� ����
#define TILE_COUNT_X 85
#define TILE_COUNT_Y 55

//Ÿ�� �̹���
#define TILE_SIZE_X 8
#define TILE_SIZE_Y 10

#define TILE_MAX 1

enum TILEKIND
{
	TILEKIND_OBJECT,
	TILEKIND_TERRAIN,
	TILEKIND_NONE
};

struct TagTile
{
	int left, top;

	int index;

	int tileNum[TILE_MAX]; // 
	TILEKIND tileKind[TILE_MAX]; // ������Ʈ, Ÿ�� ����.
	POINT tilePos[TILE_MAX]; // ����Ÿ�Ͽ��� ������༮

	int height;
};