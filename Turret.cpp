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
#include"ParticleColider.h"
#include "EventMgr.h"
#include "TurretMissle.h"
CTurret::CTurret(D3DXVECTOR3 pos)
	:m_pTexture(NULL), m_fStartTime(0), m_fEndTime(0), m_bDirty(true), m_bProgress(true)
	, m_fEnd_NewMissleTime(10), m_fStart_NewMissleTime(0)
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
	m_Champ_State.resize(CHAMPION_STATETYPE_END_ANIMSTATE);
	StatusInit();
	D3DXMatrixIdentity(&m_Info.matWorld);
	CloneMesh(GetDevice(), L"Blue_Turret1", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl)
		return S_FALSE;

	m_pAnimationCtrl->SetAnimationSet("Default_Action");
	m_CurStateType = CHAMPION_STATETYPE_IDLE1;
	m_strAnimationState = "Default_Action";
	UpdateWorldMatrix();
	//>>콜라이더 생성
	m_pColider = new CObjectColider(this);
	m_pColider->SetUp(m_Info, 1.0f, new CBoundingBox);
	m_ColiderList.push_back(m_pColider);
	InsertObjSphereColider(this, &m_ColiderList);
	GET_SINGLE(CPickingSphereMgr)->AddSphere(this, m_pColider->GetSphere());
	GET_SINGLE(EventMgr)->Subscribe(this, &CTurret::PaticleCollisionEvent);
	GET_SINGLE(EventMgr)->Subscribe(this, &CTurret::OnFindPickingSphere);
	GET_SINGLE(EventMgr)->Subscribe(this, &CTurret::UpdateStatus_Event);
	m_pGauge = new CTurretGauge;
	m_pGauge->Initialize();
	m_pGauge->SetInfo(m_Info);
	m_pGauge->SetParentWorld(m_Info.matWorld);
	m_pGauge->SetMaxHP(m_StatusInfo.fMaxHP);
	m_pGauge->SufferDmg(m_StatusInfo.fHP);
	m_bColl = false;
	return S_OK;
}

void CTurret::Progress()
{
	if (m_bProgress) {
		UpdateCollisionList();
		SettingAnimationSort();
		SettingFrameAnimation();
		m_pAnimationCtrl->FrameMove(m_MeshName, g_fDeltaTime);

		if (GetAsyncKeyState(VK_LEFT))
			Animation_Break();
		if (GetAsyncKeyState(VK_SPACE))
		{
			AddAttackLaizer();
		}
		m_pGauge->SetMaxHP(m_StatusInfo.fMaxHP);
		m_pGauge->SufferDmg(m_StatusInfo.fHP);
		m_pGauge->Progress();
		UpdateWorldMatrix();
	}
}

void CTurret::Render()
{

	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	if (m_bDirty)
	{
		m_pAnimationCtrl->BlendAnimationSet(m_strAnimationState);
		m_bDirty = false;
	}
	Mesh_Render(GetDevice(), m_MeshName);
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

	CChampion* m_pChamp = dynamic_cast<CChampion*>(Evt->m_pOriObj);
	if (m_pChamp) {
		if (dynamic_cast<CChampion*>(Evt->m_pOriObj)->GetStateType() != CHAMPION_STATETYPE_DEATH
			&& Evt->m_pOriObj != this)
		{
			//때린 객체에 대한 콜라이더
			CParticleColider * pColider = (dynamic_cast<CParticleColider*>(Evt->m_pOriCol));
			if (pColider) {
				CParticleObj * pParticle = pColider->GetParticle();
				if (pParticle)
				{
					pParticle->SetStateCol(true);
					//타겟의 hp에서 때리는 객체의 공격을 빼준다.
					CTurret* pChamp = dynamic_cast<CTurret*>(Evt->m_pTarget);
					if (pChamp) {
						float myHp = dynamic_cast<CTurret*>(Evt->m_pTarget)->GetStatusInfo()->fHP;
						float fDamge = pParticle->GetStatus().fBase_Attack;
						float fHp = myHp - fDamge;
						dynamic_cast<CTurret*>(Evt->m_pTarget)->GetStatusInfo()->fHP = fHp;
						if (m_StatusInfo.fHP < 0)
						{
							m_Champ_State[CHAMPION_STATETYPE_DEATH] = true;
							if (m_fStartTime <= 0)		m_fStartTime = 0;
							m_bProgress = false;
						}
						if (m_StatusInfo.fHP < 2500)
						{//부셔지는 애니메이션
							InitAnimationState();
							m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
							m_Champ_State[CHAMPION_STATETYPE_IDLE2] = true;
						}
						m_bColl = true;
						//list<ColiderComponent*>::iterator iter = find(m_ColiderList.begin(), m_ColiderList.end(), Evt->m_pOriCol);
						//if (iter != m_ColiderList.end()) (*iter)->SetStateCol(true);
					}
				}
			}
			else
			{

				CTurret* m_pTurret = dynamic_cast<CTurret*>(Evt->m_pOriObj);
				if (m_pTurret)
					m_pTurret->AddLaizer(Evt->m_pTarget);
			}
		}
		m_bColl = false;
		std::cout << "HP" << dynamic_cast<CChampion*>(Evt->m_pOriObj)->GetStatusInfo()->fHP << endl;
	}
	
}

void CTurret::OnFindPickingSphere(PICKSPHEREEVENT * evt)
{

}


void CTurret::InitAnimationState()
{
	for (int i = 0; i<m_Champ_State.size(); i++)
	{
		m_Champ_State[i] = false;
	}
	m_Champ_State[CHAMPION_STATETYPE_IDLE1] = true;
}

void CTurret::SettingAnimationSort()
{
	CHAMPION_STATETYPE Check = CHAMPION_STATETYPE_IDLE1;

	if (!m_Champ_State[CHAMPION_STATETYPE_IDLE1])
	{
		if (Check == CHAMPION_STATETYPE_IDLE1) Check = SettingBreak_Motion();
		if (m_CurStateType != Check)
		{
			m_fStartTime = 0.f;
			m_bDirty = true;
		}
		m_CurStateType = Check;
	}

	if (m_Champ_State[CHAMPION_STATETYPE_IDLE1] && m_ChangeMotion)
	{
		InitAnimationState();
		m_bDirty = true;
		m_ChangeMotion = false;
	}
}

void CTurret::SettingFrameAnimation()
{
	switch (m_CurStateType)
	{
	case CHAMPION_STATETYPE_IDLE1:
		m_strAnimationState = "Default_Action";
		break;
	case CHAMPION_STATETYPE_IDLE2:
		m_strAnimationState = "Idle_Break";
		break;
	}
}

CHAMPION_STATETYPE CTurret::SettingBreak_Motion()
{
	if (m_Champ_State[CHAMPION_STATETYPE_IDLE2])
	{
		InitAnimationState();
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
		m_Champ_State[CHAMPION_STATETYPE_IDLE2] = true;
		m_ChangeMotion = false;
		m_fEndTime = 168;
		if (m_fStartTime >= m_fEndTime &&
			m_CurStateType == CHAMPION_STATETYPE_IDLE2)
		{
			InitAnimationState();
			m_Champ_State[CHAMPION_STATETYPE_IDLE2] = false;
			m_Champ_State[CHAMPION_STATETYPE_IDLE1] = true;
			m_ChangeMotion = true;
			m_fStartTime = 0;
			m_bDirty = true;
			return CHAMPION_STATETYPE_IDLE1;
		}
		m_fStartTime += 1;
		return CHAMPION_STATETYPE_IDLE2;
	}
	return CHAMPION_STATETYPE_IDLE1;

}

void CTurret::AddLaizer(CObj* pTarget)
{
	if (m_fStart_NewMissleTime > m_fEnd_NewMissleTime)
	{
		CTurretMissle* pMissle = new CTurretMissle(m_Info, 1.0f, D3DXVECTOR3(m_fAngle[ANGLE_X], m_fAngle[ANGLE_Y], m_fAngle[ANGLE_Z]), pTarget);
		pMissle->Initalize();
		//	m_ColiderList.push_back(pMissle->GetColider());
		InsertObjSphereColider(this, &m_ColiderList);
		GET_SINGLE(CParticleMgr)->AddParticle(this, pMissle);
		m_fStart_NewMissleTime = 0;
	}
	else m_fStart_NewMissleTime += g_fDeltaTime;
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

void CTurret::StatusInit()
{
	m_StatusInfo.fHP = 3000;
	m_StatusInfo.fMaxHP = 3000;
	m_StatusInfo.fBase_Attack = 80;
	m_StatusInfo.fBase_Defence = 20;
	m_StatusInfo.fMagic_Defence = 30;
	m_StatusInfo.fAttackRange = 500;
}

void CTurret::UpdateStatus_Event(PHYSICALATTACKEVENT * Evt)
{
	D3DXVECTOR3 vDir = Evt->m_vecAttackPos - m_Info.vPos;
	float fDistance = D3DXVec3Length(&vDir);

	if (fDistance < 1.f)
	{
		m_StatusInfo.fHP -= Evt->m_infoDemage.fBase_Attack;
	}
}
