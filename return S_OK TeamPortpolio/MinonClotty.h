#pragma once
#include "EnemyBase.h"

class MinonClotty : public EnemyBase
{
public:
	MinonClotty();
	~MinonClotty();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

