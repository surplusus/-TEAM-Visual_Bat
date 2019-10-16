#pragma once
#include"Particle.h"
class CSkill
	: public CParticle
{
public:
	CSkill();
	~CSkill();
public:
	virtual void	ResetParticle(ATTRIBUTE * pAttribute) {}	
private:
	INFO m_Info;
	float m_fSpeed;
};

