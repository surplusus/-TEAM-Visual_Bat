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
	HRESULT res = CloneMesh(GetDevice(), m_sName.c_str(), &m_pAnimationCtrl);
	
	if (!m_pAnimationCtrl)
		return S_FALSE;
	m_pAnimationCtrl->SetAnimationSet("Default_Action");
	
	m_SortID = SORTID_LAST;
	float fPos = 0.f;
	basic_string<TCHAR> tmp = m_sName.substr(6, m_sName.size() - 1);
	fPos += stof(tmp) * 10.f;
	m_Info.vPos = D3DXVECTOR3(fPos, 0.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, -1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, -1.f);
	m_fSize = 1.f;
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	
	UpdateWorldMatrix();
	SetUpPickingShere(10.f, m_Info.vPos);
	return S_OK;
}

void CMeleeMinion::Progress()
{
	float speed = 1.f;
	m_Info.vPos.x -= speed * g_fDeltaTime;
	m_Info.vPos.y -= speed * g_fDeltaTime;
	UpdateWorldMatrix();
}

void CMeleeMinion::Render()
{
	basic_string<TCHAR> szName(m_sName.begin(), m_sName.end());
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), szName.c_str());
}

void CMeleeMinion::Release()
{
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pAnimationCtrl);
}
