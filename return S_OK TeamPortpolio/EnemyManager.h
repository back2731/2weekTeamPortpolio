#pragma once
#include "singletonBase.h"
#include "MinionAttackFly.h"
#include "MinionMaw.h"
#include "MinionTumor.h"
#include "MinionGaper.h"
#include "MinionHorf.h"
#include "MinionMulligan.h"
#include "MinionPacer.h"
#include "MinionClot.h"
#include "MinionClotty.h"

class EnemyManager : public singletonBase<EnemyManager>
{
private:
	MinionAttackFly* m_MinionAttackFly;
	MinionMaw* m_MinionMaw;
	MinionTumor* m_MinionTumor;
	MinionGaper* m_MinionGaper;
	MinionHorf* m_MinionHorf;
	MinionMulligan* m_MinionMulligan;
	MinionPacer* m_MinionPacer;
	MinionClot* m_MinionClot;
	MinionClotty* m_MinionClotty;

public:
	EnemyManager();
	~EnemyManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	//테스트 에네미 렉트값 가져오기
	//RECT GetRect() { return m_TestMinion->GetRect(); }
	//float GetRectX() { return m_TestMinion->GetRectX(); }
	//float GetRectY() { return m_TestMinion->GetRectY(); }

	MinionTumor* getMinionTumor() { return m_MinionTumor; }
};