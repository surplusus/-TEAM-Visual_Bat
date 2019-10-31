#include "BaseInclude.h"
#include "Dynamic.h"

CDynamic::CDynamic()
	: m_pAnimationCtrl(nullptr)
	, m_bMove(false)
	, m_fHeight(0.f)
{
}

CDynamic::~CDynamic()
{
	Release();
}

bool CDynamic::Update_vPos_ByDestPoint(const D3DXVECTOR3 * pDestPoint, const float & fSpeed)
{
	D3DXVECTOR3 vDir = *pDestPoint - m_Info.vPos;
	float fDistance = D3DXVec3Length(&vDir);
	float speed = fSpeed;
	D3DXVec3Normalize(&vDir, &vDir);
	if (fDistance < 0.1f) {
		if (fDistance <= 0.001f) {
			m_Info.vPos = *pDestPoint;
			return false;
		}
		D3DXVec3Lerp(&m_Info.vPos, &m_Info.vPos, pDestPoint, 0.5f);
		return true;
	}
	vDir = vDir * speed * g_fDeltaTime;
	if (D3DXVec3Length(&vDir) <= fDistance) {
		m_Info.vPos += vDir;
		return true;
	}
	else {
		m_Info.vPos = *pDestPoint;
		return false;
	}
}

void CDynamic::Release()
{
	if (m_pAnimationCtrl)
	{
		delete m_pAnimationCtrl;
		m_pAnimationCtrl = NULL;
	}
}