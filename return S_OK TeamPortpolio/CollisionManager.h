#pragma once
#include"singletonBase.h"

#include "Player.h"

#include "MinionAttackFly.h"
#include "MinionAttackFly.h"
#include "MinionMaw.h"
#include "MinionTumor.h"

#include "MinionClot.h"
#include "MinionClotty.h"
#include "MinionGaper.h"
#include "MinionHorf.h"
#include "MinionMulligan.h"
#include "MinionPacer.h"

class CollisionManager : public singletonBase<CollisionManager>
{
private:
	MinionTumor* m_MinionTumor;

public:
	CollisionManager();
	~CollisionManager();

	void PlayerBulletCollision(vector<BulletInfo>& playerBulletVector, vector<BulletInfo>::iterator& playerBulletIter);
};

