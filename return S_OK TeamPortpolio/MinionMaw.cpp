#include "stdafx.h"
#include "MinionMaw.h"


MinionMaw::MinionMaw()
{
}


MinionMaw::~MinionMaw()
{
}

HRESULT MinionMaw::Init(POINT position)
{
	EnemyInfo minionMaw;
	//����ü ���� ����

	vMinionMaw.push_back(minionMaw);


	areaCheck = true;
	return E_NOTIMPL;
}

void MinionMaw::Release()
{
}

void MinionMaw::Update()
{
}

void MinionMaw::Render(HDC hdc)
{
}
