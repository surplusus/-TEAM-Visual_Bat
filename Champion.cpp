#include "BaseInclude.h"
#include "Champion.h"
#include"MathMgr.h"
#include"PipeLine.h"
#include "ObjMgr.h"

CChampion::CChampion()
	:m_fCamDistance(1.f)
{
	m_fAngle[0] = 0.0f;		m_fAngle[1] = 0.0f;		m_fAngle[2] = 0.0f;

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
	const VTXTEX* vtx = m_ObjMgr->GetVtxInfo(L"Map_SommonMap");
	int number = m_ObjMgr->GetVtxNumber(L"Map_SommonMap");

	if (vtx == NULL) return false;


	for (int i = 0; i < number; i += 3) {
		D3DXVECTOR3 V0 = vtx[i].vPosition;
		D3DXVECTOR3 V1 = vtx[i + 1].vPosition;
		D3DXVECTOR3 V2 = vtx[i + 2].vPosition;

		if (CheckPickingOnTriangle(&V0, &V1, &V2, &m_vecMouseHitPoint))
		{
			return true;
		}
	}
	return false;
}

void CChampion::SetCameraPos()
{

}

void CChampion::SetContantTable()
{

}

