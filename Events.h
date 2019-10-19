#pragma once

class CObj;
class SoundManager;
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