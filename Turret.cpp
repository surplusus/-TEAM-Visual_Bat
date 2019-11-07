#include "BaseInclude.h"
#include "Turret.h"
#include"CollisionMgr.h"
#include"ParticleMgr.h"
#include"EzealQ_Particle.h"
#include"AnimationCtrl.h"
#include"ObjectColider.h"
#include"BoundingBox.h"
#include"PickingSphereMgr.h"
#include "TurretGauge.h"
#include"EventMgr.h"
CTurret::CTurret(D3DXVECTOR3 pos)
{
	m_fSize = 1.0f;
	m_fAngle[ANGLE_X] = 0;
	m_fAngle[ANGLE_Y] = 1.0f;
	m_fAngle[ANGLE_Z] = 0;
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = pos;
	m_fHeight = 0.0f;

}

CTurret::~CTurret()
{
	Release();
}

HRESULT CTurret::Initialize()
{

	D3DXMatrixIdentity(&m_Info.matWorld);
	CloneMesh(GetDevice(), L"Blue_Turret", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl)
		return S_FALSE;

	m_pAnimationCtrl->SetAnimationSet("Default_Action");
	
	UpdateWorldMatrix();	
	//>>콜라이더 생성
	m_pColider = new CObjectColider(this);
	m_pColider->SetUp(m_Info, 1.0f, new CBoundingBox);
	m_ColiderList.push_back(m_pColider);
	GET_SINGLE(CParticleMgr) ->InsertColList(   this, &m_ColiderList);
	GET_SINGLE(CCollisionMgr)->InsertColistion(this, &m_ColiderList);
	GET_SINGLE(CPickingSphereMgr)->AddSphere(  this, m_pColider->GetSphere());	
	GET_SINGLE(EventMgr)->Subscribe(this, &CTurret::PaticleCollisionEvent);
	GET_SINGLE(EventMgr)->Subscribe(this, &CTurret::OnFindPickingSphere);	
	
	m_pGauge = new CTurretGauge;
	m_pGauge->SetWorld(m_Info.matWorld);
	m_pGauge->Initialize();
	m_bColl = false;
	return S_OK;
}

void CTurret::Progress()
{
	m_pAnimationCtrl->FrameMove(L"Blue_Turret", g_fDeltaTime);

	if (GetAsyncKeyState(VK_LEFT))
		Animation_Break();
	if (GetAsyncKeyState(VK_SPACE))
	{
		AddAttackLaizer();
	}
	m_pGauge->SetPosition(m_Info.vPos); 
	
	m_pGauge->Progress();
	UpdateWorldMatrix();

}

void CTurret::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), L"Blue_Turret");
	m_pGauge->Render();
	SetTexture(0, NULL);
}

void CTurret::Release()
{
	SAFE_RELEASE(m_pAnimationCtrl);
}


bool CTurret::Animation_Break()
{
	m_pAnimationCtrl->BlendAnimationSet("Idle_Break");
	return true;
}


void CTurret::AddAttackLaizer()
{
	D3DXMATRIX matWorld;
	D3DXVECTOR3 vPos;
	GetBoneMatrix(L"Blue_Turret", "Armature_bone_HA_OrderTurret_Damage10", &matWorld);
	vPos.x = matWorld._41;	vPos.y = matWorld._42;	vPos.z = matWorld._43;
	INFO tInfo = m_Info;
	vPos.z = 2.5f;
 	vPos.y = 6.3f;
	tInfo.vPos = vPos;

	CParticle * p = new CEzealQ_Particle(tInfo, 10.0f, D3DXVECTOR3(m_fAngle[ANGLE_X], m_fAngle[ANGLE_Y], m_fAngle[ANGLE_Z]));
	p->Initalize();
	m_ColiderList.push_back(dynamic_cast<CEzealQ_Particle*>(p)->GetColider());
	GET_SINGLE(CParticleMgr)->InsertColList(this, &m_ColiderList);
	GET_SINGLE(CCollisionMgr)->InsertColistion(this, &m_ColiderList);
	GET_SINGLE(CParticleMgr)->AddParticle(this, p);
}

void CTurret::PaticleCollisionEvent(COLLISIONEVENT * Evt)
{

}

void CTurret::OnFindPickingSphere(PICKSPHEREEVENT * evt)
{

}

void CTurret::UpdateCollisionList()
{
	list<ColiderComponent*>::iterator iter = m_ColiderList.begin();
	for (iter; iter != m_ColiderList.end();)
	{
		if ((*iter)->GetStateCol())
		{
			iter = m_ColiderList.erase(iter);
		}
		else iter++;
	}
}
