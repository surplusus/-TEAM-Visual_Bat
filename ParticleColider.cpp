#include "BaseInclude.h"
#include "ParticleColider.h"
#include"BoundingBox.h"


CParticleColider::CParticleColider(CParticle * pParticle)
	:m_Type(COLISION_TYPE_PARTICLE)
{
	m_Particle = pParticle;
}

CParticleColider::~CParticleColider()
{
	Release();
}

void CParticleColider::Update(D3DXVECTOR3 vPos)
{
	m_Info.matWorld._41 = vPos.x;
	m_Info.matWorld._42 = vPos.y;
	m_Info.matWorld._43 = vPos.z;

	D3DMATRIX matWorld = m_Info.matWorld * m_matWorld;

	m_Info.vPos = { matWorld._41,matWorld._42,matWorld._43 };
}

bool CParticleColider::CheckColision(ColiderComponent* pEnemy)
{
	return ColiderComponent::CheckColision(pEnemy);
}




