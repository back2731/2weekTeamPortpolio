#pragma once
#include "singletonBase.h"

class EnemyManager : public singletonBase<EnemyManager>
{
private:

public:
	EnemyManager();
	~EnemyManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

