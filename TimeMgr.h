#pragma once
class CTimeMgr
{
	
DECLARE_SINGLETON(CTimeMgr)
private:
	CTimeMgr();
public:
	~CTimeMgr();

private:
	LARGE_INTEGER			m_CpuTick;
	LARGE_INTEGER			m_InvaliTime;
	LARGE_INTEGER			m_FixTime;
	LARGE_INTEGER			m_LastTime;
	// 구현 새로 만듦
	LARGE_INTEGER			m_NowTime;
private:
	float   m_fTime;
	// 구현 새로 만듦
	int		m_nFPS = 0.f;
	float	m_fDeltaTime = 0.f;
	float   m_fPileDeltaTime = 0.f;
	const float SEC_PER_FRAME = 1.0f / 60.0f;
public:
	void SetTime();
	void InitTimeMgr();
	// 구현 새로 만듦
	bool ControlFPS(float framePerSec);
public:
	float GetTime() const {		
		return m_fTime;
	}
	// 구현 새로 만듦
	int GetFPSTime() const {
		return m_nFPS;
	}
	float GetSystemDeltaTime() const {
		return m_fDeltaTime;
	}

};

