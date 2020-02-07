#pragma once
#include "EnemyBase.h"

class MinionMulligan : public EnemyBase
{
public:
	MinionMulligan();
	~MinionMulligan();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

