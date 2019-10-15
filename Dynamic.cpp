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

bool CDynamic::Update_vPos_ByDestPoint(const D3DXVECTOR3 * pDestPoint, const float & fSpeed)
{
	m_Info.vDir = *pDestPoint - m_Info.vPos;
	float fDistance = D3DXVec3Length(&m_Info.vDir);
	float speed = fSpeed;
	D3DXVec3Normalize(&m_Info.vDir, &m_Info.vDir);
	if (fDistance < 1.f)
	{
		speed = fSpeed / 10.f;
		if (fDistance < 0.1f)
			return false;
	}
	m_Info.vPos += m_Info.vDir * speed * GetTime();
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
