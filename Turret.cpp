#include "BaseInclude.h"
#include "Turret.h"
#include"ColitionMgr.h"
#include"ParticleMgr.h"
#include"EzealQ_Particle.h"
CTurret::CTurret()
{
	m_fSize = 1.0f;

	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = D3DXVECTOR3(23.f, 0.f, 22.5f);
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
	if (GetAsyncKeyState(VK_SPACE))
	{
		AddAttackLaizer();
	}
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

bool CTurret::Attacked_Target()
{

	return false;
}

void CTurret::AddAttackLaizer()
{
	D3DXMATRIX matWorld;
	D3DXVECTOR3 vPos;
	GetBoneMatrix(L"Blue_Turret", "Armature_bone_HA_OrderTurret_Damage1", &matWorld);
	vPos.x = matWorld._41;	vPos.y = matWorld._42;	vPos.z = matWorld._43;
	INFO tInfo = m_Info;
	tInfo.vPos = vPos;

	CParticle * p = new CEzealQ_Particle(tInfo, 10.0f, D3DXVECTOR3(m_fAngle[ANGLE_X], m_fAngle[ANGLE_Y], m_fAngle[ANGLE_Z]));
	p->Initalize();
	m_ColiderList.push_back(dynamic_cast<CEzealQ_Particle*>(p)->GetColider());
	GET_SINGLE(CColitionMgr)->InsertColistion(this, &m_ColiderList);
	GET_SINGLE(CParticleMgr)->AddParticle(this, p);
}
