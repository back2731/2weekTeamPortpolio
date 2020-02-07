#pragma once
#include "EnemyBase.h"
class MinionAttackFly : public EnemyBase
{
public:
	MinionAttackFly();
	~MinionAttackFly();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

