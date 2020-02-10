#pragma once
#include "singletonBase.h"

class CameraManager : public singletonBase<CameraManager>
{
private:

public:
	CameraManager();
	~CameraManager();
	
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

