#include "BaseInclude.h"
#include "Ezreal.h"
#include "ThreadPool.h"
#include "BaseInclude.h"
#include"PipeLine.h"
#include "ObjMgr.h"
#include "Ray.h""
#include"ParticleMgr.h"
#include"EzealQ_Particle.h"
#include"ObjectColider.h"
#include"MathMgr.h"
#include"BoundingBox.h"
#include"CollisionMgr.h"
#include"EventMgr.h"
#include"HP.h"
#include"PickingSphereMgr.h"
#include"Factory.h"
#include"ChampGauge.h"
#include"BaseAttack.h"
#include"ParticleColider.h"
#include"GameHUD.h"
#include"Input.h"
D3DXVECTOR3 CEzreal::g_MouseHitPoint = D3DXVECTOR3(0, 0, 0);
std::atomic<bool> CEzreal::g_bMouseHitPoint = false;

CEzreal::CEzreal()
	:m_bDirty(true),m_pMesh(NULL), m_fStartTime(0)
{

	m_CurStateType = CHAMPION_STATETYPE_IDLE1;
	m_fAngle[ANGLE_X] = 0;
	m_fAngle[ANGLE_Y] = 1.5;
	m_fAngle[ANGLE_Z] = 0;
	m_fStartTime = 0.f;
	m_fEndTime = 0.f;
	m_Champ_State.resize(CHAMPION_STATETYPE_END_ANIMSTATE);
	for (int i = 0; i <CHAMPION_STATETYPE_END_ANIMSTATE; i++)
	{
		m_Champ_State[i] = false;
	}
	m_strAnimationState = "IDLE1";
	m_ChangeMotion = true;
	TestMeshName = L"Ezreal";
	StatusInitalize();
}


CEzreal::~CEzreal()
{

}

void CEzreal::SetContantTable()
{

	D3DXMATRIX		matView, matProj;
	GetTransform(D3DTS_VIEW, &matView);
	GetTransform(D3DTS_PROJECTION, &matProj);
	if (m_Champ_State[CHAMPION_STATETYPE_SPELL1] && m_fStartTime ==1) {
		AddSkill_Q();
	}
	if (m_Champ_State[CHAMPION_STATETYPE_ATTACK1] && m_fStartTime == 1) {
		TurnSlowly(&m_MouseHitPoint,1.0f);
		UpdateWorldMatrix();
		AddBaseAttack();
	}
}

void CEzreal::WorldSetting()
{
	D3DXMATRIX matRotX, matRotY, matRotZ, matTrans, matScale;
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngle[ANGLE_X]));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle[ANGLE_Y]));
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle[ANGLE_Z]));
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
	m_Info.matWorld = matScale*matRotX*matRotY*matRotZ*matTrans;
	CPipeLine::MyVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &m_Info.matWorld);
}

bool CEzreal::MouseCheck()
{
	// 방향전환
	if (MyGetMouseState().rgbButtons[0]) {
		m_bPicked = SearchPickingPointInHeightMap(GetVertexNumInHeightMap(), GetVertexInHeightMap());
	}	
	return m_bPicked;
}

void CEzreal::SetAngleFromPostion()
{
	D3DXVECTOR3 vUp = { 0,1.0f,0.0f };
	D3DXVECTOR3 vDirection = m_Info.vPos - g_MouseHitPoint;
	D3DXVec3Normalize(&vDirection, &vDirection);
}



HRESULT CEzreal::Initialize()
{
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, -1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, -1.f);
	m_Info.vPos = D3DXVECTOR3(0, 0, 0);

	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];
	m_ObjName = "Ezreal";

	D3DXMatrixIdentity(&m_Info.matWorld);
	CloneMesh(GetDevice(), TestMeshName, &m_pAnimationCtrl);
	D3DXMATRIX BonMatrix;
	GetBoneMatrix(TestMeshName, "Armature_root", &BonMatrix);
	m_pAnimationCtrl->GetAniCtrl();
	
	g_MouseHitPoint = m_Info.vPos;
	WorldSetting();

	m_pColider = new CObjectColider(this);
	//>> 콜라이더 생성
	INFO pInfo = m_Info;	
	m_pColider->SetUp(m_Info, 2.0f,new CBoundingBox);
	m_ColiderList.push_back(m_pColider);
	GET_SINGLE(CParticleMgr)->InsertColList(this,&m_ColiderList);
	GET_SINGLE(CCollisionMgr)->InsertColistion(this, &m_ColiderList);
	GET_SINGLE(EventMgr)->Subscribe(this,&CEzreal::PaticleCollisionEvent);
	GET_SINGLE(EventMgr)->Subscribe(this, &CEzreal::OnFindPickingSphere);
	GET_SINGLE(CPickingSphereMgr)->AddSphere(this, m_pColider->GetSphere());
	//스킬레벨 설정
	m_SkillLevel.resize(4);
	m_SkillLevel = { SKILL_LEVEL1,SKILL_LEVEL0 ,SKILL_LEVEL0 ,SKILL_LEVEL0 };
	StatusInitalize();
	
	return S_OK;
}

void CEzreal::Progress()
{
	if (m_bProgress) {
		KeyCheck();
	}
	SettingAnimationSort();
	SettingFrameAnimation();
	UpdateWorldMatrix();

	if ( !(m_Champ_State[CHAMPION_STATETYPE_DEATH] && m_fStartTime >= m_fEndTime)) {
		m_pAnimationCtrl->FrameMove(TestMeshName, g_fDeltaTime);
	}
	if(m_pColider)	m_pColider->Update(m_Info.vPos);
	SetContantTable();
	GET_SINGLE(cGameHUD)->SetInfoChamp(m_StatusInfo);


}
void CEzreal::AddSkill_Q()
{	
	D3DXMATRIX matWorld;
	D3DXVECTOR3 vPos;
	GetBoneMatrix(TestMeshName, "Armature_L_hand", &matWorld);
	vPos.x = matWorld._41;	vPos.y = matWorld._42;	vPos.z = matWorld._43;
	INFO tInfo = m_Info;
	tInfo.vPos = vPos;
	float fMana =0;
	switch (m_SkillLevel[SKILL_Q])
	{
	case SKILL_LEVEL0: return;
	case SKILL_LEVEL1: fMana = 50.0f; break;
	case SKILL_LEVEL2: fMana = 60.0f; break;
	case SKILL_LEVEL3: fMana = 70.0f; break;
	case SKILL_LEVEL4: fMana = 80.0f; break;
	}
	if (m_StatusInfo.fMana > fMana) {
		CParticle * p = new CEzealQ_Particle(tInfo, 10.0f, D3DXVECTOR3(m_fAngle[ANGLE_X], m_fAngle[ANGLE_Y], m_fAngle[ANGLE_Z]));
		p->Initalize();
		if (dynamic_cast<CEzealQ_Particle*>(p)->StatusInit(&m_StatusInfo, m_SkillLevel[SKILL_Q])) {
			m_ColiderList.push_back(dynamic_cast<CEzealQ_Particle*>(p)->GetColider());
			GET_SINGLE(CCollisionMgr)->InsertColistion(this, &m_ColiderList);
			GET_SINGLE(CParticleMgr)->AddParticle(this, p);
		}
	}
	std::cout <<"마나량" <<m_StatusInfo.fMana<<endl;
}

void CEzreal::AddBaseAttack()
{
	D3DXMATRIX matWorld;
	D3DXVECTOR3 vPos;
	GetBoneMatrix(TestMeshName, "Armature_L_hand", &matWorld);
	vPos.x = matWorld._41;	vPos.y = matWorld._42;	vPos.z = matWorld._43;
	INFO tInfo = m_Info;
	tInfo.vPos = vPos;
	CParticle * p = new CBaseAttack(tInfo, 10.0f, D3DXVECTOR3(m_fAngle[ANGLE_X], m_fAngle[ANGLE_Y], m_fAngle[ANGLE_Z]),m_StatusInfo);
	p->Initalize();
	m_ColiderList.push_back(dynamic_cast<CBaseAttack*>(p)->GetColider());
	GET_SINGLE(CCollisionMgr)->InsertColistion(this, &m_ColiderList);
	GET_SINGLE(CParticleMgr)->AddParticle(this, p);
}

void CEzreal::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	//몇개의 애니메이션이 돌지에 대해 설정한다.
	if (m_bDirty) {
		m_pAnimationCtrl->SetAnimationSet(m_strAnimationState);
		m_bDirty = false;
	}
	
	Mesh_Render(GetDevice(), TestMeshName);
	SetTexture(0,NULL);	
}

void CEzreal::Release()
{
	SAFE_DELETE(m_pColider);
	m_HpBar->Release();
	SAFE_DELETE(m_HpBar);
	m_HpBar = NULL;
}


void CEzreal::ChangeAniSetByState()
{

}

void CEzreal::SettingFrameAnimation()
{
	if (m_CurStateType == CHAMPION_STATETYPE_DEATH)
	{
		m_strAnimationState = "Death";		
		
		return;
	}
	
	switch (m_CurStateType)
	{
	case CHAMPION_STATETYPE_IDLE1:
		m_strAnimationState = "IDLE1"; break;
	case CHAMPION_STATETYPE_IDLE2:			
		m_strAnimationState = "IDLE2"; break;
	case CHAMPION_STATETYPE_IDLE3:
		m_strAnimationState = "IDLE3"; break;
	case CHAMPION_STATETYPE_ATTACK1:
		m_strAnimationState = "Attack1"; break;
	case CHAMPION_STATETYPE_ATTACK2:
		m_strAnimationState = "Attack2"; break;
	case CHAMPION_STATETYPE_SPELL1:	
		m_strAnimationState = "Spell1"; break;
	case CHAMPION_STATETYPE_SPELL2: 		
		m_strAnimationState = "Spell2"; break;
	case CHAMPION_STATETYPE_SPELL3: 
		m_strAnimationState = "Spell3"; break;
	case CHAMPION_STATETYPE_SPELL4:
		m_strAnimationState = "Spell4"; break;
	case CHAMPION_STATETYPE_RUN:	
		m_strAnimationState = "Run"; break;
	case CHAMPION_STATETYPE_DEATH:
		m_strAnimationState = "Death"; break;
	case CHAMPION_STATETYPE_DEFAULT_ACTION:
		m_strAnimationState = "Default_Action"; break;
	default:
		break;
	}
}

void CEzreal::KeyCheck()
{
	if (GetAsyncKeyState(VK_LBUTTON) )
	{
		if (MouseCheck())
		{
			SPHERE* spherePicked = nullptr;
			bool bPickSphere = GET_SINGLE(CPickingSphereMgr)->GetSpherePicked(this, &spherePicked);
			if (bPickSphere)
				m_Champ_State[CHAMPION_STATETYPE_ATTACK1] = true;
			else if (!bPickSphere)
				m_Champ_State[CHAMPION_STATETYPE_RUN] = true;

			m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
			m_bDirty = true;
			SetAngleFromPostion();
			m_fStartTime = 0;
		}
	}
	else if (CheckPushKeyOneTime(VK_Q))
	{
		m_Champ_State[CHAMPION_STATETYPE_SPELL1] = true;
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
		m_fEndTime = 25;
		m_bDirty = true;
	}	
	
}

void CEzreal::SettingAnimationSort()
{

	CHAMPION_STATETYPE Check = CHAMPION_STATETYPE_IDLE1;
	
	if (SettingDeath_Motion()==CHAMPION_STATETYPE_DEATH)
	{
		m_bDirty = true;
		m_CurStateType = CHAMPION_STATETYPE_DEATH;
		return;
	}
	else if (SettingDeath_Motion() == CHAMPION_STATETYPE_END_ANIMSTATE)
	{
		m_bDirty = false;
		return;
	}
	if (!m_Champ_State[CHAMPION_STATETYPE_IDLE1])
	{

		if(Check == CHAMPION_STATETYPE_IDLE1) Check =SettingSpell1_Motion();
		if(Check == CHAMPION_STATETYPE_IDLE1) Check =SettingAttack_Motion();
		if(Check == CHAMPION_STATETYPE_IDLE1) Check =SettingRun_Motion();
		
		
		m_CurStateType = Check;
	}


	if (m_Champ_State[CHAMPION_STATETYPE_IDLE1] && m_ChangeMotion
		)
	{
		InitAnimationState();
		m_bDirty = true;
		m_ChangeMotion = false;		
	}
}

void CEzreal::InitAnimationState()
{
	for (int i = 0; i<m_Champ_State.size(); i++)
	{
		m_Champ_State[i] = false;
	}
	m_Champ_State[CHAMPION_STATETYPE_IDLE1] = true;
}

void CEzreal::InitUpdate()
{
	list<ColiderComponent*>::iterator iter = m_ColiderList.begin();
	for (iter; iter != m_ColiderList.end();)
	{
		if (*iter == NULL)
		{
			iter = m_ColiderList.erase(iter);
		}
		else iter++;
	}
}

void CEzreal::PaticleCollisionEvent(COLLISIONEVENT* Evt)
{
	if (dynamic_cast<CChampion*>(Evt->m_pOriObj)->GetStateType() != CHAMPION_STATETYPE_DEATH) 
	{
		dynamic_cast<CChampion*>(Evt->m_pOriObj)->GetStatusInfo()->fHP -= (dynamic_cast<CParticleColider*>(Evt->m_pOriCol))->GetParticle()->GetStatus().fBase_Attack;
		if (m_StatusInfo.fHP < 0)
		{
			m_Champ_State[CHAMPION_STATETYPE_DEATH] = true;
			if (m_fStartTime <= 0)		m_fStartTime = 0;
			m_bProgress = false;
			m_bDirty = true;
			dynamic_cast<CChampion*>(Evt->m_pOriObj);
		}
	}
	m_bColl = false;
	std::cout <<"HP" <<m_StatusInfo.fHP<<endl;
}

void CEzreal::OnFindPickingSphere(PICKSPHEREEVENT * evt)
{
	m_pTargetObj = evt->m_pObj;
}

CHAMPION_STATETYPE CEzreal::SettingSpell1_Motion()
{
	if (m_Champ_State[CHAMPION_STATETYPE_SPELL1])
	{
		InitAnimationState();
		m_Champ_State[CHAMPION_STATETYPE_SPELL1] = true;
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
		m_ChangeMotion = false;
		//시간이 다 지나을때에 대한 모션
		if (m_fStartTime >= m_fEndTime) {
			InitAnimationState();
			m_ChangeMotion = true;
			m_fStartTime = 0;
			m_bDirty = true;
			return CHAMPION_STATETYPE_IDLE1;
		}		
		m_fStartTime += 1;
		return CHAMPION_STATETYPE_SPELL1;		
	}
	return CHAMPION_STATETYPE_IDLE1;
}

CHAMPION_STATETYPE CEzreal::SettingAttack_Motion()
{
	if (m_Champ_State[CHAMPION_STATETYPE_ATTACK1])
	{
		
		InitAnimationState();
		m_Champ_State[CHAMPION_STATETYPE_ATTACK1] = true;
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
		m_ChangeMotion = false;
		m_fEndTime = 25;
		m_CurStateType = CHAMPION_STATETYPE_ATTACK1;
			
		if (m_fStartTime >= m_fEndTime &&
			m_CurStateType == CHAMPION_STATETYPE_ATTACK1) 
		{
			InitAnimationState();
			m_Champ_State[CHAMPION_STATETYPE_ATTACK1] = false;
			m_Champ_State[CHAMPION_STATETYPE_IDLE1] = true;
			m_ChangeMotion = true;
			m_fStartTime = 0;
			m_bDirty = true;
			return CHAMPION_STATETYPE_IDLE1;
		}
		m_fStartTime += 1;
		return CHAMPION_STATETYPE_ATTACK1;

	}
	
	
	return CHAMPION_STATETYPE_IDLE1;
}

CHAMPION_STATETYPE CEzreal::SettingRun_Motion()
{
	bool Check = false;
	if (m_Champ_State[CHAMPION_STATETYPE_RUN] )//달리는 상태일때
	{

		InitAnimationState();
		m_Champ_State[CHAMPION_STATETYPE_RUN]	= true;
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
		m_ChangeMotion = false;
		Check = true;

		TurnSlowly(&m_MouseHitPoint);
		bool bRun = Update_vPos_ByDestPoint(&m_MouseHitPoint, 5.0f);
		if (!bRun)
		{
			m_ChangeMotion = true;
			m_Champ_State[CHAMPION_STATETYPE_RUN] = false;
			m_Champ_State[CHAMPION_STATETYPE_IDLE1] = true;
			Check = false;
		}
	}

	if (Check) return CHAMPION_STATETYPE_RUN;
		
	return CHAMPION_STATETYPE_IDLE1;

}

CHAMPION_STATETYPE CEzreal::SettingDeath_Motion()
{
	if (m_Champ_State[CHAMPION_STATETYPE_DEATH])
	{
		InitAnimationState();
		m_Champ_State[CHAMPION_STATETYPE_DEATH] = true;
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
		m_ChangeMotion = true;
		m_fEndTime = 25;
		if (m_fStartTime >= m_fEndTime )
		{
			InitAnimationState();
			m_Champ_State[CHAMPION_STATETYPE_DEATH] = true;
			m_ChangeMotion = true;
			m_bDirty = true;
			return CHAMPION_STATETYPE_END_ANIMSTATE;
		}
		m_fStartTime += 1;
		return CHAMPION_STATETYPE_DEATH;
	}
	return CHAMPION_STATETYPE_IDLE1;
}

void CEzreal::StatusInitalize()
{

	m_StatusInfo.fBase_Attack = 30;
	m_StatusInfo.fMoveSpeed = 200;
	m_StatusInfo.fAttackRange = 200;
	m_StatusInfo.fHP = 150;
	m_StatusInfo.fMana = 300;
	m_StatusInfo.fBase_Defence = 5;
	m_StatusInfo.fMagic_Defence = 5;
	m_StatusInfo.fCriticalRatio = 0;
	m_StatusInfo.fSkillTimeRatio = 0;

}

