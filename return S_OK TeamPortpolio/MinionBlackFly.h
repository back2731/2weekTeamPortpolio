#pragma once
#include "EnemyBase.h"

class MinionBlackFly : public EnemyBase
{
public:
	MinionBlackFly();
	~MinionBlackFly();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

