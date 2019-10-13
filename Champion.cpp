#include "BaseInclude.h"
#include "Champion.h"
#include"MathMgr.h"
#include"PipeLine.h"
#include "ObjMgr.h"
#include"MyThreadPool.h"
#include "Ray.h"

D3DXVECTOR3 CChampion::g_MouseHitPoint = D3DXVECTOR3(0, 0, 0);
std::atomic<bool> CChampion::g_bMouseHitPoint = false;
bool CChampion::bPick = false;
CChampion::CChampion()
	:m_fCamDistance(1.f)
{
	m_fAngle[ANGLE_X] = 0.0f;		m_fAngle[ANGLE_Y] = 0.0f;		m_fAngle[ANGLE_Z] = 0.0f;
}


CChampion::~CChampion()
{
}

void CChampion::KeyCheck()
{
	
}

bool CChampion::MouseCheck()
{
	if (m_ObjMgr == NULL) return false;
	const VTXTEX* vtx = m_ObjMgr->GetVtxInfo(L"Map");
	int number = m_ObjMgr->GetVtxNumber(L"Map");

	if (vtx == NULL) return false;
	if (g_ThreadPool->EnqueueJob(THREAD_MOUSE, MapChecktThreadLoop, number, vtx).get())
	{
		g_ThreadPool->Thread_Stop(THREAD_MOUSE);
		return true;
	}
	return false;
}

void CChampion::SetCameraPos()
{
	
}

void CChampion::SetAngleFromPostion()
{
	D3DXVECTOR3 vUp = { 0,1.0f,0.0f };
	D3DXVECTOR3 vDirection = m_Info.vPos - g_MouseHitPoint;
	D3DXVec3Normalize(&vDirection,&vDirection);



}

void CChampion::SetContantTable()
{

}

bool CChampion::MapChecktThreadLoop(int number, const VTXTEX * vtx)
{

		CRay m_Ray;		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		m_Ray =CRay::RayAtWorldSpace(pt.x, pt.y);

	
	for (int i = 0; i <number; i += 3) {
		D3DXVECTOR3 V0 = vtx[i].vPosition;
		D3DXVECTOR3 V1 = vtx[i + 1].vPosition;
		D3DXVECTOR3 V2 = vtx[i + 2].vPosition;
		
		if (m_Ray.IsPicked(g_MouseHitPoint,V0, V1, V2))
		{
			g_bMouseHitPoint = true;
			return true;
		}
	}
	return false;
}

void CChampion::RenderDirection()
{	
	ST_PC_VERTEX lines[2];
	
	lines[0].p = m_Info.vPos;
	lines[0].c = 0xffffffff;
	lines[1].p = m_Info.vPos ;//m_Info.vPos+ m_Info.vDir*100.0f;	
	lines[1].p.x -= (m_Info.vPos.x - g_MouseHitPoint.x);	lines[1].p.z -= (m_Info.vPos.z - g_MouseHitPoint.z);
	lines[1].c = 0xffffffff;
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,0,1.0f,.0);
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld = matTrans;
	SetTransform(D3DTS_WORLD, &matWorld);
	GET_SINGLE(CDevice)->GetDevice()->SetFVF(ST_PC_VERTEX::FVF);
	GET_SINGLE(CDevice)->GetDevice()->SetTexture(0,NULL);
	SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	SetRenderState(D3DRS_LIGHTING, FALSE);
	GET_SINGLE(CDevice)->GetDevice()->DrawPrimitiveUP(D3DPT_LINELIST, 1, lines, sizeof(ST_PC_VERTEX));

}



