#pragma once
#include "gameNode.h"
#include "Shop.h"

class GameScene : public gameNode
{
private:
	Shop* m_shop;

public:
	GameScene();
	~GameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

