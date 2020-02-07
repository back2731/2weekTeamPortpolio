#pragma once
#include "EnemyBase.h"

class MinionTumor : EnemyBase
{
public:
	MinionTumor();
	~MinionTumor();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

