#pragma once
#include "EnemyBase.h"

class MinionGaper : public EnemyBase
{
public:
	MinionGaper();
	~MinionGaper();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

