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
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_ObjMgr = GET_SINGLE(CObjMgr);

}

bool CChampion::CheckMousePickingOnFloor()
{
	if (m_ObjMgr == NULL) return false;
	const VTXTEX* vtx = m_ObjMgr->GetVtxInfo(L"Map_SommonMap");
	int number = m_ObjMgr->GetVtxNumber(L"Map_SommonMap");

	if (vtx == NULL) return false;
	if (g_ThreadPool->EnqueueJob(THREAD_MOUSE, MapChecktThreadLoop, number, vtx).get())
	{
		g_ThreadPool->Thread_Stop(THREAD_MOUSE);
		return true;
	}
	return false;
}

void CChampion::SetAngleFromPostion()
{
	D3DXVECTOR3 vUp = { 0,1.0f,0.0f };
	D3DXVECTOR3 vDirection = m_Info.vPos - g_MouseHitPoint;
	D3DXVec3Normalize(&vDirection,&vDirection);



	for (int i = 0; i < number; i += 3) {
		D3DXVECTOR3 V0 = vtx[i].vPosition;
		D3DXVECTOR3 V1 = vtx[i + 1].vPosition;
		D3DXVECTOR3 V2 = vtx[i + 2].vPosition;

		if (CheckPickingOnTriangle(&V0, &V1, &V2, &m_vecMouseHitPoint))
		{
			cout << m_vecMouseHitPoint.x << " " << m_vecMouseHitPoint.y << " " << m_vecMouseHitPoint.z << endl;
			return true;
		}
	}
	return false;
}

bool CChampion::MapChecktThreadLoop(int number, const VTXTEX * vtx)
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