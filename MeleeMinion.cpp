#include "BaseInclude.h"
#include "MeleeMinion.h"
#include <random>

CMeleeMinion::CMeleeMinion()
{
}


CMeleeMinion::~CMeleeMinion()
{
}

HRESULT CMeleeMinion::Initialize()
{
	CloneMesh(GetDevice(), L"Minion", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl)
		return S_FALSE;
	UpdateWorldMatrix();
	m_pAnimationCtrl->SetAnimationSet("Default_Action");
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, -1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, -1.f);
	float fPos = 0.f;
	
	fPos += stof(m_sName, m_sName.size() - 2);
	m_Info.vPos = D3DXVECTOR3(fPos, 0.f, 0.f);
	return S_OK;
}

void CMeleeMinion::Progress()
{
	float speed = 1.f;
	m_Info.vPos.x -= speed * g_fDeltaTime;
	m_Info.vPos.y -= speed * g_fDeltaTime;
}

void CMeleeMinion::Render()
{
	basic_string<TCHAR> szName(m_sName.begin(), m_sName.end());
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), szName.c_str());
}

void CMeleeMinion::Release()
{
}
