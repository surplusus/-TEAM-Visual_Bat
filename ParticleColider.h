#pragma once
#include "ColiderComponent.h"
class CParticle;
class CParticleColider :
	public ColiderComponent
{
public:
	CParticleColider(CParticle* pParticle);
	~CParticleColider();
private:
	CParticle* m_Particle;
	const COLISION_TYPE m_Type;
public:
	virtual COLISION_TYPE GetType() override { return m_Type; }
	virtual void Update(D3DXVECTOR3 vPos) override;
};
