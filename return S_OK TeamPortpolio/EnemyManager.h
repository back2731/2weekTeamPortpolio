#pragma once
#include "singletonBase.h"
#include "TestMinion.h"
#include "MinionMaw.h"
#include "MinionMulligan.h"

class EnemyManager : public singletonBase<EnemyManager>
{
private:
	TestMinion* m_TestMinion;
	MinionMaw* m_MinionMaw;
	MinionMulligan* m_MinionMulligan;

public:
	EnemyManager();
	~EnemyManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	//테스트 에네미 렉트값 가져오기
	RECT GetRect() { return m_TestMinion->GetRect(); }
	float GetRectX() { return m_TestMinion->GetRectX(); }
	float GetRectY() { return m_TestMinion->GetRectY(); }
};