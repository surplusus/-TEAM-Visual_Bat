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
	// ���� ���� ����
	LARGE_INTEGER			m_NowTime;
private:
	float   m_fTime;
	// ���� ���� ����
	int		m_nFPS = 0.f;
	float	m_fDeltaTime = 0.f;
	float   m_fPileDeltaTime = 0.f;
	const float SEC_PER_FRAME = 1.0f / 60.0f;
public:
	void SetTime();
	void InitTimeMgr();
	// ���� ���� ����
	bool ControlFPS(float framePerSec);
public:
	float GetTime() const {		
		return m_fTime;
	}
	// ���� ���� ����
	int GetFPSTime() const {
		return m_nFPS;
	}
	float GetSystemDeltaTime() const {
		return m_fDeltaTime;
	}

};

