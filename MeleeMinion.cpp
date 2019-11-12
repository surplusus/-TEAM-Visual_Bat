#include "BaseInclude.h"
#include "MeleeMinion.h"
#include <random>

CMeleeMinion::CMeleeMinion()
{
}


CMeleeMinion::~CMeleeMinion()
{
	Release();
}

HRESULT CMeleeMinion::Initialize()
{
	HRESULT res = CloneMesh(GetDevice(), m_MeshName, &m_pAnimationCtrl);
	SetUpAniSetNameList();
	if (!m_pAnimationCtrl)
		return S_FALSE;
	m_pAnimationCtrl->SetAnimationSet("Default_Action");
	m_pAnimationCtrl->GetAnimationNames(m_AniSetNameList);
	
	m_SortID = SORTID_LAST;
	m_Info.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, -1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, -1.f);
	m_fSize = 1.f;
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);


	UpdateWorldMatrix();
	SetUpPickingShere(1.f);
	return S_OK;
}

void CMeleeMinion::Progress()
{
	if (D3DXVec3Length(&(m_Info.vPos - m_NextPoint)) <= 3.f)
		ChangeNextPoint();

	CMinion::UpdateWorldMatrix();
	if (m_pBehavior->m_BlackBoard->getBool("Alive") == true)
		m_pAnimationCtrl->FrameMove(L"MeleeMinion", g_fDeltaTime);
}

void CMeleeMinion::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"MeleeMinion");
	Render_PickingShere();
}

void CMeleeMinion::Release()
{
	SAFE_RELEASE(m_pAnimationCtrl);
	SAFE_DELETE(m_pBehavior);
	SAFE_DELETE(m_pCollider);
}

void CMeleeMinion::SetPosition(const D3DXVECTOR3 * pos)
{
	m_Info.vPos.x = pos->x;
	m_Info.vPos.y = pos->y;
	m_Info.vPos.z = pos->z;
}
