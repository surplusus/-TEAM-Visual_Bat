#include "BaseInclude.h"
#include "Turret.h"


CTurret::CTurret()
{
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
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pAnimationCtrl);
}


bool CTurret::Animation_Break()
{
	m_pAnimationCtrl->BlendAnimationSet("Idle_break");
	return true;
}
