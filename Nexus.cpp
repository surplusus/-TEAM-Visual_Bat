#include "BaseInclude.h"
#include "Nexus.h"
#include "Ray.h"
#include "ObjMgr.h"
#include "HeightMap.h"
#include "SoundMgr.h"
#include "NexusGauge.h"
#include"ObjectColider.h"
#include"BoundingBox.h"
#include"PickingSphereMgr.h"
#include "TurretGauge.h"
#include"EventMgr.h"
#include"ParticleMgr.h"
#include"CollisionMgr.h"
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

	m_pColider = new CObjectColider(this);
	m_pColider->SetUp(m_Info, 2.0f, new CBoundingBox);
	m_ColiderList.push_back(m_pColider);
	InsertObjSphereColider(this, &m_ColiderList);
	GET_SINGLE(CPickingSphereMgr)->AddSphere(this, m_pColider->GetSphere());
	GET_SINGLE(EventMgr)->Subscribe(this, &CNexus::PaticleCollisionEvent);
	GET_SINGLE(EventMgr)->Subscribe(this, &CNexus::OnFindPickingSphere);



	m_pGauge = new CNexusGauge;
	m_pGauge->Initialize();

	return S_OK;
}

void CNexus::Progress()
{
	CTower::UpdateWorldMatrix();
	m_pAnimationCtrl->FrameMove(L"Nexus", g_fDeltaTime);

	AnimationSet();

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

void CNexus::PaticleCollisionEvent(COLLISIONEVENT * Evt)
{
}

void CNexus::OnFindPickingSphere(PICKSPHEREEVENT * evt)
{
}

bool CNexus::AnimationSet()
{
	m_pAnimationCtrl->BlendAnimationSet("Nexus_Animation");
	return false;
}
