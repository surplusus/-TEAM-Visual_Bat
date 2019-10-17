#pragma once
enum T_SOUND
{
	gun,
	get_coin,
	bgm,
	left30sec,
	createminion,
	welcome,
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
	unordered_map<string, FMOD::Sound*>   map_pSounds;
	float							m_fVolume = 1.f;
	bool							m_bDirty = false;
	float							m_fPlayGap = 0.3f;
	float							m_fPrevPlayTime = 0.f;
	FMOD_RESULT						m_result;
private:
	unordered_map<int, MyAlarm*>	m_mapAlarm;
	float							m_cumulativeTime = 0.f;
	int								m_bitFlag = 0;
};

#define GET_SOUNDMGR SoundManager::GetInstance()
