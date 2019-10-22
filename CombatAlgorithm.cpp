#include "BaseInclude.h"
#include "CombatAlgorithm.h"
#include "Obj.h"
#include "EventMgr.h"

CCombatAlgorithm::CCombatAlgorithm()
{
}


CCombatAlgorithm::~CCombatAlgorithm()
{
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CCombatAlgorithm::Follow);
}

void CCombatAlgorithm::SubscribeEvent()
{
	GET_SINGLE(EventMgr)->Subscribe(this, &CCombatAlgorithm::Follow);
}

void CCombatAlgorithm::Follow(FOLLOWEVENT * evt)
{
	D3DXVECTOR3 champPos, enemyPos;
	champPos = evt->m_champ->GetInfo()->vPos;
	enemyPos = evt->m_enemy->GetInfo()->vPos;
}