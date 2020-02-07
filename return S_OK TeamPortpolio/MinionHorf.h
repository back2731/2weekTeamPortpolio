#pragma once
#include "EnemyBase.h"

class MinionHorf : public EnemyBase
{
public:
	MinionHorf();
	~MinionHorf();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

