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

void CParticleObj::UpdateMatrix()
{
	D3DXMATRIX matRotX, matRotY, matRotZ;
	D3DXMATRIX matScale, matRot, matTrans;
	D3DXMatrixScaling(&matScale, 1, 1, 1);
	if (_isnan(m_fAngle[ANGLE_Y]))	m_fAngle[ANGLE_Y] = 0.f;
	D3DXMatrixRotationY(&matRot, m_fAngle[ANGLE_Y]);
	D3DXVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &matRot);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixIdentity(&m_Info.matWorld);
	m_Info.matWorld = matScale * matRot * matTrans;

}
