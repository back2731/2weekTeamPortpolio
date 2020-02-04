#pragma once
#include "singletonBase.h"
class ItemManager : public singletonBase<ItemManager>
{
private:

public:
	ItemManager();
	~ItemManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

