#pragma once
#include <vector>
#include <string>
std::string;
class CObj;
class SoundMgr;
class GuhyunScene;

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
		: m_pObj(picked) {}
	CObj * m_pObj;
}PICKSPHEREEVENT;