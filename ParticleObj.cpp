#include "BaseInclude.h"
#include "ParticleObj.h"


CParticleObj::CParticleObj()
	: m_pColider(NULL)
{
}


CParticleObj::~CParticleObj()
{
}
bool CParticleObj::Move_Chase(const D3DXVECTOR3* pDestPoint
	, const float& fSpeed)
{
	D3DXVECTOR3 vDirection = *pDestPoint - m_Info.vPos;

	float fDistance = D3DXVec3Length(&vDirection);

	D3DXVec3Normalize(&vDirection, &vDirection);

	m_Info.vPos += vDirection * fSpeed * g_fDeltaTime;

	if (fDistance < 0.1f)
		return false;
	return true;
}