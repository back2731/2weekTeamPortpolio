#pragma once
#include "EnemyBase.h"

class MinonClot : public EnemyBase
{
public:
	MinonClot();
	~MinonClot();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

