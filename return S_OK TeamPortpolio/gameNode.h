#pragma once
#include"image.h"
//백버퍼 이미지를 스태틱으로..
static image * _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

//맵툴에서 사용할 녀석
enum CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_MAP1,
	CTRL_MAP2,
	CTRL_END
};

class gameNode
{
private:

	
	//void setBackBuffer();		//백버퍼 셋팅

	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	//맵툴용
	int _ctrSelect;
	void setCtrSelect(int num) { _ctrSelect = num; }

	virtual void save();
	virtual void load();
	virtual void SetMap();



	//백버퍼 가져오기
	image* getBackBuffer() { return _backBuffer; }

	HDC getHDC() { return _hdc; }
	
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

