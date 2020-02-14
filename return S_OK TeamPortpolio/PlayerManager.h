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

	RECT GetPlayerHeadRect() { return m_Player->GetPlayerHeadRect(); }
	float GetPlayerHeadRectX() { return m_Player->GetPlayerHeadRectX(); }
	float GetPlayerHeadRectY() { return m_Player->GetPlayerHeadRectY(); }

	RECT GetPlayerHitRect() { return m_Player->GetPlayerHitRect(); }
	float GetPlayerHitRectX() { return m_Player->GetPlayerHitRectX(); }
	float GetPlayerHitRectY() { return m_Player->GetPlayerHitRectY(); }

	void SetPlayerRectX(float num) { m_Player->SetPlayerRectX(num); }
	void SetPlayerRectY(float num) { m_Player->SetPlayerRectY(num); }

	int GetPlayerOffensePower() { return m_Player->GetPlayerOffensePower(); }
	void SetPlayerOffensePower(int addPower) { m_Player->SetPlayerOffensePower(addPower); }

};
