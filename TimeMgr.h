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
private:
	float m_fTime;
public:
	void SetTime();
	void InitTimeMgr();
public:
	float GetTime() const
	{
		return m_fTime;
	}
};

