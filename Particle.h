#pragma once

#include "Defines.h"

class CParticle
{
public:
	CParticle();
	virtual ~CParticle();
protected:
	vector<CUSTOMVERTEX>	m_vecVertexParticle;
	vector<PARTICLE_VERTEX> m_vecVertex_Multi;	
	LPDIRECT3DTEXTURE9 m_pTex0;
	LPDIRECT3DTEXTURE9 m_pTex1;
	LPDIRECT3DTEXTURE9 m_pTex2;
	INFO m_Info;
	vector<DWORD> m_vecRenderInitData;
public:
	virtual void Initalize();
	virtual bool Progress();
	virtual void Render();
	virtual void Release();

public:
	virtual void SetUp_Particle();
	virtual void Render_Particle();
	virtual void RenderEnd_Particle();
	virtual void Update_Particle();
	virtual void Setup_MultiTexture();
	virtual void InitRenderState();

	DWORD fword(float f)
	{
		return *((DWORD*)&f);
	}

};
