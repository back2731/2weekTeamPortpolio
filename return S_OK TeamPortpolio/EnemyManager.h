#pragma once
#include "singletonBase.h"
#include "MinionAttackFly.h"
#include "MinionBlackFly.h"
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

	// 공중미니언
	MinionAttackFly*	m_MinionAttackFly;
	MinionBlackFly*		m_MinionBlackFly;
	MinionMaw*			m_MinionMaw;
	MinionTumor*		m_MinionTumor;

	// 지상미니언
	MinionClot*			m_MinionClot;
	MinionClotty*		m_MinionClotty;
	MinionGaper*		m_MinionGaper;
	MinionHorf*			m_MinionHorf;
	MinionMulligan*		m_MinionMulligan;
	MinionPacer*		m_MinionPacer;

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

	// 총알 충돌용 함수
	MinionAttackFly*	GetMinionAttackFly()	{ return m_MinionAttackFly; }
	MinionBlackFly*		GetMinionBlackFly()		{ return m_MinionBlackFly; }
	MinionMaw*			GetMinionMaw()			{ return m_MinionMaw; }
	MinionTumor*		GetMinionTumor()		{ return m_MinionTumor; }

	MinionClot*			GetMinionClot()			{ return  m_MinionClot;	}
	MinionClotty*		GetMinionClotty()		{ return m_MinionClotty; }
	MinionGaper*		GetMinionGaper()		{ return m_MinionGaper; }
	MinionHorf*			GetMinionHorf()			{ return m_MinionHorf; }
	MinionMulligan*		GetMinionMulligan()		{ return  m_MinionMulligan; }
	MinionPacer*		GetMinionPacer()		{ return  m_MinionPacer; }

};