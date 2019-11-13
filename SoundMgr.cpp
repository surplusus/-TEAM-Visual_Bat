#include "BaseInclude.h"
#include "SoundMgr.h"
#include "EventMgr.h"
#include <sstream>
#include <fstream>

using namespace FMOD;

SoundMgr::~SoundMgr()
{
	for (auto it = m_mappSounds.begin(); it != m_mappSounds.end(); it++)
		m_result = it->second->release();
		//FMOD_Sound_Release(it->second);
	m_result = m_pSystem->close();
	m_result = m_pSystem->release();
	for (size_t i = 0; i < m_mapAlarm.size(); i++)
	{
		SAFE_DELETE(m_mapAlarm[i]);
	}
	m_mapAlarm.clear();
	for (auto & it : m_mappSounds) {
		SAFE_DELETE(it.second);
	}
	m_mappSounds.clear();
	//=========== Unsubscribe Events ==========//
	GET_SINGLE(EventMgr)->Unsubscribe(this, &SoundMgr::OnNoticeTestSoundEvent);
}

void SoundMgr::SetUp()
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

	ParseSoundPathListFile("./Resource/SoundPathList.dat");

	Sound* sound;
	for (int i = 0; i < (int)(T_SOUND::Ezreal_END); i++)
	{
		auto ps = m_mapPathInfo.find(i);
		if (ps == m_mapPathInfo.end())
			continue;
		m_result = m_pSystem->createSound(m_mapPathInfo[i].c_str(), FMOD_DEFAULT, 0, &sound);
		m_mappSounds.insert(make_pair(i, sound));

	}

	//FMOD_System_CreateSound(m_pSystem, "Resource/Sound/welcome.wav", FMOD_LOOP_NORMAL, 0, &sound); ErrCheck(m_result);
	
	//=========== Subscribe Events ==========//
	GET_SINGLE(EventMgr)->Subscribe(this, &SoundMgr::OnNoticeTestSoundEvent);
}

void SoundMgr::Update()
{
	m_pSystem->update();
	if (m_mapAlarm.size() != 0)
		m_cumulativeTime += g_fDeltaTime;
}

void SoundMgr::StopBGM()
{
	bool isPlaying;
	m_pEzrealChannel->isPlaying(&isPlaying);
	
	if (isPlaying)
		m_pEzrealChannel->stop();
}

void SoundMgr::VolumeUp()
{
	if (m_fVolume <= 1.f)
	{
		m_fVolume += 0.1f;
	}
	else
	{
		m_fVolume = 1.f;
	}
	m_pEzrealChannel->setVolume(m_fVolume);
	m_pUdyrChannel->setVolume(m_fVolume);
	m_pAnnouncerChannel->setVolume(m_fVolume);
	//FMOD_Channel_SetVolume(m_pBGMChannel, m_fVolume);

	m_bDirty = true;
}

void SoundMgr::VolumeDown()
{
	if (m_fVolume >= 0.f)
	{
		m_fVolume -= 0.1f;
	}
	else
	{
		m_fVolume = 0.f;
	}
	m_pEzrealChannel->setVolume(m_fVolume);
	m_pUdyrChannel->setVolume(m_fVolume);
	m_pAnnouncerChannel->setVolume(m_fVolume);

	m_bDirty = true;
}

void SoundMgr::ErrCheck(FMOD_RESULT result)
{
	string strText;
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		PostMessage(NULL, WM_QUIT, 0, 0);
	}
}

bool SoundMgr::PlayOnTime(float endsec, int idx)
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

bool SoundMgr::PlayUdyrSound(T_SOUND type)
{
	if (T_SOUND::ANNOUNCER_END > type || T_SOUND::Udyr_END <= type)
		return false;
	return PlaySoundRegistered(type, m_pUdyrChannel);
}

bool SoundMgr::PlayEzrealSound(T_SOUND type)
{
	if (T_SOUND::Udyr_END > type || T_SOUND::Ezreal_END <= type)
		return false;
	return PlaySoundRegistered(type, m_pEzrealChannel);
}

bool SoundMgr::PlayAnnouncerMention(T_SOUND type)
{
	if (type >= T_SOUND::ANNOUNCER_END)
		return false;
	return PlaySoundRegistered(type, m_pAnnouncerChannel);
}

bool SoundMgr::PlaySoundRegistered(T_SOUND type, Channel* channel)
{
	auto pSound = m_mappSounds.find(static_cast<int>(type));
	if (pSound != m_mappSounds.end())
	{
		bool playing;
		m_pEzrealChannel->isPlaying(&playing);
		if (playing)
			m_pUdyrChannel->stop();
		m_result = m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound->second, false, &channel); 
		ErrCheck(m_result);

		//m_pSystem->update();
		int nChannelPlayingNow = 0;
		m_pSystem->getChannelsPlaying(&nChannelPlayingNow);
		return true;
	}
	return false;
}

void SoundMgr::OnNoticeTestSoundEvent(ANNOUNCEEVENT * evt)
{
	// 이벤트 안쓸듯
	PlayAnnouncerMention(ANNOUNCER_Createminion);
	
	delete evt;
}

void SoundMgr::ParseSoundPathListFile(string sFilePath)
{
	ifstream file(sFilePath.c_str(), ifstream::in);

	if (!file.is_open()) {
		cout << "Error Opening SoundPathList File\n";
		return;
	}

	string str;
	while (file)
	{
		vector<string> token;
		string s, t;
		getline(file, s);
		if (s[0] == ' ' || s[0] == '#' || s[0] == '\n')
			continue;
		for (stringstream ss(s); (ss >> t);)
			token.push_back(t);
		
		if (token.size() >= 2)
			m_mapPathInfo.insert(make_pair(stoi(token[0]),token[1]));

		if (file.eof())
			break;
	}

	file.close();
}
