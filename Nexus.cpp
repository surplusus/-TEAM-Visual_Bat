#include "BaseInclude.h"
#include "Nexus.h"
#include "Ray.h"
#include "ObjMgr.h"
#include "HeightMap.h"
#include "SoundMgr.h"

CNexus::CNexus()
{
}


CNexus::~CNexus()
{
	Release();
}

HRESULT CNexus::Initialize()
{
	CloneMesh(GetDevice(), L"Udyr", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl) return S_FALSE;

	UpdateWorldMatrix();
	m_pAnimationCtrl->SetAnimationSet("Default_Action");

	m_Info.vLook = D3DXVECTOR3(0, 0, -1.0f);
	m_Info.vDir = D3DXVECTOR3(0, 0, -1.0f);
	m_Info.vPos = D3DXVECTOR3(0, 0, 0);
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0);

	return S_OK;
}

void CNexus::Progress()
{
	CTower::UpdateWorldMatrix();
	m_pAnimationCtrl->FrameMove(L"Udyr", g_fDeltaTime);
}

void CNexus::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Udyr");
}

void CNexus::Release()
{
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pAnimationCtrl);
}