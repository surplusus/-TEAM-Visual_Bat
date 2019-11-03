#include "BaseInclude.h"
#include "AnimationCtrl.h"
#include "MeshMgr.h"

CAnimationCtrl::CAnimationCtrl()
	: m_dwCurrentAniSet(0)
	, m_numAnimationSets(0)
	, m_pAniCtrl(NULL)
	, m_fDurationTime(0.f)
{
}

CAnimationCtrl::CAnimationCtrl(const CAnimationCtrl & Ani)
	: m_dwCurrentAniSet(0)
	, m_numAnimationSets(0)
	, m_pAniCtrl(NULL)
	, m_fDurationTime(0.f)
	, m_sAnimationSets("")
{
		Ani.m_pAniCtrl->CloneAnimationController(Ani.m_pAniCtrl->GetMaxNumAnimationOutputs()
			, Ani.m_pAniCtrl->GetMaxNumAnimationSets()
			, Ani.m_pAniCtrl->GetMaxNumTracks()
			, Ani.m_pAniCtrl->GetMaxNumEvents()
			, &m_pAniCtrl);

	// x 파일 내 애니메이션 이름 가져오기
		LPD3DXANIMATIONSET pAn;
		UINT nAn = m_pAniCtrl->GetNumAnimationSets();
		for (UINT i = 0; i < nAn; i++)
		{
			m_pAniCtrl->GetAnimationSet(i, &pAn);
			string sName = pAn->GetName();
			m_vAllAnimationName.push_back(sName);
			pAn->Release();
		}
}


CAnimationCtrl::~CAnimationCtrl()
{
	Release();
}
//인덱스가 애니메이션 set을 의미
const float kMoveTransitionTime = 0.25f;

void CAnimationCtrl::SetAnimationSet(int iIdx)
{
	//트랙 2개를 준비
	//현재 트랙이 0 이면 1, 1이면 0으로
	m_dwNewTrack = (m_dwCurrentTrack == 0 ? 1 : 0);
	LPD3DXANIMATIONSET pAs = NULL;
	//애니메이션 set 셋팅
	if (m_pAniCtrl == NULL) return;
	
	m_pAniCtrl->GetAnimationSet(iIdx, &pAs);
	//애니메이션  트랙에 애니메이션 셋을 올림
	m_pAniCtrl->SetTrackAnimationSet(m_dwNewTrack, pAs);
	m_dPeriodCurAnimSet = pAs->GetPeriod();
	pAs->Release();
	
	//현재 셋팅되어 있는 애니메이션 셋이 셋팅하고자하는 애니메이션 셋과 같으면
	//다시 셋팅할 필요가 없음 , 그러므로 빠져나간다.
	if (m_dwCurrentAniSet == iIdx)
		return;

	//위 조건을 만족하지 않ㄴ으면 이제 새로운 애니메이션 셋팅
	//현재 애니메이션 셋의 인덱스 저장하고 있는 변수에 넣어줌
	m_dwCurrentAniSet = iIdx;
	//각 트랙을 처음부터 돌아갈수 있도록 초기화
	m_pAniCtrl->UnkeyAllTrackEvents(m_dwNewTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_dwCurrentTrack);
	
	//트랙의 시작위치 설정
	m_pAniCtrl->SetTrackPosition(m_dwNewTrack, 0.f);
	m_pAniCtrl->SetTrackPosition(m_dwCurrentTrack, 0.f);

	m_pAniCtrl->SetTrackEnable(m_dwNewTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_dwNewTrack, 1.f, m_fDurationTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_dwNewTrack, 1.f, m_fDurationTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR);
}

void CAnimationCtrl::SetAnimationSet(string aniName)
{
	//트랙 2개를 준비
//현재 트랙이 0 이면 1, 1이면 0으로
	m_dwNewTrack = (m_dwCurrentTrack == 0 ? 1 : 0);
	LPD3DXANIMATIONSET pAs = NULL;
	//애니메이션 set 셋팅
	if (m_pAniCtrl == NULL) return;

	//m_pAniCtrl->GetAnimationSet(iIdx, &pAs);
	m_pAniCtrl->GetAnimationSetByName(aniName.c_str(), &pAs);
	//애니메이션  트랙에 애니메이션 셋을 올림
	m_pAniCtrl->SetTrackAnimationSet(m_dwNewTrack, pAs);
	m_dPeriodCurAnimSet = pAs->GetPeriod();
	pAs->Release();

	//현재 셋팅되어 있는 애니메이션 셋이 셋팅하고자하는 애니메이션 셋과 같으면
	//다시 셋팅할 필요가 없음 , 그러므로 빠져나간다.
	if (m_sAnimationSets == aniName)
		return;

	//위 조건을 만족하지 않ㄴ으면 이제 새로운 애니메이션 셋팅
	//현재 애니메이션 셋의 인덱스 저장하고 있는 변수에 넣어줌
	m_sAnimationSets = aniName;
	//각 트랙을 처음부터 돌아갈수 있도록 초기화
	m_pAniCtrl->UnkeyAllTrackEvents(m_dwNewTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_dwCurrentTrack);

	//트랙의 시작위치 설정
	m_pAniCtrl->SetTrackPosition(m_dwNewTrack, 0.f);
	m_pAniCtrl->SetTrackPosition(m_dwCurrentTrack, 0.f);

	m_pAniCtrl->SetTrackEnable(m_dwNewTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_dwNewTrack, 1.f, m_fDurationTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_dwNewTrack, 1.f, m_fDurationTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR);

}

void CAnimationCtrl::BlendAnimationSet(string aniName)
{
	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC stTrackDesc;
	m_pAniCtrl->GetTrackDesc(0, &stTrackDesc);
	m_pAniCtrl->GetTrackAnimationSet(0, &pPrevAnimSet);

	m_dPeriodCurAnimSet = pPrevAnimSet->GetPeriod();
	string sCompName = pPrevAnimSet->GetName();
	
	if (aniName == sCompName) {
		SAFE_RELEASE(pPrevAnimSet);
		return;
	}

	m_bIsBlending = true;
	m_fTimeDuringBlending = 0.f;

	m_pAniCtrl->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAniCtrl->SetTrackDesc(1, &stTrackDesc);

	m_pAniCtrl->GetAnimationSetByName(aniName.c_str(), &pNextAnimSet);
	m_pAniCtrl->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAniCtrl->SetTrackPosition(0, 0.0f);

	m_pAniCtrl->SetTrackWeight(0, 0.0f);
	m_pAniCtrl->SetTrackWeight(1, 1.0f);
	
	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);
}

void CAnimationCtrl::BlendAnimationSet(int aniIdx)
{
	m_bIsBlending = true;
	m_fTimeDuringBlending = 0.f;

	UINT iAniCount = m_pAniCtrl->GetNumAnimationSets();
	aniIdx %= static_cast<int>(iAniCount);

	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC stTrackDesc;
	m_pAniCtrl->GetTrackDesc(0, &stTrackDesc);
	m_pAniCtrl->GetTrackAnimationSet(0, &pPrevAnimSet);
	
	m_dPeriodCurAnimSet = pPrevAnimSet->GetPeriod();
	string sPrevName = pPrevAnimSet->GetName();
	m_pAniCtrl->GetAnimationSet(aniIdx, &pNextAnimSet);
	string sNextName = pNextAnimSet->GetName();
	if (sPrevName == sNextName) {
		SAFE_RELEASE(pPrevAnimSet);
		SAFE_RELEASE(pNextAnimSet);
		return;
	}

	m_pAniCtrl->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAniCtrl->SetTrackDesc(1, &stTrackDesc);

	m_pAniCtrl->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAniCtrl->SetTrackPosition(0, 0.0f);

	m_pAniCtrl->SetTrackWeight(0, 0.0f);
	m_pAniCtrl->SetTrackWeight(1, 1.0f);

	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);
}

void CAnimationCtrl::FrameMove(const TCHAR * pMeshKey, float fTime)
{
	if (m_bIsBlending)
	{
		m_fTimeDuringBlending += fTime;
		if (m_fTimeDuringBlending >= m_fAniOverlapTime)
		{
			//m_fTimeDuringBlending = 0.f;
			m_bIsBlending = false;
			m_pAniCtrl->SetTrackWeight(0, 1.f);
			m_pAniCtrl->SetTrackEnable(1, false);
		}
		else
		{
			float fWeight = m_fTimeDuringBlending / m_fAniOverlapTime;
			m_pAniCtrl->SetTrackWeight(0, fWeight);
			m_pAniCtrl->SetTrackWeight(1, 1.f - fWeight);
		}
	}

	if (m_pAniCtrl != NULL)
		m_pAniCtrl->AdvanceTime(fTime, NULL);

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	(*(CMeshMgr::GetInstance()))->InvalidateMesh(pMeshKey, &matWorld);
}

void CAnimationCtrl::DisplayAniSetNameOnConsole()
{
	UINT nCntAni = m_pAniCtrl->GetNumAnimationSets();
	UINT nAniNum;
	LPD3DXANIMATIONSET pAniSet;
	m_pAniCtrl->GetTrackAnimationSet(0, &pAniSet);
	//m_pAniCtrl->GetAnimationSetByName("Stand", &pAniSet);
	LPCSTR name = pAniSet->GetName();
	DOUBLE dPeriod = pAniSet->GetPeriod();
	system("cls");
	cout << "Ani 이름 : " <<name << endl;
	printf("period : %f\n", dPeriod);
	printf("애니메이션 이름 : \n");
	for (size_t i = 0; i < m_vAllAnimationName.size(); i++)
	{
		cout << m_vAllAnimationName[i] << " \n";
	}
}

void CAnimationCtrl::GetAnimationNames(OUT vector<string>& vec)
{
	vec.resize(m_vAllAnimationName.size());
	copy(m_vAllAnimationName.begin(), m_vAllAnimationName.end(), vec.begin());
}

CAnimationCtrl * CAnimationCtrl::Clone()
{
	return new CAnimationCtrl(*this);
}

void CAnimationCtrl::Release()
{
	if (m_pAniCtrl)
	{
		m_pAniCtrl->Release();
	}
}
