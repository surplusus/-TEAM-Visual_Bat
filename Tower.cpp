#include "BaseInclude.h"
#include "Tower.h"
#include "MathMgr.h"
#include "PipeLine.h"
#include "ThreadPool.h"
#include "ObjMgr.h"
#include "Ray.h"

//D3DXVECTOR3 CTower::g_MouseHitPoint = D3DXVECTOR3(0, 0, 0);
//std::atomic<bool> CTower::g_bHitFloor = false;
//bool CTower::bPick = false;


CTower::~CTower()
{
	m_ObjMgr = GET_SINGLE(CObjMgr);

	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vPos = D3DXVECTOR3(-10.f, 18.f, -10.f);
	m_fHeight = 0.0f;
}

void CTower::UpdateWorldMatrix()
{
}
