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
	m_Monstro = new Monstro;
	m_MinionAttackFly = new MinionAttackFly;
	m_MinionBlackFly = new MinionBlackFly;
	m_MinionMaw = new MinionMaw;
	m_MinionTumor = new MinionTumor;
	m_MinionClot = new MinionClot;
	m_MinionClotty = new MinionClotty;
	m_MinionGaper = new MinionGaper;
	m_MinionHorf = new MinionHorf;
	m_MinionMulligan = new MinionMulligan;
	m_MinionPacer = new MinionPacer;

	//m_Monstro->Init(PointMake(WINSIZEX / 2, WINSIZEY / 2));

	m_MinionAttackFly->Init(PointMake(80, 100), 0);
	//m_MinionAttackFly->Init(PointMake(80, 150), 1);
	//m_MinionAttackFly->Init(PointMake(80, 200), 2);

	m_MinionBlackFly->Init(PointMake(300, 400), 0);
	//m_MinionBlackFly->Init(PointMake(400, 400), 1);
	//m_MinionBlackFly->Init(PointMake(500, 400), 2);	

	//m_MinionMaw->Init(PointMake(500, 100), 0);
	//m_MinionMaw->Init(PointMake(550, 100), 1);
	//m_MinionMaw->Init(PointMake(600, 100), 2);

	//m_MinionTumor->Init(PointMake(700, 100), 0);
	//m_MinionTumor->Init(PointMake(800, 100), 1);
	//m_MinionTumor->Init(PointMake(900, 100), 2);

	//m_MinionClot->Init(PointMake(100, 500), 0);
	//m_MinionClot->Init(PointMake(200, 500), 1);
	//m_MinionClot->Init(PointMake(300, 500), 2);

	//m_MinionClotty->Init(PointMake(100, 500), 0);
	//m_MinionClotty->Init(PointMake(200, 500), 1);
	//m_MinionClotty->Init(PointMake(300, 500), 2);

	//m_MinionGaper->Init(PointMake(100, 300), 0);
	//m_MinionGaper->Init(PointMake(200, 300), 1);
	//m_MinionGaper->Init(PointMake(300, 300), 2);

	//m_MinionHorf->Init(PointMake(100, 300), 0);
	//m_MinionHorf->Init(PointMake(200, 300), 1);
	//m_MinionHorf->Init(PointMake(300, 300), 2);

	//m_MinionMulligan->Init(PointMake(100, 300), 0);
	//m_MinionMulligan->Init(PointMake(200, 300), 1);
	//m_MinionMulligan->Init(PointMake(300, 300), 2);

	//m_MinionPacer->Init(PointMake(100, 300), 0);
	//m_MinionPacer->Init(PointMake(200, 300), 1);
	//m_MinionPacer->Init(PointMake(300, 300), 2);

	return S_OK;
}

void EnemyManager::Release()
{
	SAFE_DELETE(m_Monstro);
	SAFE_DELETE(m_MinionAttackFly);
	SAFE_DELETE(m_MinionBlackFly);
	SAFE_DELETE(m_MinionMaw);
	SAFE_DELETE(m_MinionTumor);
	SAFE_DELETE(m_MinionGaper);
	SAFE_DELETE(m_MinionHorf);
	SAFE_DELETE(m_MinionMulligan);
	SAFE_DELETE(m_MinionPacer);
	SAFE_DELETE(m_MinionClot);
	SAFE_DELETE(m_MinionClotty);
}

void EnemyManager::Update()
{
	m_Monstro->Update();
	m_MinionAttackFly->Update();
	m_MinionBlackFly->Update();
	m_MinionMaw->Update();
	m_MinionTumor->Update();
	m_MinionGaper->Update();
	m_MinionHorf->Update();
	m_MinionMulligan->Update();
	m_MinionPacer->Update();
	m_MinionClot->Update();
	m_MinionClotty->Update();
}

void EnemyManager::Render(HDC hdc)
{
	m_Monstro->Render(hdc);
	m_MinionAttackFly->Render(hdc);
	m_MinionBlackFly->Render(hdc);
	m_MinionMaw->Render(hdc);
	m_MinionTumor->Render(hdc);
	m_MinionGaper->Render(hdc);
	m_MinionHorf->Render(hdc);
	m_MinionMulligan->Render(hdc);
	m_MinionPacer->Render(hdc);
	m_MinionClot->Render(hdc);
	m_MinionClotty->Render(hdc);
}