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
	m_TestMinion = new TestMinion;
	m_TestMinion->Init();

	m_MinionMaw = new MinionMaw;
	m_MinionMaw->Init();

	return S_OK;
}

void EnemyManager::Release()
{
	SAFE_DELETE(m_TestMinion);
	SAFE_DELETE(m_MinionMaw);
}

void EnemyManager::Update()
{
	m_TestMinion->Update();
	m_MinionMaw->Update();
}

void EnemyManager::Render(HDC hdc)
{
	m_TestMinion->Render(hdc);
	m_MinionMaw->Render(hdc);
}

