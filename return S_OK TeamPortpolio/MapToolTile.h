#pragma once
//크기
#define CELL_WIDTH 52
#define CELL_HEIGHT 52

//초기좌표
#define INIT_X -1768
#define INIT_Y -1144
//타일 갯수
#define TILE_COUNT_X 85
#define TILE_COUNT_Y 55

//타일 이미지
#define TILE_SIZE_X 8
#define TILE_SIZE_Y 10


#define TILE_MAX 3

enum TILEKIND
{
	TILEKIND_TERRAIN,
	TILEKIND_OBJECT,
	TILEKIND_INVISIBLE_BLOCK,
	TILEKIND_ITEMPOINT,
	TILEKIND_OPEN_DOOR,
	TILEKIND_CLOSE_DOOR,
	TILEKIND_NONE,

	TILEKIND_ITEMHEART,
	TILEKIND_ITEMGOLD,
	TILEKIND_ITEMBOMB,
	TILEKIND_ITEMATTACKBOMB,
	TILEKIND_ITEMKEY,
	TILEKIND_ITEMPILL,
	TILEKIND_ITEMCARD,
	TILEKIND_BLACKITEMBOXOPEN,
	TILEKIND_BLACKITEMBOXCLOSE,
	TILEKIND_GOLDITEMBOXOPEN,
	TILEKIND_GOLDITEMBOXCLOSE,
	TILEKIND_REDITEMBOXOPEN,
	TILEKIND_REDITEMBOXCLOSE,
	TILEKIND_CRACKEDITEMBOXOPEN,
	TILEKIND_CRACKEDITEMBOXCLOSE
};

struct TagTile
{
	int left, top, right, bottom; // x, y 값(rect의 left, top)

	RECT rect;

	int index; // 색인값. tileNum, tileKind, tilePos 에서 사용.

	int tileNum[TILE_MAX]; // 샘플타일 인덱스(선택된 창) index를 가져와서 담음.
	TILEKIND tileKind[TILE_MAX]; // 오브젝트, 타일 구분.
	POINT tilePos[TILE_MAX]; // 샘플타일에서 골라진녀석(frameX, frameY)


	int height; // 쌓일수록 커지는 높이
};
