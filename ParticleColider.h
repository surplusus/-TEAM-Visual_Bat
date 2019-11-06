#pragma once
#include "ColiderComponent.h"
class CParticleObj;
class CParticleColider :
	public ColiderComponent
{
public:
	CParticleColider(CParticleObj* pParticle);
	~CParticleColider();
private:
	CParticleObj* m_Particle;
	const COLISION_TYPE m_Type;
	ColiderComponent m_Colider;
public:
	virtual COLISION_TYPE GetType() override { return m_Type; }
	virtual void Update(D3DXVECTOR3 vPos) override;
	virtual bool CheckColision(ColiderComponent* pEnemy) override;
	CParticleObj* GetParticle() { return m_Particle; }
};
