#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::Init()
{
	//m_TestMinion = new TestMinion;
	//m_TestMinion->Init(PointMake(WINSIZEX / 2 + 300, WINSIZEY / 2));

	m_MinionMaw = new MinionMaw;
	m_MinionMaw->Init(PointMake(100, 100), 0);
	m_MinionMaw->Init(PointMake(400, 100), 1);
	m_MinionMaw->Init(PointMake(700, 100), 2);

	m_MinionMulligan = new MinionMulligan;
	m_MinionMulligan->Init(PointMake(300, 300), 0);
	m_MinionMulligan->Init(PointMake(700, 300), 1);

	return S_OK;
}

void EnemyManager::Release()
{
	//SAFE_DELETE(m_TestMinion);
	SAFE_DELETE(m_MinionMaw);
	SAFE_DELETE(m_MinionMulligan);
}

void EnemyManager::Update()
{
	//m_TestMinion->Update();
	m_MinionMaw->Update();
	m_MinionMulligan->Update();
}

void EnemyManager::Render(HDC hdc)
{
	//m_TestMinion->Render(hdc);
	m_MinionMaw->Render(hdc);
	m_MinionMulligan->Render(hdc);
}