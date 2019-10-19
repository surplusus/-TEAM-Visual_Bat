#include "BaseInclude.h"
#include "CombatAlgorithm.h"
#include "EventMgr.h"
#include "Obj.h"

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

void CCombatAlgorithm::Follow(CObj * champ, CObj * enemy)
{
	D3DXVECTOR3 champPos, enemyPos;
	champPos= champ->GetInfo()->vPos;
	enemyPos = enemy->GetInfo()->vPos;


}
