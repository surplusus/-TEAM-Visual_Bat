#include "BaseInclude.h"
#include "Champion.h"
#include "MathMgr.h"
#include "PipeLine.h"
#include "ThreadPool.h"
#include "ObjMgr.h"
#include "Ray.h"
#include "MathMgr.h"
#include "HeightMap.h"
#include "PickingSphereMgr.h"

CChampion::CChampion()
	: m_ObjMgr(nullptr)
	, m_pHeightMap(nullptr)
	, m_fSize(1.f)
	, m_MouseHitPoint(0.f,0.f,0.f)
	, m_bPicked(false)
	, m_pMeshSphere(nullptr)
{
	m_ObjMgr = GET_SINGLE(CObjMgr);
	
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_fHeight = 0.0f; // ���̸� ������ CDynamic �ɹ�
	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];
	D3DXMatrixIdentity(&m_Info.matWorld);

	m_vMin = *(GetMin(BOUNDTYPE_CUBE));
	m_vMax = *(GetMax(BOUNDTYPE_CUBE));
}


CChampion::~CChampion()
{

}

void CChampion::UpdateWorldMatrix()
{
	D3DXMATRIX matRotX, matRotY, matRotZ;
	D3DXMATRIX matScale, matRot, matTrans;
	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, m_fSize);
	//if (_isnan(m_fAngle[ANGLE_Y]))	m_fAngle[ANGLE_Y] = 0.f;
	D3DXMatrixRotationY(&matRot, m_fAngle[ANGLE_Y]);
	D3DXVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &matRot);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixIdentity(&m_Info.matWorld);
	m_Info.matWorld = matScale * matRot * matTrans;
}

void CChampion::SetDirectionToMouseHitPoint()
{
	D3DXVECTOR3 vUp = { 0, 1.f, 0.f };
	m_Info.vDir = m_Info.vPos - m_MouseHitPoint;
	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
}

bool CChampion::SetUpPickingShere(const float r, D3DXVECTOR3* v)
{
	m_SphereForPick.fRadius = r;
	if (v == nullptr) {
		m_SphereForPick.vpCenter = &m_Info.vPos;
	}
	GET_SINGLE(CPickingSphereMgr)->AddSphere(this, &m_SphereForPick);
	HRESULT result = D3DXCreateSphere(GET_DEVICE, r, 10, 10, &m_pMeshSphere, NULL);
	return true;
}

bool CChampion::Render_PickingShere()
{
	if (m_pMeshSphere != NULL) {
		m_pMeshSphere->DrawSubset(0);
		return true;
	}
	return false;
}

bool CChampion::SearchPickingPointInHeightMap(int number, const VTXTEX * vtx)
{
	CRay m_Ray;		POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_Ray = CRay::RayAtWorldSpace(pt.x, pt.y);

	for (int i = 0; i < number; i += 3) {
		D3DXVECTOR3 V0 = vtx[i].vPosition;
		D3DXVECTOR3 V1 = vtx[i + 1].vPosition;
		D3DXVECTOR3 V2 = vtx[i + 2].vPosition;

		if (m_Ray.IsPicked(m_MouseHitPoint, V0, V1, V2))
		{
			return true;
		}
	}
	return false;
}

void CChampion::SetHeightMap(CHeightMap * pHeightMap)
{
	m_pHeightMap = pHeightMap;
}

const VTXTEX * CChampion::GetVertexInHeightMap()
{
	return m_pHeightMap->GetVtxInfo();
}

DWORD & CChampion::GetVertexNumInHeightMap()
{
	return m_pHeightMap->m_VtxNum;
}
