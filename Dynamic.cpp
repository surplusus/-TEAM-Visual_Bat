#include "BaseInclude.h"
#include "Dynamic.h"


CDynamic::CDynamic()
	: m_bMove(false)
	, m_fHeight(0.f)
	, m_pAnimationCtrl(NULL)
{
}


CDynamic::~CDynamic()
{
	Release();
}

bool CDynamic::Update_vPos_ByDestPoint(const D3DXVECTOR3 * pDestPoint, const float & fSpeed)
{
	D3DXVECTOR3 dir = *pDestPoint - m_Info.vPos;
	float fDistance = D3DXVec3Length(&dir);
	float speed = fSpeed;
	D3DXVec3Normalize(&dir, &dir);
	if (fDistance < 0.1f) {
		if (fDistance <= 0.001f) {
			m_Info.vPos = *pDestPoint;
			return false;
		}
		D3DXVec3Lerp(&m_Info.vPos, &m_Info.vPos, pDestPoint, 0.5f);
		return true;
	}

	m_Info.vPos += dir * speed * g_fDeltaTime;
	return true;
}

void CDynamic::Release()
{
	if (m_pAnimationCtrl)
	{
		delete m_pAnimationCtrl;
		m_pAnimationCtrl = NULL;
	}
}
