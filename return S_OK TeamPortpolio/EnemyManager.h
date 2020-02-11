#pragma once
#include "singletonBase.h"
#include "Monstro.h"
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
	//����
	Monstro*			m_Monstro;

	// ���߹̴Ͼ�
	MinionAttackFly*	m_MinionAttackFly;
	MinionBlackFly*		m_MinionBlackFly;
	MinionMaw*			m_MinionMaw;
	MinionTumor*		m_MinionTumor;

	// ����̴Ͼ�
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

	// �Ѿ� �浹�� �Լ�
	Monstro*			GetMonstro()			{ return m_Monstro; }

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