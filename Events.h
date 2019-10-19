#pragma once

class CObj;
class SoundManager;
class GuhyunScene;

typedef struct _tagEvent
{
} EVENT;

typedef struct _tagAnnounceEvent : EVENT
{
	//_tagSoundEvent(SoundManager* sound, GuhyunScene* caller)
	//	: m_sound(sound), m_caller(caller) {}
	//SoundManager* m_sound;
	//GuhyunScene* m_caller;
} ANNOUNCEEVENT;

