#pragma once
#include "singletonBase.h"

class PlayerManager : public singletonBase<PlayerManager>
{
private:

public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

