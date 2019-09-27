#include "BaseInclude.h"
#include "AnimationCtrl.h"
#include"MeshMgr.h"

CAnimationCtrl::CAnimationCtrl()
	: m_dwCurrentAniSet(0)
	, m_numAnimationSets(0)
	, m_fCurrentTime(0.f)
	, m_pAniCtrl(NULL)

{
}

CAnimationCtrl::CAnimationCtrl(const CAnimationCtrl & Ani)
	: m_dwCurrentAniSet(0)
	, m_numAnimationSets(0)
	, m_fCurrentTime(0.f)
	, m_pAniCtrl(NULL)
{
		Ani.m_pAniCtrl->CloneAnimationController(Ani.m_pAniCtrl->GetMaxNumAnimationOutputs()
			, Ani.m_pAniCtrl->GetMaxNumAnimationSets()
			, Ani.m_pAniCtrl->GetMaxNumTracks()
			, Ani.m_pAniCtrl->GetMaxNumEvents()
			, &m_pAniCtrl);
	
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
	m_pAniCtrl->KeyTrackSpeed(m_dwNewTrack, 1.f, m_fCurrentTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_dwNewTrack, 1.f, m_fCurrentTime, kMoveTransitionTime, D3DXTRANSITION_LINEAR);
}

void CAnimationCtrl::FrameMove(const TCHAR * pMeshKey, float fTime)
{
	if (m_pAniCtrl != NULL)
		m_pAniCtrl->AdvanceTime(fTime, NULL);
	m_fCurrentTime += fTime;

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	(*(CMeshMgr::GetInstance()))->InvalidateMesh(pMeshKey, &matWorld);
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
