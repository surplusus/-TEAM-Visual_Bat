#include "BaseInclude.h"
#include "Nexus.h"
#include "Ray.h"
#include "ObjMgr.h"
#include "HeightMap.h"
#include "SoundMgr.h"
#include "NexusGauge.h"

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

	m_pGauge = new CNexusGauge;
	m_pGauge->SetWorld(m_Info.matWorld);
	m_pGauge->Initialize();
	return S_OK;
}

void CNexus::Progress()
{
	CTower::UpdateWorldMatrix();
	m_pAnimationCtrl->FrameMove(L"Nexus", g_fDeltaTime);

	AnimationSet();

	m_pGauge->SetPosition(m_Info.vPos);
	m_pGauge->Progress();
}

void CNexus::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Nexus");
	m_pGauge->Render();
}

void CNexus::Release()
{
	SAFE_RELEASE(m_pAnimationCtrl);
}

bool CNexus::AnimationSet()
{
	m_pAnimationCtrl->BlendAnimationSet("Nexus_Animation");
	return false;
}
