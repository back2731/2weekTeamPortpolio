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
	return S_OK;
}

void EnemyManager::Release()
{
	SAFE_DELETE(m_TestMinion);
}

void EnemyManager::Update()
{
	m_TestMinion->Update();
}

void EnemyManager::Render(HDC hdc)
{
	m_TestMinion->Render(hdc);
}
