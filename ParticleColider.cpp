#include "BaseInclude.h"
#include "ParticleColider.h"



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
	m_Info.matWorld = m_Info.matWorld*m_matWorld;
		
		
	m_Info.vPos.x=		m_Info.matWorld._41;
	m_Info.vPos.y=		m_Info.matWorld._42;
	m_Info.vPos.z=		m_Info.matWorld._43;
}


