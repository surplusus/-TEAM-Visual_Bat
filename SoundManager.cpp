#include "BaseInclude.h"
#include "SoundManager.h"
#include "EventMgr.h"

using namespace FMOD;

SoundManager::~SoundManager()
{
	for (auto it = map_pSounds.begin(); it != map_pSounds.end(); it++)
		m_result = it->second->release();
		//FMOD_Sound_Release(it->second);
	m_result = m_pSystem->close();
	m_result = m_pSystem->release();
	for (size_t i = 0; i < m_mapAlarm.size(); i++)
	{
		delete m_mapAlarm[i];
		m_mapAlarm.erase(i);
	}
	//=========== Unsubscribe Events ==========//
	GET_SINGLE(EventMgr)->Unsubscribe(this, &SoundManager::OnNoticeTestSoundEvent);
}

void SoundManager::SetUp()
{
	unsigned int version;
	//FMOD_System_Create(&m_pSystem);
	System_Create(&m_pSystem);
	m_result = m_pSystem->getVersion(&version);
	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
		return;
	}
	//FMOD_System_Init(m_pSystem, 10, FMOD_INIT_NORMAL, NULL);
	m_result = m_pSystem->init(1, FMOD_INIT_NORMAL, 0);	ErrCheck(m_result);
	m_result = m_pSystem->setStreamBufferSize(64 * 1024, FMOD_TIMEUNIT_RAWBYTES); ErrCheck(m_result);

	Sound* sound;
	m_result = m_pSystem->createSound("./Resource/Sound/gun.wav", FMOD_DEFAULT, 0, &sound);  
	ErrCheck(m_result);		map_pSounds["gun"] = sound;
	m_result = m_pSystem->createSound("./Resource/Sound/get_coin.wav", FMOD_DEFAULT, 0, &sound);  
	ErrCheck(m_result);  	map_pSounds["get_coin"] = sound;
	m_result = m_pSystem->createSound("./Resource/Sound/bgm.wav", FMOD_LOOP_NORMAL, 0, &sound);  
	ErrCheck(m_result);		map_pSounds["bgm"] = sound;
	m_result = m_pSystem->createSound("./Resource/Sound/left30sec.wav", FMOD_DEFAULT, 0, &sound);  
	ErrCheck(m_result);		map_pSounds["left30sec"] = sound;
	m_result = m_pSystem->createSound("./Resource/Sound/createminion.wav", FMOD_DEFAULT, 0, &sound);  
	ErrCheck(m_result);		map_pSounds["createminion"] = sound;
	m_result = m_pSystem->createSound("./Resource/Sound/welcome.wav", FMOD_DEFAULT, 0, &sound);  
	ErrCheck(m_result);		map_pSounds["welcome"] = sound;
	//FMOD_System_CreateSound(m_pSystem, "Resource/Sound/welcome.wav", FMOD_LOOP_NORMAL, 0, &sound); ErrCheck(m_result);
	
	//=========== Subscribe Events ==========//
	GET_SINGLE(EventMgr)->Subscribe(this, &SoundManager::OnNoticeTestSoundEvent);
}

void SoundManager::Update()
{
	m_pSystem->update();
	if (m_mapAlarm.size() != 0)
		m_cumulativeTime += g_fDeltaTime;
}

void SoundManager::PlayEffectSound(string name)
{
	//float startTime = GetTime();
	//if (startTime - m_fPrevPlayTime < m_fPlayGap)
	//	return;
	//m_fPrevPlayTime = startTime;

	if (map_pSounds.find(name) != map_pSounds.end())
	{
		bool playing;
		m_pBGMChannel->isPlaying(&playing);
		if (playing)
			m_pEffectChannel->stop();
		//FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, map_pSounds[name], 0, &m_pEffectChannel);
		m_result = m_pSystem->playSound(FMOD_CHANNEL_FREE, map_pSounds[name], false, &m_pEffectChannel);  ErrCheck(m_result);
		//FMOD_System_Update(m_pSystem);
		m_pSystem->update();
		int nChannelPlayingNow = 0;
		m_pSystem->getChannelsPlaying(&nChannelPlayingNow);
		cout << "m_pEffectChannel is playing" << endl;
	}
	
}

void SoundManager::PlayBGMSound(string name)
{
	bool playing;
	m_pBGMChannel->isPlaying(&playing);
	if (playing)
		return;

	if (map_pSounds.find(name) != map_pSounds.end())
	{
		m_result = m_pSystem->playSound(FMOD_CHANNEL_FREE, map_pSounds[name], false, &m_pBGMChannel); ErrCheck(m_result);
		m_pSystem->update();
		int nChannelPlayingNow = 0;
		m_pSystem->getChannelsPlaying(&nChannelPlayingNow);
		cout << "m_pBGMChannel is playing" << endl;
	}
}

void SoundManager::PlayAnnouncerMention(string name)
{
	if (map_pSounds.find(name) != map_pSounds.end())
	{
		bool playing;
		m_pBGMChannel->isPlaying(&playing);
		if (playing)
			m_pEffectChannel->stop();
		m_result = m_pSystem->playSound(FMOD_CHANNEL_FREE, map_pSounds[name], false, &m_pAnnouncerChannel); ErrCheck(m_result);
		
		m_pSystem->update();
		int nChannelPlayingNow = 0;
		m_pSystem->getChannelsPlaying(&nChannelPlayingNow);
		cout << "m_pAnnouncerChannel is playing" << endl;
	}
}

void SoundManager::StopBGM()
{
	bool isPlaying;
	m_pBGMChannel->isPlaying(&isPlaying);
	
	if (isPlaying)
		m_pBGMChannel->stop();
}

void SoundManager::VolumeUp()
{
	if (m_fVolume <= 1.f)
	{
		m_fVolume += 0.1f;
	}
	else
	{
		m_fVolume = 1.f;
	}
	m_pBGMChannel->setVolume(m_fVolume);
	m_pEffectChannel->setVolume(m_fVolume);
	m_pAnnouncerChannel->setVolume(m_fVolume);
	//FMOD_Channel_SetVolume(m_pBGMChannel, m_fVolume);

	m_bDirty = true;
}

void SoundManager::VolumeDown()
{
	if (m_fVolume >= 0.f)
	{
		m_fVolume -= 0.1f;
	}
	else
	{
		m_fVolume = 0.f;
	}
	m_pBGMChannel->setVolume(m_fVolume);
	m_pEffectChannel->setVolume(m_fVolume);
	m_pAnnouncerChannel->setVolume(m_fVolume);

	m_bDirty = true;
}

void SoundManager::ErrCheck(FMOD_RESULT result)
{
	string strText;
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		PostMessage(NULL, WM_QUIT, 0, 0);
	}
}

bool SoundManager::PlayOnTime(float endsec, int idx)
{
	bool ringing = false;
	if (m_mapAlarm.find(idx) == m_mapAlarm.end()) {
		m_bitFlag |= (1 << idx);
		MyAlarm* a = new MyAlarm;
		m_mapAlarm[idx] = a;
		m_mapAlarm[idx]->startTime = m_cumulativeTime;
		printf("bitflaf on : %b", m_bitFlag);
	}
	if (m_cumulativeTime - m_mapAlarm[idx]->startTime >= endsec && (m_bitFlag & (1 << idx))) {
		m_mapAlarm[idx]->isRinging = ringing = true;
		m_bitFlag &= ~(1 << idx);
	}

	if (m_bitFlag == 0) {
		m_cumulativeTime = 0.f;
	}
	return ringing;
}

void SoundManager::PlayBySoundType(T_SOUND sound)
{
}

void SoundManager::OnNoticeTestSoundEvent(ANNOUNCEEVENT * evt)
{
	PlayAnnouncerMention("left30sec");
}
