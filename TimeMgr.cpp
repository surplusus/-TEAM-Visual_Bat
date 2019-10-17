#include "BaseInclude.h"
#include "TimeMgr.h"

CTimeMgr::CTimeMgr()
{
}


CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::SetTime()
{
	QueryPerformanceCounter(&m_InvaliTime);

	if (m_InvaliTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_LastTime = m_InvaliTime;
	}

	m_fTime = float(m_InvaliTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;
	m_FixTime = m_InvaliTime;
}

void CTimeMgr::InitTimeMgr()
{
	// 1초에 cpu가 카운팅하는 숫자
	QueryPerformanceFrequency(&m_CpuTick);

	// 현재 cpu가 카운팅한 숫자
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceCounter(&m_InvaliTime);
	QueryPerformanceCounter(&m_FixTime);
	// 구현 새로 만듦	
	QueryPerformanceCounter(&m_NowTime);
}

bool CTimeMgr::ControlFPS(float framePerSec)
{
	const float secByOneFrame = 1.f / framePerSec;
	static int cntLoop = 0;
	static float fPileUntilOneSec = 0.f;
	bool checker = false;
	m_fPileDeltaTime += GetTime();
	fPileUntilOneSec += GetTime();
	if (m_fPileDeltaTime >= secByOneFrame) {
		checker = true;
		g_fDeltaTime = m_fDeltaTime = m_fPileDeltaTime;
		m_fPileDeltaTime = 0.f;
		++cntLoop;
	}

	if (fPileUntilOneSec >= 1.f)
	{
		//printf("PileUntilOneSec : %f\n", fPileUntilOneSec);
		fPileUntilOneSec = 0.f;
		m_nFPS = cntLoop;
		cntLoop = 0;
	}

	return checker;
}
