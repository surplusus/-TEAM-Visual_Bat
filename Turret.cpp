#include "BaseInclude.h"
#include "Turret.h"


CTurret::CTurret()
{
	m_fSize = 1.0f;

	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = D3DXVECTOR3(23.f, 0.f, 22.8f);
	m_fHeight = 0.0f;
}


CTurret::~CTurret()
{
	Release();
}

HRESULT CTurret::Initialize()
{
	CloneMesh(GetDevice(), L"Blue_Turret", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl)
		return S_FALSE;

	UpdateWorldMatrix();
	m_pAnimationCtrl->SetAnimationSet("Default_Action");

	return S_OK;
}

void CTurret::Progress()
{
	m_pAnimationCtrl->FrameMove(L"Blue_Turret", g_fDeltaTime);
	if (GetAsyncKeyState(VK_LEFT))
		Animation_Break();
}

void CTurret::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Blue_Turret");
}

void CTurret::Release()
{
	SAFE_RELEASE(m_pAnimationCtrl);
}


bool CTurret::Animation_Break()
{
	m_pAnimationCtrl->BlendAnimationSet("Idle_break");
	return true;
}
