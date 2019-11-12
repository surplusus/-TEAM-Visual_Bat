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

typedef struct _tagCollisionTarget : EVENT
{
	_tagCollisionTarget(CObj* pOri, CObj* pTarget)
		:m_pOri(pOri),m_pTarget(pTarget)
	{}
	CObj* m_pOri;
	CObj* m_pTarget;
}COLLISIONTARGETEVNET;