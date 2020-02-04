#pragma once
#include "singletonBase.h"

class ObjectPool : public singletonBase<ObjectPool>
{
private:

public:
	ObjectPool();
	~ObjectPool();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

