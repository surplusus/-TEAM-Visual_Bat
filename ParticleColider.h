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
public:
	virtual COLISION_TYPE GetType() override { return m_Type; }
	virtual void Update(D3DXVECTOR3 vPos, D3DXMATRIX matWorld) override;
	virtual void Render() override;
	virtual bool CheckColision(ColiderComponent* pEnemy) override;
	CParticleObj* GetParticle() { 
		if (m_Particle) { return m_Particle; }
		else return NULL; 
	}
};
