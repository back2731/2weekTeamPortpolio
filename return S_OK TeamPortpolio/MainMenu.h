#pragma once
#include "gameNode.h"
class MainMenu : public gameNode
{
public:
	MainMenu();
	~MainMenu();

	HRESULT init();
	void release();
	void update();
	void render();
};

