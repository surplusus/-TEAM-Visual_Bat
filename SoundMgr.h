#pragma once
enum T_SOUND
{
	ANNOUNCER_Welcome = 1,	ANNOUNCER_Left30sec,	ANNOUNCER_Createminion, ANNOUNCER_END = 4,
	Udyr_Attack_Left,	Udyr_Idle,	Udyr_Search,	Udyr_Run,
	Udyr_Taunt,	Udyr_Dance,	Udyr_Death, 
	// 만들어야 하는 소리들
	Udyr_Beaten, Udyr_END = 12,
	Ezreal_Idle1,	Ezreal_Idle2,	Ezreal_Idel3,
	Ezreal_Attack1,	Ezreal_Attack2, Ezreal_Run, Ezreal_Death,
	Ezreal_Spell1,	Ezreal_Spell2,	Ezreal_Spell3,	Ezreal_Spell4,	Ezreal_END = 24
};

struct MyAlarm
{
	float startTime = 0.f;
	bool isRinging = false;
	bool isDead = false;
};

class SoundMgr
{
	DECLARE_SINGLETON(SoundMgr);
private:
	SoundMgr() {}
	~SoundMgr();
public:
	void SetUp();
	void Update();
	bool PlayUdyrSound(T_SOUND type);
	bool PlayEzrealSound(T_SOUND type);
	bool PlayAnnouncerMention(T_SOUND type);
	void StopBGM();
	void VolumeUp();
	void VolumeDown();
	void ErrCheck(FMOD_RESULT result);

	bool PlayOnTime(float endsec, int idx);
private:
	FMOD::System*					m_pSystem = nullptr;
	FMOD::Channel*					m_pUdyrChannel = nullptr;
	FMOD::Channel*					m_pEzrealChannel = nullptr;
	FMOD::Channel*					m_pAnnouncerChannel = nullptr;
	unordered_map<int, FMOD::Sound*>   m_mappSounds;
	float							m_fVolume = 1.f;
	bool							m_bDirty = false;
	float							m_fPlayGap = 0.3f;
	float							m_fPrevPlayTime = 0.f;
	FMOD_RESULT						m_result;
private:
	unordered_map<int, MyAlarm*>	m_mapAlarm;
	float							m_cumulativeTime = 0.f;
	int								m_bitFlag = 0;
	map<int, string>				m_mapPathInfo;
private:
	bool PlaySoundRegistered(T_SOUND type, FMOD::Channel* channel);
	void OnNoticeTestSoundEvent(ANNOUNCEEVENT* evt);
	void ParseSoundPathListFile(string sFilePath);
};

#define GET_SOUNDMGR SoundMgr::GetInstance()
