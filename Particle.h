#pragma once

#include "Defines.h"
DWORD fword(float f)
{
	return *((DWORD*)&f);
}

class CParticle
{
public:
	CParticle();
	~CParticle();
private:
	vector<PARTICLE_VERTEX> m_vVertex;
	vector<PARTICLE_VERTEX> m_vecVertex_Multi;
	LPDIRECT3DTEXTURE9 m_pTex1;
	LPDIRECT3DTEXTURE9 m_pTex2;

public:
	virtual void SetUp_Particle();
	virtual void Render_Particle();
	virtual void Setup_MultiTexture();
};
