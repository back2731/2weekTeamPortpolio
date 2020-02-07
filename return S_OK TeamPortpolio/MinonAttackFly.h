#pragma once
#include "EnemyBase.h"

class MinonAttackFly : public EnemyBase
{
public:
	MinonAttackFly();
	~MinonAttackFly();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

