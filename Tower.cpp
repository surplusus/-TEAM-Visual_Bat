#include "BaseInclude.h"
#include "Tower.h"
#include "MathMgr.h"
#include "PipeLine.h"
#include "ThreadPool.h"
#include "ObjMgr.h"
#include "Ray.h"
#include "MathMgr.h"
#include "HeightMap.h"


CTower::CTower(string name, ST_ABILITY Ability)
{
	m_ObjMgr = GET_SINGLE(CObjMgr);

	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vPos = D3DXVECTOR3(-10.f, 18.f, -10.f);
	m_fHeight = 0.0f;
}

CTower::~CTower()
{
	
}

void CTower::UpdateWorldMatrix()
{
	D3DXMATRIX	matRotX, matRotY, matRotZ;
	D3DXMATRIX	matS, matR, matT;
	D3DXMatrixScaling(&matS, m_fSize, m_fSize, m_fSize);
	if (_isnan(m_fAngle[ANGLE_Y]))
		m_fAngle[ANGLE_Y] = 0.f;
	D3DXMatrixRotationY(&matR, m_fAngle[ANGLE_Y]);
	D3DXVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &matR);
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
