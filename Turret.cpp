#include "BaseInclude.h"
#include "Turret.h"
#include"CollisionMgr.h"
#include"ParticleMgr.h"
#include"EzealQ_Particle.h"
#include"AnimationCtrl.h"
#include "TurretGauge.h"
CTurret::CTurret(D3DXVECTOR3 pos, TCHAR* TurretName, float Rotation_Radian)
	:m_MeshName(TurretName), m_RotRadian(Rotation_Radian)
{
	m_fSize = 1.0f;

	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
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
	CloneMesh(GetDevice(),m_MeshName, &m_pAnimationCtrl);

	if (!m_pAnimationCtrl)
		return S_FALSE;

	UpdateWorldMatrix(m_RotRadian);
	m_pAnimationCtrl->SetAnimationSet("Default_Action");

	m_pGauge = new CTurretGauge;
	m_pGauge->SetInfo(m_Info);
	m_pGauge->SetParentWorld(m_Info.matWorld);
	m_pGauge->Initialize();

	return S_OK;
}

void CTurret::Progress()
{
	m_pAnimationCtrl->FrameMove(m_MeshName, g_fDeltaTime);

	if (GetAsyncKeyState(VK_LEFT))
		Animation_Break();
	if (GetAsyncKeyState(VK_SPACE))
	{
		AddAttackLaizer();
	}
	
	m_pGauge->Progress();
}

void CTurret::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), m_MeshName);
	m_pGauge->Render();
}

void CTurret::Release()
{
	SAFE_RELEASE(m_pAnimationCtrl);
}


bool CTurret::Animation_Break()
{
	m_pAnimationCtrl->BlendAnimationSet("Break1");
	return true;
}


void CTurret::AddAttackLaizer()
{
	D3DXMATRIX matWorld;
	D3DXVECTOR3 vPos;
	GetBoneMatrix(m_MeshName, "Armature_bone_HA_OrderTurret_Damage10", &matWorld);
	vPos.x = matWorld._41;	vPos.y = matWorld._42;	vPos.z = matWorld._43;
	INFO tInfo = m_Info;
	vPos.z = 2.5f;
 	vPos.y = 6.3f;
	tInfo.vPos = vPos;

	CParticle * p = 
		new CEzealQ_Particle
		(tInfo, 10.0f, D3DXVECTOR3(m_fAngle[ANGLE_X], m_fAngle[ANGLE_Y], m_fAngle[ANGLE_Z]));
	p->Initalize();
	m_ColiderList.push_back(dynamic_cast<CEzealQ_Particle*>(p)->GetColider());
	GET_SINGLE(CParticleMgr)->InsertColList(this, &m_ColiderList);
	GET_SINGLE(CCollisionMgr)->InsertColistion(this, &m_ColiderList);
	GET_SINGLE(CParticleMgr)->AddParticle(this, p);
}
