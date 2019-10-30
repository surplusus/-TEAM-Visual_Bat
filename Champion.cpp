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
	m_fHeight = 0.0f; // ³ôÀÌ¸Ê Àû¿ëÇÒ CDynamic ¸É¹ö
	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];
	D3DXMatrixIdentity(&m_Info.matWorld);

	m_vMin = *(GetMin(BOUNDTYPE_CUBE));
	m_vMax = *(GetMax(BOUNDTYPE_CUBE));
}


CChampion::~CChampion()
{

}

bool CChampion::TurnSlowly(const D3DXVECTOR3 * destPos)
{
	D3DXVECTOR3 vMousePos = *destPos - m_Info.vPos; vMousePos.y = m_fHeight;
	D3DXVECTOR3 vMouseNor;
	D3DXVec3Normalize(&vMouseNor, &vMousePos);
	if (_isnan(m_Info.vDir.y))	m_Info.vDir.y = vMouseNor.y;
	float fDot = D3DXVec3Dot(&m_Info.vDir, &vMouseNor);
	float fRadian = acosf(fDot);
	float fDirLerped = fRadian / 7.f;

	if (fabs(fRadian) <= D3DX_16F_EPSILON) {
		return false;
	}

	D3DXVECTOR3 vLeft;
	D3DXVec3Cross(&vLeft, &m_Info.vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));
	if (D3DXVec3Dot(&vMouseNor, &vLeft) > 0) {
		m_fAngle[ANGLE_Y] -= fDirLerped;
		if (m_fAngle[ANGLE_Y] < D3DX_PI)
			m_fAngle[ANGLE_Y] += 2.f * D3DX_PI;
	}
	else {
		m_fAngle[ANGLE_Y] += fDirLerped;
		if (m_fAngle[ANGLE_Y] > D3DX_PI)
			m_fAngle[ANGLE_Y] -= 2.f * D3DX_PI;
	}

	return false;
}

void CChampion::UpdateWorldMatrix()
{
	D3DXMATRIX matRotX, matRotY, matRotZ;
	D3DXMATRIX matScale, matRot, matTrans;
	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, m_fSize);
	if (_isnan(m_fAngle[ANGLE_Y]))
		m_fAngle[ANGLE_Y] = 0.f;
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
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
		mtrl.Diffuse.r = mtrl.Ambient.r = mtrl.Specular.r = 1.f;
		mtrl.Diffuse.g = mtrl.Ambient.g = mtrl.Specular.g = 0.f;
		mtrl.Diffuse.b = mtrl.Ambient.b = mtrl.Specular.b = 0.f;
		mtrl.Diffuse.a = mtrl.Ambient.a = mtrl.Specular.a = 1.f;

	GET_DEVICE->SetTexture(0, NULL);
	GET_DEVICE->SetMaterial(&mtrl);
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
