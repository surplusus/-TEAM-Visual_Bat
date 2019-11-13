#pragma once
#include <vector>
#include <string>
std::string;
class CObj;
class SoundMgr;
class GuhyunScene;
class CPaticle;
class ColiderComponent;
class CParticleObj;
typedef struct _tagEvent
{
} EVENT;

typedef struct _tagAnnounceEvent : EVENT
{

} ANNOUNCEEVENT;

typedef struct _tagFollowEvent : EVENT
{
	_tagFollowEvent(CObj* champ, CObj* enemy)
	: m_champ(champ), m_enemy(enemy) {}
	CObj* m_champ;
	CObj* m_enemy;
} FOLLOWEVENT;

typedef struct _tagRegisterObj : EVENT
{
	_tagRegisterObj(std::string* result)
		: m_result(result) {}
	std::string* m_result;
} REGISTEREVENT;

typedef struct _tagPickingSphere : EVENT
{
	_tagPickingSphere(CObj* picked)
		: m_pObj(picked){}
	CObj* m_pObj;
} PICKSPHEREEVENT;

typedef struct _tagCollisionEvent : EVENT
{
	_tagCollisionEvent(CObj* pOri,ColiderComponent* pOriCol,
		CObj* pTarget =NULL, ColiderComponent* pTargetCol =NULL)
		: m_pOriObj(pOri),m_pOriCol(pOriCol),m_pTarget(pTarget),m_pTargetCol(pTargetCol)
		{}
	ColiderComponent* m_pOriCol;
	ColiderComponent* m_pTargetCol;
	CObj* m_pOriObj;
	CObj* m_pTarget;
	
} COLLISIONEVENT;

typedef struct _tagInsertColliderEvent : EVENT
{
	_tagInsertColliderEvent(void** pNewObj, void** pNewList)
		: m_pNewObj(pNewObj), m_pNewList(pNewList) {}
	void** m_pNewObj;
	void** m_pNewList;
} INSERTCOLLIDEREVENT;

typedef struct _tagPhysicalAttackEvent : EVENT
{
	_tagPhysicalAttackEvent(D3DXVECTOR3* vecAttackFrom, D3DXVECTOR3* vecAttackTo, STATUSINFO* infoDemage)
	: m_vecAttackFrom(*vecAttackFrom), m_vecAttackTo(*vecAttackTo), m_infoDemage(*infoDemage){}
	D3DXVECTOR3 m_vecAttackFrom;
	D3DXVECTOR3 m_vecAttackTo;
	STATUSINFO m_infoDemage;
} PHYSICALATTACKEVENT;