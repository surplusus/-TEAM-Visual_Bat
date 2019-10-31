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
	if (m_Champ_State[CHAMPION_STATETYPE_SPELL1] && m_fStartTime ==1) {
		AddSkill_Q();
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
	// ������ȯ
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
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, -1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, -1.f);
	m_Info.vPos = D3DXVECTOR3(0, 0, 0);

	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];

	D3DXCreateBox(GetDevice(), 1, 1, 1, &m_BoxMeseh, NULL);

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
	KeyCheck();
	SettingAnimationSort();
	SettingFrameAnimation();
	UpdateWorldMatrix();
	SetContantTable();
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
	//��� �ִϸ��̼��� ������ ���� �����Ѵ�.
	if (m_bDirty) {
		m_pAnimationCtrl->SetAnimationSet(m_strAnimationState);
		m_bDirty = false;
	}
	Mesh_Render(GetDevice(), L"Ezreal");
	SetTexture(0,NULL);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	CollisionBoxRender();
	SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}

void CEzreal::Release()
{

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
	if (GetAsyncKeyState(VK_LBUTTON) && 0x8001) {

		if (MouseCheck())
		{
			m_Champ_State[CHAMPION_STATETYPE_RUN]	  = true;
			m_Champ_State[CHAMPION_STATETYPE_ATTACK1] = true;
			m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
			m_bDirty = true;
			SetAngleFromPostion();
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
		m_fEndTime = 25;
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
			m_Champ_State[CHAMPION_STATETYPE_RUN] = false;

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
		else if (m_Champ_State[CHAMPION_STATETYPE_RUN])//�޸��� �����϶�
		{
			m_Champ_State[CHAMPION_STATETYPE_IDLE1] = false;
			m_AnimationQueue.push(CHAMPION_STATETYPE_RUN);
			
			m_ChangeMotion = false;
		}
		if (m_Champ_State[CHAMPION_STATETYPE_RUN] && !m_ChangeMotion) {
			TurnSlowly(&m_MouseHitPoint);
			bool bRun = Update_vPos_ByDestPoint(&m_MouseHitPoint, 5.0f);
			if (!bRun)
			{
				m_ChangeMotion = true;
				m_Champ_State[CHAMPION_STATETYPE_RUN] = false;
				m_AnimationQueue.pop();

			}
		}
		
	}
	if (!m_Champ_State[CHAMPION_STATETYPE_IDLE1] && m_ChangeMotion
		)
	{
		InitAnimationState();
		m_AnimationQueue.push(CHAMPION_STATETYPE_IDLE1);
		m_bDirty = true;
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

void CEzreal::CollisionBoxRender()
{
	m_BoxMeseh->DrawSubset(0);
}




