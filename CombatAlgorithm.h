#pragma once
#include "GameAlgorithm.h"
class CObj;
class CCombatAlgorithm :
	public CAlgorithm
{
public:
	CCombatAlgorithm();
	virtual ~CCombatAlgorithm();
public:
	void SubscribeEvent();
	void Follow(CObj* champ, CObj* enemy);
};

