#pragma once
#include "gameNode.h"
#include "Shop.h"
#include "MapToolScene.h"

class GameScene : public gameNode
{
private:
	Shop* m_shop;
	image* testMapImage;
	MapToolScene * _mapToolScene;

public:
	GameScene();
	~GameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};