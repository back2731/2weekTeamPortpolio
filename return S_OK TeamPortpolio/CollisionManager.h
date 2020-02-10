#pragma once
#include "singletonBase.h"
class CollisionManager : public singletonBase<CollisionManager>
{
private:

public:
	CollisionManager();
	~CollisionManager();
};

