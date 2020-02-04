#pragma once
#include "singletonBase.h"

class BulletManager : public singletonBase<BulletManager>
{
private:

public:
	BulletManager();
	~BulletManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

