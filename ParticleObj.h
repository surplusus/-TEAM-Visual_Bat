#pragma once
#include "Particle.h"
class ColiderComponent;
class CParticleObj :
	public CParticle
{
public:
	CParticleObj();
	~CParticleObj();
protected:
	ColiderComponent * m_pColider;
	STATUSINFO m_StatusInfo;
public:
	virtual void Initalize() {}
	virtual bool Progress() { return true; }
	virtual void Render() {}
	virtual void Release() {}
public:
	ColiderComponent * GetColider() { return m_pColider; }
	STATUSINFO GetStatus() { return m_StatusInfo; }
};

