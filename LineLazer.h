#pragma once
#include "Skill.h"
class CLineLazer :
	public CSkill
{
public:
	CLineLazer();
	CLineLazer(INFO& Info);
	~CLineLazer();
public:
	virtual HRESULT InitParticleBuffer(LPDIRECT3DDEVICE9 pDevice) override;
	virtual void	ResetParticle(ATTRIBUTE * pAttribute) override;
	virtual void	Progress() override;

private:
	INFO m_Info;
	float m_fSpeed;
public:

};

