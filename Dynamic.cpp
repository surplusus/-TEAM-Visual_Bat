#include "BaseInclude.h"
#include "Dynamic.h"


CDynamic::CDynamic()
	: m_bMove(false)
	, m_pAnimationCtrl(NULL)
{
}


CDynamic::~CDynamic()
{
	Release();
}

bool CDynamic::Move_Chase(const D3DXVECTOR3 * pDestPoint, const float & fSpeed)
{
	D3DXVECTOR3 vDirection = *pDestPoint - m_Info.vPos;
	float fDistance = D3DXVec3Length(&vDirection);

	D3DXVec3Normalize(&vDirection, &vDirection);
	m_Info.vPos += vDirection*fSpeed*GetTime();
	if (fDistance < 0.1f)
		return false;
	return false;
}

void CDynamic::Release()
{
	if (m_pAnimationCtrl)
	{
		delete m_pAnimationCtrl;
		m_pAnimationCtrl = NULL;
	}
}
