#include "BaseInclude.h"
#include "Ezreal.h"
#include "ThreadPool.h"
#include "BaseInclude.h"
#include"PipeLine.h"
#include "ObjMgr.h"
#include "Ray.h""
#include"ParticleMgr.h"
#include"EzealQ_Particle.h"
#include"MathMgr.h"
D3DXVECTOR3 CEzreal::g_MouseHitPoint = D3DXVECTOR3(0, 0, 0);
std::atomic<bool> CEzreal::g_bMouseHitPoint = false;

CEzreal::CEzreal()
	:m_bDirty(true)
{
	m_fAngle[ANGLE_X] = 0;
	m_fAngle[ANGLE_Y] = 0;
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
}


CEzreal::~CEzreal()
{

}

void CEzreal::SetContantTable()
{

	D3DXMATRIX		matView, matProj;
	GetTransform(D3DTS_VIEW, &matView);
	GetTransform(D3DTS_PROJECTION, &matProj);
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
//	CPipeLine::MyVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &m_Info.matWorld);
}

bool CEzreal::MouseCheck()
{
	if (m_ObjMgr == NULL) return false;
	const VTXTEX* vtx = m_ObjMgr->GetVtxInfo(L"Map");
	int number = m_ObjMgr->GetVtxNumber(L"Map");

	/*if (vtx == NULL) return false;
	if (GET_THREADPOOL->EnqueueFunc(THREAD_MOUSE, MapChecktThreadLoop, number, vtx).get())
	{
		GET_THREADPOOL->Thread_Stop(THREAD_MOUSE);		return true;
	}
*/
	if (MyGetMouseState().rgbButtons[0]) {
		m_bPicked = SearchPickingPointInHeightMap(GetVertexNumInHeightMap(), GetVertexInHeightMap());
	}


	return false;
}

void CEzreal::SetAngleFromPostion()
{
	D3DXVECTOR3 vUp = { 0,1.0f,0.0f };
	D3DXVECTOR3 vDirection = m_Info.vPos - g_MouseHitPoint;
	D3DXVec3Normalize(&vDirection, &vDirection);
}

bool CEzreal::Move_Chase(const D3DXVECTOR3 * pDestPoint, const float & fSpeed)
{
	D3DXVECTOR3 vDirection = *pDestPoint - m_Info.vPos;
	float fDistance = D3DXVec3Length(&vDirection);

	D3DXVec3Normalize(&vDirection, &vDirection);
	m_Info.vPos += vDirection * g_fDeltaTime*fSpeed;
	if (fDistance < 0.1f)
		return false;

	return true;
}

bool CEzreal::MapChecktThreadLoop(int number, const VTXTEX * vtx)
{
	CRay m_Ray;		POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_Ray = CRay::RayAtWorldSpace(pt.x, pt.y);


	for (int i = 0; i < number; i += 3) {
		D3DXVECTOR3 V0 = vtx[i].vPosition;
		D3DXVECTOR3 V1 = vtx[i + 1].vPosition;
		D3DXVECTOR3 V2 = vtx[i + 2].vPosition;

		if (m_Ray.IsPicked(g_MouseHitPoint, V0, V1, V2))
		{
			g_bMouseHitPoint = true;
			return true;
		}
	}
	return false;
}



HRESULT CEzreal::Initialize()
{
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vPos = D3DXVECTOR3(0, 0, 0);

	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];


	D3DXMatrixIdentity(&m_Info.matWorld);
	CloneMesh(GetDevice(), L"Ezreal", &m_pAnimationCtrl);

	m_vMin = *(GetMin(BOUNDTYPE_CUBE));
	m_vMax = *(GetMax(BOUNDTYPE_CUBE));
	g_MouseHitPoint = m_Info.vPos;
	WorldSetting();
	
	m_pMesh = GetMesh(L"Ezreal");

	return S_OK;
}

void CEzreal::Progress()
{
	WorldSetting();
	KeyCheck();
	SettingAnimationSort();
	SettingFrameAnimation();
	for (list<CParticle*>::iterator iter = m_ListQSkill.begin(); iter != m_ListQSkill.end(); ++iter)
	{
		(*iter)->Progress();
	}
	m_pAnimationCtrl->FrameMove(L"Ezreal", g_fDeltaTime);
	
}
void CEzreal::AddSkill_Q()
{	
	D3DXMATRIX matWorld;
	D3DXVECTOR3 vPos;
	GetBoneMatrix(L"Ezreal", "Armature_L_hand", &matWorld);
	vPos.x = matWorld._41;	vPos.y = matWorld._42;	vPos.z = matWorld._43;
	INFO tInfo = m_Info;
	tInfo.vPos = vPos;
	CParticle * p = new CEzealQ_Particle(tInfo,10.0f,D3DXVECTOR3(m_fAngle[ANGLE_X], m_fAngle[ANGLE_Y], m_fAngle[ANGLE_Z]));
	p->Initalize();
	GET_SINGLE(CParticleMgr)->AddParticle(L"Ez", p);
}

void CEzreal::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	//몇개의 애니메이션이 돌지에 대해 설정한다.
	if (m_bDirty) {
		m_pAnimationCtrl->SetAnimationSet(m_strAnimationState);
		m_bDirty = false;
	}
	Mesh_Render(GetDevice(), L"Ezreal");



}

void CEzreal::Release()
{

}

void CEzreal::RoationObject()
{
	D3DXVECTOR3 Pre_Position	=	 m_Info.vPos;
	D3DXVECTOR3 After_Position	=	 g_MouseHitPoint;
	D3DXVECTOR3 vCurDirection	=	 m_Info.vLook * -1.f;

	
	D3DXVECTOR3 vDirection = After_Position-Pre_Position;

	float fDistance = D3DXVec3Length(&vDirection);


	D3DXVec3Normalize(&vDirection, &vDirection);
	D3DXVec3Normalize(&vCurDirection, &vCurDirection);

	float Dot = 0;	float Radian = 0;
	Dot = D3DXVec3Dot(&vDirection, &vCurDirection);
	Radian = (float)acos(Dot);
	D3DXVECTOR3 Right_Dir;
	D3DXVec3Cross(&Right_Dir, &vDirection, &D3DXVECTOR3(0, 0, -1));
	if(Right_Dir.y < 0)
	{
		m_fAngle[ANGLE_Y] =	D3DXToDegree(Radian);
		CMathMgr::Rotation_Y(&m_Info.vDir, &m_Info.vDir, D3DXToRadian(m_fAngle[ANGLE_Y]));
	}
	else
	{
		m_fAngle[ANGLE_Y] = 360- D3DXToDegree (Radian);
		CMathMgr::Rotation_Y(&m_Info.vDir, &m_Info.vDir, D3DXToRadian(m_fAngle[ANGLE_Y]));
	}	
}

void CEzreal::ChangeAniSetByState()
{

}

void CEzreal::SettingFrameAnimation()
{
	CHAMPION_STATETYPE eState;
	if (m_AnimationQueue.empty()) {
		eState = CHAMPION_STATETYPE_IDLE1;
	}
	else	eState = m_AnimationQueue.front();
	switch (eState)
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
	if(!m_AnimationQueue.empty())	m_AnimationQueue.pop();
}

void CEzreal::KeyCheck()
{
	if (GetAsyncKeyState(VK_LBUTTON)) {

		if (MouseCheck())
		{
			m_Champ_State[CHAMPION_STATETYPE_RUN]	  = true;
			m_Champ_State[CHAMPION_STATETYPE_ATTACK1] = true;
			m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
			m_bDirty = true;
			SetAngleFromPostion();
			RoationObject();
		}
	}
	if (g_bMouseHitPoint) {
		g_bMouseHitPoint = false;
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;

	}
	if (CheckPushKeyOneTime(VK_Q))
	{
		m_Champ_State[CHAMPION_STATETYPE_SPELL1] = true;
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
		AddSkill_Q();
		m_fEndTime = 25;
		m_bDirty = true;
	}
	else if (!Move_Chase(&g_MouseHitPoint, 5.0f) 
		&& !m_Champ_State[CHAMPION_STATETYPE_IDLE1] && m_ChangeMotion
		)
	{
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = true;
		m_bDirty = true;
	}
	for (list<CParticle*>::iterator iter = m_ListQSkill.begin(); iter != m_ListQSkill.end(); ++iter)
	{
		(*iter)->Progress();
	}
}

void CEzreal::SettingAnimationSort()
{
	if (!m_Champ_State[CHAMPION_STATETYPE_IDLE1])
	{
		if (m_Champ_State[CHAMPION_STATETYPE_SPELL1])
		{
			m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
			m_ChangeMotion = false;
			if (m_fStartTime >= m_fEndTime) {
				m_Champ_State[CHAMPION_STATETYPE_SPELL1] = false;
				m_Champ_State[CHAMPION_STATETYPE_IDLE1] = true;
				m_ChangeMotion = true;
				m_fStartTime = 0;
				m_bDirty = true;
			}
			else
			{
				m_AnimationQueue.push(CHAMPION_STATETYPE_SPELL1);
				m_fStartTime += 1;

			}
		}
		else if (m_Champ_State[CHAMPION_STATETYPE_RUN])
		{
			m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
			m_AnimationQueue.push(CHAMPION_STATETYPE_RUN);
		}
	}
	else
	{
		m_Champ_State[CHAMPION_STATETYPE_IDLE1] = true;
		m_AnimationQueue.push(CHAMPION_STATETYPE_IDLE1);
		InitAnimationState();
	}	
}

void CEzreal::InitAnimationState()
{
	for (int i = 0; i > m_Champ_State.size(); i++)
	{
		m_Champ_State[i] = false;
	}
	m_Champ_State[CHAMPION_STATETYPE_IDLE1] = true;
}




