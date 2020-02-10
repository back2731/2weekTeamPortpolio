#pragma once
#include "Player.h"

#include "MinionAttackFly.h"
#include "MinionBlackFly.h"
#include "MinionMaw.h"
#include "MinionTumor.h"

#include "MinionClot.h"
#include "MinionClotty.h"
#include "MinionGaper.h"
#include "MinionHorf.h"
#include "MinionMulligan.h"
#include "MinionPacer.h"

class CollisionManager
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
	CollisionManager();
	~CollisionManager();	

	void Test(vector<BulletInfo>& unitBulletVector, vector<BulletInfo>::iterator& unitBulletIter);
};

