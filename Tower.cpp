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

	m_fSize = 0.5f;

	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vDir =  D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos =  D3DXVECTOR3(0.f, 0.f, 0.f);
	m_fHeight = 0.0f;
}

CTower::~CTower()
{
	
}

void CTower::UpdateWorldMatrix()
{
	D3DXMATRIX	matS, matR, matT;
	D3DXMatrixScaling(&matS, m_fSize, m_fSize, m_fSize);
	D3DXMatrixRotationY(&matR, 1.5f);
	D3DXMatrixTranslation(&matT, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixIdentity(&m_Info.matWorld);
	m_Info.matWorld = matS * matR * matT;
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
