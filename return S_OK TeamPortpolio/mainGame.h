#pragma once
#include "gameNode.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "SubMap.h"
#include "MapToolScene.h"

#define SUBWINOPEN 1
class mainGame :  public gameNode
{
private:

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�
};

