#pragma once
#include "gameNode.h"
class GameScene : public gameNode
{
public:
	GameScene();
	~GameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

