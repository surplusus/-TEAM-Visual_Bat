#include "BaseInclude.h"
#include "Inhibitor.h"
#include "InhibitorGauge.h"

#include"ObjectColider.h"
#include"BoundingBox.h"
#include"PickingSphereMgr.h"
#include "TurretGauge.h"
#include"EventMgr.h"

CInhibitor::CInhibitor(D3DXVECTOR3 pos)
{
	m_fSize = 1.5f;

	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = pos;
	m_fHeight = 0.0f;


	
}

CInhibitor::~CInhibitor()
{
	Release();
}

HRESULT CInhibitor::Initialize()
{
	CloneMesh(GetDevice(), L"Inhibitor", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl)
		return S_FALSE;

	UpdateWorldMatrix();
	m_pAnimationCtrl->SetAnimationSet("Default_Action");

	m_pColider = new CObjectColider(this);
	m_pColider->SetUp(m_Info, 2.0f, new CBoundingBox);
	m_ColiderList.push_back(m_pColider);
	InsertObjSphereColider(this, &m_ColiderList);
	GET_SINGLE(CPickingSphereMgr)->AddSphere(this, m_pColider->GetSphere());
	GET_SINGLE(EventMgr)->Subscribe(this, &CInhibitor::PaticleCollisionEvent);
	GET_SINGLE(EventMgr)->Subscribe(this, &CInhibitor::OnFindPickingSphere);


	m_pGauge = new CInhibitorGauge;
	m_pGauge->SetWorld(m_Info.matWorld);
	m_pGauge->Initialize();


	return S_OK;
}

void CInhibitor::Progress()
{
	m_pAnimationCtrl->FrameMove(L"Inhibitor", g_fDeltaTime);
	Animation_Set();
	m_pGauge->SetPosition(m_Info.vPos);
}

void CInhibitor::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Inhibitor");
	m_pGauge->Render();
}

void CInhibitor::Release()
{
	SAFE_RELEASE(m_pAnimationCtrl);
}

bool CInhibitor::Animation_Set()
{
	m_pAnimationCtrl->BlendAnimationSet("Armature_Take_001_BaseLayer");

	m_pAnimationCtrl->BlendAnimationSet("BUFFBONE_GLB_CHANNEL_LOC_Take_001_BaseLayer");

	m_pAnimationCtrl->BlendAnimationSet("BUFFBONE_GLB_GROUND_LOC_Take_001_BaseLayer");

	m_pAnimationCtrl->BlendAnimationSet("C_BUFFBONE_GLB_CENTER_LOC_Take_001_BaseLayer");

	m_pAnimationCtrl->BlendAnimationSet("C_BUFFBONE_GLB_LAYOUT_LOC_Take_001_BaseLayer");

	m_pAnimationCtrl->BlendAnimationSet("C_BUFFBONE_GLB_OVERHEAD_LOC_Take_001_BaseLayer");

	return true;
}

void CInhibitor::PaticleCollisionEvent(COLLISIONEVENT * Evt)
{
}

void CInhibitor::OnFindPickingSphere(PICKSPHEREEVENT * evt)
{
}
