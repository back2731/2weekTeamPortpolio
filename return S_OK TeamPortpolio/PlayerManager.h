#pragma once
#include "singletonBase.h"
#include "Player.h"

class PlayerManager : public singletonBase<PlayerManager>
{
private:
	Player* m_Player;

public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

