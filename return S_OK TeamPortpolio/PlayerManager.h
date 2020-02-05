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

	RECT GetRect() { return m_Player->GetRect(); }
	float GetRectX() { return m_Player->GetRectX(); }
	float GetRectY() { return m_Player->GetRectY();	}

};

