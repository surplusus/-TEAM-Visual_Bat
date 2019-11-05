#include "BaseInclude.h"
#include "Nexus.h"
#include "Ray.h"
#include "ObjMgr.h"
#include "HeightMap.h"
#include "SoundMgr.h"

CNexus::CNexus(D3DXVECTOR3 pos)
{
	m_fSize = 1.0f;
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = pos;
	m_fHeight = 0.0f;
}


CNexus::CNexus()
{
	m_fSize = 1.0f;
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = D3DXVECTOR3(0, 0, 0);
	m_fHeight = 0.0f;
}

CNexus::~CNexus()
{
	Release();
}

HRESULT CNexus::Initialize()
{
	CloneMesh(GetDevice(), L"Nexus", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl) return S_FALSE;

	UpdateWorldMatrix();
	m_pAnimationCtrl->SetAnimationSet("Default_Action");

	

	return S_OK;
}

void CNexus::Progress()
{
	CTower::UpdateWorldMatrix();
	m_pAnimationCtrl->FrameMove(L"Nexus", g_fDeltaTime);

	AnimationSet();
}

void CNexus::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Nexus");
}

void CNexus::Release()
{
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pAnimationCtrl);
}

bool CNexus::AnimationSet()
{
	m_pAnimationCtrl->BlendAnimationSet("Nexus_Animation");
	return false;
}
