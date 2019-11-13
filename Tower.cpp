#include "BaseInclude.h"
#include "Tower.h"
#include "MathMgr.h"
#include "PipeLine.h"
#include "ThreadPool.h"
#include "ObjMgr.h"
#include "Ray.h"
#include "MathMgr.h"
#include "HeightMap.h"



CTower::CTower()
{
	m_ObjMgr = GET_SINGLE(CObjMgr);

	
}

CTower::~CTower()
{
	
}

void CTower::UpdateWorldMatrix()
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

const VTXTEX * CTower::GetVertexInHeightMap()
{
	return m_pHeightMap->GetVtxInfo();
}

DWORD & CTower::GetVertexNumInHeightMap()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_pHeightMap->m_VtxNum;
}

void CTower::SetHeightMap(CHeightMap * pHeightMap)
{
	m_pHeightMap = pHeightMap;
}
