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
	HRESULT res = CloneMesh(GetDevice(), L"Minion", &m_pAnimationCtrl);
	
	if (!m_pAnimationCtrl)
		return S_FALSE;
	m_pAnimationCtrl->SetAnimationSet("Default_Action");
	
	m_SortID = SORTID_LAST;
	int Pos = rand() % 10;
	m_Info.vPos = D3DXVECTOR3((float)Pos, 0.f, 0.f);
	//m_Info.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
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
	float speed = 0.1f;
	m_Info.vPos.x -= speed * g_fDeltaTime;
	UpdateWorldMatrix();
}

void CMeleeMinion::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Minion");
	//Render_PickingShere();
}

void CMeleeMinion::Release()
{
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pAnimationCtrl);
}
