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
	//구조체 정보 기입

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
