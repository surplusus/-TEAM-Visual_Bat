#pragma once
class CAnimationCtrl
{
public:
	CAnimationCtrl();
	CAnimationCtrl(const CAnimationCtrl& Ani);
	~CAnimationCtrl();
private:
	LPD3DXANIMATIONCONTROLLER m_pAniCtrl;
	//현재 진행하고 있는 애니메이션 Set
	//애니메이션 Set이란 ? x파일에서 제공해주는 공격, 방어,뛰기,걷기등의 모션들을 이야기함
	//각 모션당 한 Set이라고 부름, 만약 위에 네가지 모션이 있으면
	//x파일은 네가지 애니메이션 set을 가진 것이라고 할 수 있음
	
	DWORD m_dwCurrentTrack;//현재 트랙
	DWORD m_dwNewTrack;//새로운 것
	DWORD m_dwCurrentAniSet;//현재 애니메이션 set

	//x파일 내에서 제공해주느 애니메이션 Set갯수
	int m_numAnimationSets;
	int m_fCurrentTime;

public:
	//애니메이션 관련 함수
	// 해당 함수들은 애니메이션을 들리고자하느 객체의 Progres함수에서 반복 호출
	// 특정애니메이션을 셋팅하기 위한 함수
	//여기에서 인데스는 전체 애니메이션중 어떤 부분을 돌려줄 것인지 판단하는 인자
	void SetAnimationSet(int);
	void FrameMove(const TCHAR* pMeshKey, float fTime);

public:
	LPD3DXANIMATIONCONTROLLER* GetAniCtrl()
	{
		return &m_pAniCtrl;
	}
	CAnimationCtrl* Clone();
public:
	void Release();

};

