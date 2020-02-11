#pragma once
//크기
#define CELL_WIDTH 52
#define CELL_HEIGHT 52

//초기좌표
#define INIT_X 50
#define INIT_Y 50
//타일 갯수
#define TILE_COUNT_X 85
#define TILE_COUNT_Y 55

//타일 이미지
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
	TILEKIND tileKind[TILE_MAX]; // 오브젝트, 타일 구분.
	POINT tilePos[TILE_MAX]; // 샘플타일에서 골라진녀석

	int height;
};