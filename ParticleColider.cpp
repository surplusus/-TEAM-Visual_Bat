#include "BaseInclude.h"
#include "ParticleColider.h"
#include"BoundingBox.h"
#include"ParticleObj.h"

CParticleColider::CParticleColider(CParticleObj * pParticle)
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

	m_Info.vPos = vPos;
	WorldSetting();
	D3DXMATRIX World = m_Info.matWorld * m_ParentMatrix;
	m_Info.vPos = { World._41,World._42, World._43 };
}

bool CParticleColider::CheckColision(ColiderComponent* pEnemy)
{
	return ColiderComponent::CheckColision(pEnemy);
}


void CParticleColider::Render()
{
	SetTexture(0, NULL);
	SetTransform(D3DTS_WORLD, &(m_Info.matWorld*m_ParentMatrix));
	SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	if (m_pBoxMesh)	m_pBoxMesh->GetMesh()->DrawSubset(0);
	if (m_SphereMesh)m_SphereMesh->GetMesh()->DrawSubset(0);
	SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	SetTexture(0, NULL);
}

