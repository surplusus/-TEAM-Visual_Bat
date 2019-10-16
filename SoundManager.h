#pragma once

class SoundManager
{
	DECLARE_SINGLETON(SoundManager);
private:
	SoundManager() {}
	~SoundManager();
public:
	void SetUp();
	//void Update();
	void PlayEffectSound(string name);
	void PlayBGMSound(string name);
	void PlayAnnouncerMention(string name);
	void StopBGM();
	void VolumeUp();
	void VolumeDown();
	void ErrCheck(FMOD_RESULT result);
private:
	FMOD::System*						m_pSystem = nullptr;
	FMOD::Channel*						m_pEffectChannel = nullptr;
	FMOD::Channel*						m_pBGMChannel = nullptr;
	FMOD::Channel*						m_pAnnouncerChannel = nullptr;
	std::unordered_map<string, FMOD::Sound*>	map_pSounds;
	float								m_fVolume = 1.f;
	bool								m_bDirty = false;
	float								m_fPlayGap = 0.3f;
	float								m_fPrevPlayTime = 0.f;
	FMOD_RESULT							m_result;
};

#define GET_SOUNDMGR SoundManager::GetInstance()
