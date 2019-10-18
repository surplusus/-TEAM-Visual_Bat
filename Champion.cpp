#include "BaseInclude.h"
#include "Champion.h"
#include "MathMgr.h"
#include "PipeLine.h"
#include "ObjMgr.h"
#include "ThreadPool.h"
#include "Ray.h"

D3DXVECTOR3 CChampion::g_MouseHitPoint = D3DXVECTOR3(0, 0, 0);
std::atomic<bool> CChampion::g_bHitFloor = false;
bool CChampion::bPick = false;
CChampion::CChampion()
{
	m_ObjMgr = GET_SINGLE(CObjMgr);
	
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vPos = D3DXVECTOR3(-10.f, 18.0f, -10.f);
	m_fHeight = 18.0f; // 높이맵 적용할 CDynamic 맴버
	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];
	D3DXMatrixIdentity(&m_Info.matWorld);

	m_vMin = *(GetMin(BOUNDTYPE_CUBE));
	m_vMax = *(GetMax(BOUNDTYPE_CUBE));
	g_MouseHitPoint = m_Info.vPos;
}


CChampion::~CChampion()
{

}

void CChampion::UpdateWorldMatrix()
{
	D3DXMATRIX matRotX, matRotY, matRotZ;
	D3DXMATRIX matScale, matRot, matTrans;
	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, m_fSize);
	//D3DXMatrixRotationYawPitchRoll(&matRot, m_fAngle[ANGLE_X], m_fAngle[ANGLE_Y], m_fAngle[ANGLE_Z]);
	D3DXMatrixRotationX(&matRotX, m_fAngle[ANGLE_X]);
	D3DXMatrixRotationY(&matRotY, m_fAngle[ANGLE_Y]);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle[ANGLE_Z]);
	matRot = matRotX * matRotY * matRotZ;
	fill(&m_fAngle[ANGLE_X], &m_fAngle[ANGLE_END], 0.f);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	m_Info.matWorld = matScale * matRot * matTrans;
	CPipeLine::MyVec3TransformNormal(&m_Info.vDir, &m_Info.vDir, &m_Info.matWorld);
	//D3DXVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &m_Info.matWorld);
}

void CChampion::SetDirectionToMouseHitPoint()
{
	D3DXVECTOR3 vUp = { 0, 1.f, 0.f };
	m_Info.vDir = m_Info.vPos - g_MouseHitPoint;
	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
}

bool CChampion::EnqueueMousePickingFunc()
{
	// 쓰레드를 돌려 g_MouseHitPoint 과 g_bHitFloor 로 결과를 받는다.
	if (m_ObjMgr == NULL) return false;
	const VTXTEX* vtx = m_ObjMgr->GetVtxInfo(L"Map_Floor");
	int number = m_ObjMgr->GetVtxNumber(L"Map_Floor");

	if (vtx == NULL) return false;
	if (GET_THREADPOOL->EnqueueFunc(THREAD_MOUSE, MapCheckThreadLoop, number, vtx).get())
	{
		GET_THREADPOOL->Thread_Stop(THREAD_MOUSE);
		return true;
	}
	return false;
}

bool CChampion::MapCheckThreadLoop(int number, const VTXTEX * vtx)
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
			g_bHitFloor = true;
			return true;
		}
	}
	g_bHitFloor = false;
	return false;
}