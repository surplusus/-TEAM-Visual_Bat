#include "BaseInclude.h"
#include "Champion.h"
#include"MathMgr.h"
#include"PipeLine.h"
#include "ObjMgr.h"

CChampion::CChampion()
{
	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_ObjMgr = GET_SINGLE(CObjMgr);
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
			cout << m_vecMouseHitPoint.x << " " << m_vecMouseHitPoint.y << " " << m_vecMouseHitPoint.z << endl;
			return true;
		}
	}
	return false;
}