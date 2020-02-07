#pragma once
#include "EnemyBase.h"

class MinonMaw : public EnemyBase
{
public:
	MinonMaw();
	~MinonMaw();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

