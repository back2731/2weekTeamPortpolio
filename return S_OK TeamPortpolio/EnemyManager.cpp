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

	openDoor = true;
	isSummonEnemy = false;
	isBoss = true;

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
	//보스방 진입시 보스를 소환한다.
	if (isCheckClear && isSummonEnemy && !isBoss)
	{
		m_Monstro->Init(PointMake(WINSIZEX / 2, WINSIZEY / 2));
		isSummonEnemy = false;
		isBoss = true;
	}

	// 보스방, 상점방, 황금방이 아닌 일반방 진입 시 몬스터를 소환한다. 
	else if (isCheckClear && isSummonEnemy)
	{
		// 일반방에 들어오면 case에 따라서 랜덤으로 몬스터를 소환해준다.
		switch (RND->getInt(10))
		{
			case 0:
			{
				m_MinionAttackFly->Init(PointMake(150, 150), 0);
				m_MinionBlackFly->Init(PointMake(300, 150), 0);
				isSummonEnemy = false;
			}
			break;
			case 1:
			{
				m_MinionBlackFly->Init(PointMake(300, 150), 0);
				isSummonEnemy = false;
			}
			break;
			case 2:
			{
				m_MinionMaw->Init(PointMake(150, 400), 0);
				isSummonEnemy = false;
			}
			break;
			case 3:
			{
				m_MinionTumor->Init(PointMake(540, 400), 0);
				m_MinionMaw->Init(PointMake(150, 400), 0);
				isSummonEnemy = false;
			}
				break;
			case 4:
			{	
				m_MinionTumor->Init(PointMake(540, 400), 0);
				m_MinionAttackFly->Init(PointMake(650, 350), 0);
				isSummonEnemy = false;
			}
				break;
			case 5:
			{	
				m_MinionAttackFly->Init(PointMake(650, 350), 0);
				m_MinionBlackFly->Init(PointMake(200, 200), 0);
				isSummonEnemy = false;
			}
				break;
			case 6:
			{	
				isSummonEnemy = false; 
			}
				break;
			case 7:
			{	
				m_MinionAttackFly->Init(PointMake(650, 300), 0);
				isSummonEnemy = false; 
			}
				break;
			case 8:
			{
				m_MinionMaw->Init(PointMake(600, 350), 0);
				isSummonEnemy = false; 
			}
				break;
			case 9:
			{
				isSummonEnemy = false; 
			}
				break;
		}
	}

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

	// 해당 방에 몬스터의 벡터값이 존재하면 문을 닫고 없으면 문을 연다
	if (m_MinionAttackFly->GetMinionVector().size() > 0 ||
		m_MinionBlackFly->GetMinionVector().size() > 0 ||
		m_MinionMaw->GetMinionVector().size() > 0 ||
		m_MinionTumor->GetMinionVector().size() > 0 ||
		m_MinionGaper->GetMinionVector().size() > 0 ||
		m_MinionHorf->GetMinionVector().size() > 0 ||
		m_MinionPacer->GetMinionVector().size() > 0 ||
		m_MinionClot->GetMinionVector().size() > 0 ||
		m_MinionClotty->GetMinionVector().size() > 0 ||
		m_Monstro->GetMinionVector().size() > 0)
	{
		openDoor = false;
	}
	else
	{
		openDoor = true;
	}
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

void EnemyManager::GetLoadData(int _loadData)
{
	loadData = _loadData;
}

void EnemyManager::GetCheckClear(bool value)
{
	isCheckClear = value;
}

void EnemyManager::GetSummonEnemy(bool value)
{
	isSummonEnemy = value;
}

void EnemyManager::GetBoss(bool value)
{
	isBoss = value;
}

