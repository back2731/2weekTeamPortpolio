#pragma once
#include "gameNode.h"
class IntroScene : public gameNode
{
public:
	IntroScene();
	~IntroScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

