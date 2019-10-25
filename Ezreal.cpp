#include "BaseInclude.h"
#include "Ezreal.h"
#include "ThreadPool.h"
#include "BaseInclude.h"
#include "Atrox.h"
#include"PipeLine.h"
#include "ObjMgr.h"
#include "Ray.h""
#include"ParticleMgr.h"
#include"EzealQ_Particle.h"
D3DXVECTOR3 CEzreal::g_MouseHitPoint = D3DXVECTOR3(0, 0, 0);
std::atomic<bool> CEzreal::g_bMouseHitPoint = false;

CEzreal::CEzreal()
{
	m_fAngle[ANGLE_X] = 0;
	m_fAngle[ANGLE_Y] = 0;
	m_fAngle[ANGLE_Z] = 0;

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
	D3DXMatrixRotationX(&matRotX, m_fAngle[ANGLE_X]);
	D3DXMatrixRotationY(&matRotY, m_fAngle[ANGLE_Y]);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle[ANGLE_Z]);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
	m_Info.matWorld = matScale*matRotX*matRotY*matRotZ*matTrans;
	CPipeLine::MyVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &m_Info.matWorld);
}

bool CEzreal::MouseCheck()
{
	if (m_ObjMgr == NULL) return false;
	const VTXTEX* vtx = m_ObjMgr->GetVtxInfo(L"Map");
	int number = m_ObjMgr->GetVtxNumber(L"Map");

	if (vtx == NULL) return false;
	if (GET_THREADPOOL->EnqueueFunc(THREAD_MOUSE, MapChecktThreadLoop, number, vtx).get())
	{
		GET_THREADPOOL->Thread_Stop(THREAD_MOUSE);
		return true;
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
	m_Info.vPos += vDirection * fSpeed*GetTime();
	if (fDistance < 0.1f)
		return false;
	return false;
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
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = D3DXVECTOR3(0, 0, 0);

	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];


	D3DXMatrixIdentity(&m_Info.matWorld);
	CloneMesh(GetDevice(), L"Ezreal", &m_pAnimationCtrl);

	m_vMin = *(GetMin(BOUNDTYPE_CUBE));
	m_vMax = *(GetMax(BOUNDTYPE_CUBE));
	g_MouseHitPoint = m_Info.vPos;
	WorldSetting();
	


	return S_OK;
}

void CEzreal::Progress()
{
	WorldSetting();
	//KeyCheck();
	if (GetAsyncKeyState(VK_LBUTTON)) {

		if (MouseCheck())
		{
			SetAngleFromPostion();

		}
	}
	if (g_bMouseHitPoint) {
		g_bMouseHitPoint = false;
	}
	if (CheckPushKeyOneTime(VK_Q))
	{
		AddSkill_Q();
	}
	Move_Chase(&g_MouseHitPoint, 10.0f);
	for (list<CParticle*>::iterator iter = m_ListQSkill.begin(); iter != m_ListQSkill.end(); ++iter)
	{
		(*iter)->Progress();
	}
}
void CEzreal::AddSkill_Q()
{	
	D3DXMATRIX matWorld;
	D3DXVECTOR3 vPos;
	GetBoneMatrix(L"Ezreal", "Armature_L_Hand", &matWorld);
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
	
	m_pAnimationCtrl->SetAnimationSet("Left_Attack2");
	m_pAnimationCtrl->FrameMove(L"Ezreal", GetTime()/30);
	Mesh_Render(GetDevice(), L"Ezreal");
}

void CEzreal::Release()
{

}



