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

void CTower::UpdateWorldMatrix(float radian)
{
	D3DXMATRIX	matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, m_fSize, m_fSize, m_fSize);
	float yradian = D3DXToRadian(radian);
	D3DXMatrixRotationY(&matR, yradian);
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
