#pragma once
enum T_SOUND
{
	welcome = 1,
	left30sec = 2,
	createminion,
	Udyr_Attack_Left,
	Udyr_Idle,
	Udyr_Search,
	Udyr_Run,
	Udyr_Taunt,
	Udyr_Dance,
	Udyr_Death,
	Ezreal_Idle1,
	Ezreal_Idle2,
	Ezreal_Idel3,
	Ezreal_Attack1,
	Ezreal_Attack2,
	Ezreal_Spell1,
	Ezreal_Spell2,
	Ezreal_Spell3,
	Ezreal_Spell4,
	Ezreal_Run,
	Ezreal_Death,
	END
};

struct MyAlarm
{
	float startTime = 0.f;
	bool isRinging = false;
	bool isDead = false;
};

class SoundManager
{
	DECLARE_SINGLETON(SoundManager);
private:
	SoundManager() {}
	~SoundManager();
public:
	void SetUp();
	void Update();
	void PlayEffectSound(string name);
	void PlayBGMSound(string name);
	void PlayAnnouncerMention(string name);
	void StopBGM();
	void VolumeUp();
	void VolumeDown();
	void ErrCheck(FMOD_RESULT result);

	bool PlayOnTime(float endsec, int idx);
private:
	void PlayBySoundType(T_SOUND sound); // ¸¸µé¾î¾ßµÊ
private:
	FMOD::System*					m_pSystem = nullptr;
	FMOD::Channel*					m_pEffectChannel = nullptr;
	FMOD::Channel*					m_pBGMChannel = nullptr;
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
	void PlaySoundRegistered(T_SOUND type);
	void OnNoticeTestSoundEvent(ANNOUNCEEVENT* evt);
	void ParseSoundPathListFile(string sFilePath);
};

#define GET_SOUNDMGR SoundManager::GetInstance()
