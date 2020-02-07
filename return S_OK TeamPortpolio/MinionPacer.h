#pragma once
#include "EnemyBase.h"

class MinionPacer : public EnemyBase
{
public:
	MinionPacer();
	~MinionPacer();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

